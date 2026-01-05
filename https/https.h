#ifndef HTTPS_H
#define HTTPS_H
#include <string>
#include <map>
#include "../guild/guild.h"
#include <nlohmann/json.hpp>
#include <chrono>
#include <ctime>

using json = nlohmann::json;

// Function which connect discord api and retrieve JSON object
// std::string jsonDecodeChunked(std::string response);

class HttpsCache{
    std::chrono::milliseconds retry;
    json jsonResponse;
    std::chrono::time_point<std::chrono::high_resolution_clock> nextRetryTime;
public:
    json getJsonResponse();
    std::chrono::milliseconds getRetry();
    HttpsCache(std::chrono::milliseconds retry, json json);

    bool isReadyForRetry();
};

class Https{
public:
    json connect(std::string url, std::map<std::string, std::string> params);
};
#endif
