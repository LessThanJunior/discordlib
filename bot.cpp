#include "bot.h"
#include "https/https.h"
#include <nlohmann/json.hpp>
#include <iostream>
#include "snowflake.h"
#include "guild/guild_json.h"

DiscordBot::DiscordBot(std::map<std::string, std::string> params)
{
    this->params = params;
}

DiscordGuild DiscordBot::getDiscordGuild(snowflake id)
{
    std::string test = "discord.com/api/v10/guilds/" + std::to_string((uint64_t)id);
    json j = connect(test, this->params);
    _json = std::move(j);
    return _json.get<DiscordGuild>();; 
}

json DiscordBot::getJson()
{
    return _json;
}

DiscordGuild DiscordBot::getDiscordGuild(uint64_t id)
{
    return getDiscordGuild(snowflake(id));
}
