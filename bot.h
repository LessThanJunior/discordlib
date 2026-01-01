#ifndef BOT_H
#define BOT_H
#include <map>
#include <string>
#include "guild/guild.h"
#include <nlohmann/json.hpp>
#include "guild/channel/channel.h"

using json = nlohmann::json;

class DiscordBot{
    std::map<std::string, std::string> params;
    json _json;
    
public:
    DiscordBot(std::map<std::string, std::string> params);
    DiscordGuild getDiscordGuild(uint64_t id);
    DiscordGuild getDiscordGuild(snowflake id);

    std::unique_ptr<DiscordChannel> getDiscordChannel(uint64_t id);
    std::unique_ptr<DiscordChannel> getDiscordChannel(snowflake id);
    json getJson();
};
#endif