#ifndef BOT_H
#define BOT_H
#include <map>
#include <string>
#include "guild/guild.h"
#include <nlohmann/json.hpp>

using json = nlohmann::json;

class DiscordBot{
    std::map<std::string, std::string> params;
    json _json;
public:
    DiscordBot(std::map<std::string, std::string> params);
    DiscordGuild getDiscordGuild(uint64_t id);
    DiscordGuild getDiscordGuild(snowflake id);
    json getJson();
};
#endif