#include "channel_json.h"
#include <iostream>

bool isGuild(ChannelType type){
    return type == ChannelType::GUILD_TEXT ||
        type == ChannelType::GUILD_VOICE ||
        type == ChannelType::GUILD_ANNOUNCEMENT ||
        type == ChannelType::GUILD_CATEGORY ||
        type == ChannelType::GUILD_DIRECTORY ||
        type == ChannelType::GUILD_FORUM || 
        type == ChannelType::GUILD_MEDIA ||
        type == ChannelType::GUILD_STAGE_VOICE;
}

void text(){

}

void dm(){

}

void ChannelJsonDeserializer::toDiscordVoiceChannel(const json &j, DiscordVoiceChannel &channel){

    channel.bitrate = j.at("bitrate").get<uint32_t>();
    channel.userLimit = j.at("user_limit").get<uint16_t>();
    
    if(j.contains("rtc_region") && !j.at("rtc_region").is_null())
        channel.rtcRegion = j.at("rtc_region").get<std::string>();
}


void ChannelJsonDeserializer::toDiscordChannel(const json &j, DiscordChannel &channel)
{
    j.at("type").get_to(channel.type);

    channel.id = j.at("id").get<std::string>();

    if(isGuild(channel.type)){
        channel.guildId = j.at("guild_id").get<std::string>();

        if(j.contains("parent_id") && !j.at("parent_id").is_null())
            channel.parentId = j.at("parent_id").get<std::string>();

        channel.position = j.at("position").get<uint16_t>();

        if(j.contains("rate_limit_per_user") && !j.at("rate_limit_per_user").is_null())
            channel.timeout = j.at("rate_limit_per_user").get<uint16_t>();

        if(j.contains("last_message_id") && !j.at("last_message_id").is_null())
            channel.lastMessageId = j.at("last_message_id").get<std::string>();

        j.at("name").get_to(channel.name);

        if(j.contains("nsfw") && !j.at("nsfw").is_null())
            j.at("nsfw").get_to(channel.nsfw);
    }
}

void from_json(const json &j, DiscordChannel &channel){
    ChannelJsonDeserializer::toDiscordChannel(j, channel);
}

void from_json(const json& j, DiscordVoiceChannel &channel){
    from_json(j, dynamic_cast<DiscordChannel&>(channel));
    ChannelJsonDeserializer::toDiscordVoiceChannel(j, channel);
}