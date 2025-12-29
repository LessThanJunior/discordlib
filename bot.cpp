#include "bot.h"
#include "https/https.h"
#include <nlohmann/json.hpp>
#include <iostream>

DiscordBot::DiscordBot(std::map<std::string, std::string> params)
{
    this->params = params;
}


template <typename T>
T foo(const json& j, std::string key){
    if(j.find(key) == j.end()){return {};}
    if(!j.at(key).is_null()){
        return j.at(key).get<T>(); 
    }
    else return {};
}


DiscordGuild DiscordBot::getDiscordGuild(snowflake id)
{
    DiscordGuild guild;
    std::string test = "discord.com/api/v10/guilds/" + std::to_string((uint64_t)id);
    json j = connect(test, this->params);

    guild.id = j.at("id").get<std::string>();

    guild.ownerId = foo<std::string>(j, "owner_id");
    guild.afkChannelId = foo<std::string>(j, "afk_channel_id");
    guild.rulesChannelId = foo<std::string>(j, "rules_channel_id");

    //Need think about roles, emojis, stickers
    
    if(!j.at("roles").is_null() && j.at("roles").is_array()){
        for(const auto& r : j.at("roles")){
            DiscordGuildRole role;

            role.id = r.at("id").get<std::string>();
            role.mentionable = r.at("mentionable").get<bool>();
            role.color = r.at("color").get<uint32_t>();
            role.hoist = r.at("hoist").get<bool>();
            role.position = r.at("position").get<uint32_t>();
            role.managed = r.at("managed").get<bool>();

            if(!r.at("icon").is_null()){
                role.icon = r.at("icon").get<std::string>();
            }
            role.name = r.at("name").get<std::string>();
            role.permissions = r.at("permissions").get<std::string>();

            guild.roles.push_back(role);
        }
    }

    guild.afkTimeout = j.at("afk_timeout").get<uint64_t>();
    guild.name = j.at("name").get<std::string>();
    guild.verificationLevel = j.at("verification_level").get<VerificationLevel>();
    guild.boostLevel = j.at("premium_tier").get<uint16_t>();

    guild.vanityUrlCode = foo<std::string>(j, "vanity_url_code");
    guild.description = foo<std::string>(j, "description");
    guild.banner = foo<std::string>(j, "banner");
    guild.preferredLocale = foo<std::string>(j, "preferred_locale");
    guild.publicUpdatesChannelId = foo<std::string>(j, "public_updates_channel_id");
    guild.safetyAlertsChannelId = foo<std::string>(j, "safety_alerts_channel_id");
    guild.icon = foo<std::string>(j, "icon");
    guild.iconHash = foo<std::string>(j, "icon_hash");
    guild.splash = foo<std::string>(j, "splash");

    guild.nsfwLevel = j.at("nsfw_level").get<NsfwLevel>();
    guild.premiumProgressBarEnabled = j.at("premium_progress_bar_enabled").get<bool>();
    
    _json = std::move(j);
    return guild; 
}

json DiscordBot::getJson()
{
    return _json;
}

DiscordGuild DiscordBot::getDiscordGuild(uint64_t id)
{
    return getDiscordGuild(snowflake(id));
}