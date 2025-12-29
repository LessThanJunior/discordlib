#include "https.h"
#include <iostream>
#include <istream>
#include <ostream>
#include <string>
#include <boost/asio.hpp>
#include <boost/asio/ssl.hpp>

using boost::asio::ip::tcp;

std::string jsonDecodeChunked(std::string response){
    auto pos = response.find("\r\n\r\n");
    std::string json_string;
    std::string body = (pos == std::string::npos) ? response
                                              : response.substr(pos + 4);
    
    std::size_t previous_line = 0;
    
    while(true){
        // SIZE
        std::size_t size_line = body.find("\r\n", previous_line);
        if (size_line == std::string::npos) break;

        std::size_t size = 0;
        try { 
            size = std::stoul(body.substr(previous_line, size_line - previous_line), nullptr, 16);
        } catch(const std::exception& e){
            std::cout << "EXCEPTION: " << body.substr(previous_line, size_line);
        }

        if(size == 0){
            break;
        }
        //std::cout << size << "\n";

        // JSON
        std::string temp = body.substr(size_line+2, size);
        json_string.append(std::move(temp));
        //std::cout << temp;
        previous_line = size_line + 2 + size + 2;
        if(previous_line > body.length()){
            break;
        }
    }

    return json_string;
}

json connect(std::string url, std::map<std::string, std::string> params){
    std::size_t begin = url.find_first_of('/');
    std::string host = url.substr(0,begin);
    std::string query = url.substr(begin);

    boost::asio::io_context io;
    boost::asio::ssl::context ssl_ctx(boost::asio::ssl::context::tls_client);

    tcp::resolver resolver(io);
    boost::asio::ssl::stream<tcp::socket> socket(io, ssl_ctx);

    auto endpoint = resolver.resolve(host, "443");
    boost::asio::connect(socket.next_layer(), endpoint);

    socket.handshake(boost::asio::ssl::stream_base::client);

    std::string request;
    request.append("GET " + query + " HTTP/1.1\r\n");
    request.append("Host: " + host + "\r\n");
    request.append("Authorization: " + params["Authorization"] + "\r\n");
    request.append("User-Agent: " + params["User-Agent"] + "\r\n");
    request.append("Accept: application/json\r\n");
    request.append("Connection: close\r\n\r\n");

    //std::cout << request;

    boost::asio::write(socket, boost::asio::buffer(request));

    boost::asio::streambuf response;
    boost::system::error_code ec;

    while (boost::asio::read(socket, response,
           boost::asio::transfer_at_least(1), ec)) {}

    std::string response_string(
        boost::asio::buffers_begin(response.data()),
        boost::asio::buffers_end(response.data())
    );

    std::string json = jsonDecodeChunked(response_string);
    return json::parse(json);
}

/*
    std::string chunked_test =
    "\r\n\r\n"
    "5\r\n"
    "Hello\r\n"
    "6\r\n"
    " World\r\n"
    "0\r\n"
    "\r\n";
    std::cout << jsonDecodeChunked(chunked_test);
*/
