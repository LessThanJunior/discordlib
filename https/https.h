#ifndef HTTPS_H
#define HTTPS_H
#include <string>
#include <map>
#include "../guild/guild.h"
#include <nlohmann/json.hpp>

using json = nlohmann::json;

// Function which connect discord api and retrieve JSON object
json connect(std::string url, std::map<std::string, std::string> params);
std::string jsonDecodeChunked(std::string response);
#endif
