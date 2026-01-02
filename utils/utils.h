#ifndef UTILS_H
#define UTILS_H
#include <nlohmann/json.hpp>
#include <string>
using json = nlohmann::json;

bool hasValue(const json &j, std::string key);
#endif