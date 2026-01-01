#include "guild.h"
#include "guild_json.h"

// DiscordGuildRole JSON Deserealizer

void GuildJsonDeserializer::toDiscordRole(const json &j, DiscordGuildRole &role){
    role.id = j.at("id").get<std::string>();
    role.mentionable = j.at("mentionable").get<bool>();
    role.color = j.at("color").get<uint32_t>();
    role.hoist = j.at("hoist").get<bool>();
    role.position = j.at("position").get<uint32_t>();
    role.managed = j.at("managed").get<bool>();

    if(!j.at("icon").is_null()){
        role.icon = j.at("icon").get<std::string>();
    }

    role.name = j.at("name").get<std::string>();
    role.permissions = j.at("permissions").get<std::string>();

}

// DiscordGuild JSON Deserealizer

void GuildJsonDeserializer::toDiscordGuild(const json &j, DiscordGuild &guild)
{
    if(j.contains("vanity_url_code") && !j.at("vanity_url_code").is_null()){
        j.at("vanity_url_code").get_to(guild.vanityUrlCode);
    }
    
    if(j.contains("description") && !j.at("description").is_null()){
        j.at("description").get_to(guild.description);
    }

    if(j.contains("banner") && !j.at("banner").is_null()){
        j.at("banner").get_to(guild.banner);
    }

    if(j.contains("preferred_locale") && !j.at("preferred_locale").is_null()){
        j.at("preferred_locale").get_to(guild.preferredLocale);
    }

    if(j.contains("public_updates_channel_id") && !j.at("public_updates_channel_id").is_null()){
        j.at("public_updates_channel_id").get_to(guild.publicUpdatesChannelId);
    }

    if(j.contains("safety_alerts_channel_id") && !j.at("safety_alerts_channel_id").is_null()){
        guild.safetyAlertsChannelId = j.at("safety_alerts_channel_id").get<std::string>();
    }
    
    if(j.contains("icon") && !j.at("icon").is_null()){
        j.at("icon").get_to(guild.icon);
    }
    
    if(j.contains("icon_hash") && !j.at("icon_hash").is_null()){
        j.at("icon_hash").get_to(guild.iconHash);
    }

    if(j.contains("splash") && !j.at("splash").is_null()){
        j.at("splash").get_to(guild.splash);
    }

    if(j.contains("rules_channel_id") && !j.at("rules_channel_id").is_null()){
        guild.rulesChannelId = j.at("rules_channel_id").get<std::string>();
    }

    
    if(!j.at("roles").is_null() && j.at("roles").is_array()){
        for(const auto& r : j.at("roles")){
            guild.roles.push_back(r.get<DiscordGuildRole>());
        }
    }
    

    if(j.contains("afk_timeout") && !j.at("afk_timeout").is_null()){
        j.at("afk_timeout").get_to(guild.afkTimeout);
    }

    if(j.contains("name") && !j.at("name").is_null()){
        j.at("name").get_to(guild.name);
    }

    if(j.contains("verification_level") && !j.at("verification_level").is_null()){
        j.at("verification_level").get_to(guild.verificationLevel);
    }

    if(j.contains("premium_tier") && !j.at("premium_tier").is_null()){
        j.at("premium_tier").get_to(guild.boostLevel);
    }

    if(j.contains("owner_id") && !j.at("owner_id").is_null()) {
        guild.ownerId = j.at("owner_id").get<std::string>();
    }

    if(j.contains("nsfw_level") && !j.at("nsfw_level").is_null()){
        j.at("nsfw_level").get_to(guild.nsfwLevel);
    }

    if(j.contains("premium_progress_bar_enabled") && !j.at("premium_progress_bar_enabled").is_null()){
        j.at("premium_progress_bar_enabled").get_to(guild.premiumProgressBarEnabled);
    }

    if(j.contains("id") && !j.at("id").is_null()){
        guild.id = j.at("id").get<std::string>();
    }
}

void from_json(const json& j1, DiscordGuildRole &role){
    GuildJsonDeserializer::toDiscordRole(j1, role);
}

void from_json(const json& j1, DiscordGuild &role){
    GuildJsonDeserializer::toDiscordGuild(j1, role);
}
