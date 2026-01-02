#ifndef USER_JSON_H
#define USER_JSON_H
#include <nlohmann/json.hpp>
#include "user.h"

using json = nlohmann::json;

class UserJsonDeserializer{
public:
    static void toDiscordUser(const json &j, DiscordUser &user);
};

void from_json(const json &j, DiscordUser &user);
#endif