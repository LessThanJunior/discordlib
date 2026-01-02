#include "bot.h"
#include "https/https.h"
#include <nlohmann/json.hpp>
#include <iostream>
#include "snowflake.h"
#include "guild/guild_json.h"
#include "guild/channel/channel_json.h"
#include "user/user_json.h"

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

DiscordGuild DiscordBot::getDiscordGuild(uint64_t id)
{
    return getDiscordGuild(snowflake(id));
}

std::unique_ptr<DiscordChannel> DiscordBot::getDiscordChannel(snowflake id) 
{
    std::string test = "discord.com/api/v10/channels/" + std::to_string((uint64_t)id);
    json j = connect(test, this->params);
    _json = std::move(j);
    auto type = _json.at("type").get<ChannelType>();

    if(type == ChannelType::GUILD_VOICE){
        auto voiceChannel = std::make_unique<DiscordVoiceChannel>();
        _json.get_to(*voiceChannel);
        return voiceChannel;
    }

    if(type == ChannelType::DM){
        auto dmChannel = std::make_unique<DiscordDmChannel>();
        _json.get_to(*dmChannel);
        return dmChannel;
    }

    auto channel = std::make_unique<DiscordChannel>();
    _json.get_to(*channel);

    return channel;
}

std::unique_ptr<DiscordChannel> DiscordBot::getDiscordChannel(uint64_t id) 
{
    return getDiscordChannel(snowflake(id));
}

DiscordUser DiscordBot::me(){
    json j = connect("discord.com/api/v10/users/@me", params);
    _json = std::move(j);

    return _json.get<DiscordUser>();
}

DiscordUser DiscordBot::getDiscordUser(snowflake id){
    json j = connect("discord.com/api/v10/users/" + std::to_string(id), params);
    _json = std::move(j);

    return _json.get<DiscordUser>();
}

DiscordUser DiscordBot::getDiscordUser(uint64_t id){
    return getDiscordUser(snowflake(id));
}

json DiscordBot::getJson()
{
    return _json;
}