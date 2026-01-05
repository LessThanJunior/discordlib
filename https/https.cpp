#include "https.h"
#include <iostream>
#include <istream>
#include <ostream>
#include <string>
#include <boost/asio.hpp>
#include <boost/asio/ssl.hpp>

using boost::asio::ip::tcp;
using namespace boost;

std::map<std::string, HttpsCache> httpsCache;

// HttpsCache
HttpsCache::HttpsCache(std::chrono::milliseconds retry, json json){
    this->retry = retry;
    this->jsonResponse = json;
    this->nextRetryTime = std::chrono::high_resolution_clock::now() + retry;
}

bool HttpsCache::isReadyForRetry() { return std::chrono::high_resolution_clock::now() >= nextRetryTime; }

std::chrono::milliseconds HttpsCache::getRetry(){ return retry; }
json HttpsCache::getJsonResponse() { return jsonResponse; }


// Https
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
            size = std::stoull(body.substr(previous_line, size_line - previous_line), nullptr, 16);
        } catch(const std::exception& e){
            std::cout << "EXCEPTION: " << body.substr(previous_line, size_line);
        }

        if(size == 0){
            break;
        }

        // JSON
        std::string temp = body.substr(size_line+2, size);
        json_string.append(std::move(temp));

        previous_line = size_line + 2 + size + 2;
        if(previous_line > body.length()){
            break;
        }
    }

    return json_string;
}

std::string getBody(const std::string &response){
    auto pos = response.find("\r\n\r\n");
    std::string body = (pos == std::string::npos) ? response
                                              : response.substr(pos + 4);

    return body;
}

int parseHttpStatus(const std::string& response) {
    auto end = response.find("\r\n");
    if (end == std::string::npos)
        return -1;

    std::string statusLine = response.substr(0, end);

    auto firstSpace = statusLine.find(' ');
    if (firstSpace == std::string::npos)
        return -1;

    auto secondSpace = statusLine.find(' ', firstSpace + 1);
    if (secondSpace == std::string::npos)
        return -1;

    std::string codeStr =
        statusLine.substr(firstSpace + 1, secondSpace - firstSpace - 1);

    return std::stoi(codeStr);
}

using httpsParams = std::map<std::string, std::string>;
using tcpSocket = asio::ssl::stream<tcp::socket>;

std::string getResponseFromRequest(const std::string &url, httpsParams params){
    std::size_t begin = url.find_first_of('/');
    std::string host = url.substr(0,begin);
    std::string query = url.substr(begin);

    asio::io_context io;
    asio::ssl::context ssl_ctx(asio::ssl::context::tls_client);

    tcp::resolver resolver(io);
    asio::ssl::stream<tcp::socket> socket(io, ssl_ctx);

    auto endpoint = resolver.resolve(host, "443");

    // TCP connection
    asio::connect(socket.next_layer(), endpoint);

    // TCP handshake
    socket.handshake(boost::asio::ssl::stream_base::client);

    std::string request;
    request.append("GET " + query + " HTTP/1.1\r\n");
    request.append("Host: " + host + "\r\n");
    request.append("Authorization: " + params["Authorization"] + "\r\n");
    request.append("User-Agent: " + params["User-Agent"] + "\r\n");
    request.append("Accept: application/json\r\n");
    request.append("Connection: close\r\n\r\n");

    // TLS over HTTP
    boost::asio::write(socket, boost::asio::buffer(request));

    boost::asio::streambuf response;
    boost::system::error_code ec;

    while (boost::asio::read(socket, response,
           boost::asio::transfer_at_least(1), ec)) {}

    std::string response_string(
        boost::asio::buffers_begin(response.data()),
        boost::asio::buffers_end(response.data())
    );
    return response_string;
}

json Https::connect(std::string url, std::map<std::string, std::string> params){
    std::string response_string;

    if(httpsCache.find(url) != httpsCache.end()){
        auto& cache = httpsCache.at(url);
        if(!cache.isReadyForRetry()){
            return cache.getJsonResponse();
        }
    }

    response_string = getResponseFromRequest(url, params);
    if(parseHttpStatus(response_string) != 200){
        std::string httpsBody = getBody(response_string);
        double getRetryAfter = 0;
        try{
            auto jsonBody = json::parse(httpsBody);
            if(jsonBody.contains("retry_after")){
                getRetryAfter = jsonBody.at("retry_after").get<double>();
            }
        } catch(...){

        }

        uint32_t milliseconds = getRetryAfter * 1000;
        if(milliseconds > 0 && (httpsCache.find(url) != httpsCache.end())){
            auto& cache = httpsCache.at(url);
            cache = HttpsCache(std::chrono::milliseconds(milliseconds), cache.getJsonResponse());
            return cache.getJsonResponse();
        }
    }
    else {
        std::string json_text = jsonDecodeChunked(response_string);
        httpsCache.insert_or_assign(url, HttpsCache(std::chrono::milliseconds(0), json::parse(json_text)));
    }
    return httpsCache.at(url).getJsonResponse();
}