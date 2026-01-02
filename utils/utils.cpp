#include "utils.h"

bool hasValue(const json &j, std::string key){
    return j.contains(key) && !j.at(key).is_null();
}