#include "channel_json.h"
#include <iostream>
#include "../../utils/utils.h"
#include "../../user/user_json.h"

void ChannelJsonDeserializer::toDiscordVoiceChannel(const json &j, DiscordVoiceChannel &channel){

    channel.bitrate = j.at("bitrate").get<uint32_t>();
    channel.userLimit = j.at("user_limit").get<uint16_t>();
    
    if(hasValue(j, "rtc_region"))
        channel.rtcRegion = j.at("rtc_region").get<std::string>();
}

void ChannelJsonDeserializer::toDiscordChannel(const json &j, DiscordChannel &channel)
{
    j.at("type").get_to(channel.type);

    channel.id = j.at("id").get<std::string>();
    if(hasValue(j, "last_message_id"))
        channel.lastMessageId = j.at("last_message_id").get<std::string>();

    if(isGuild(channel.type)){
        channel.guildId = j.at("guild_id").get<std::string>();

        if(hasValue(j, "parent_id"))
            channel.parentId = j.at("parent_id").get<std::string>();

        channel.position = j.at("position").get<uint16_t>();

        if(hasValue(j, "rate_limit_per_user"))
            channel.timeout = j.at("rate_limit_per_user").get<uint16_t>();

        j.at("name").get_to(channel.name);

        if(hasValue(j, "nsfw"))
            j.at("nsfw").get_to(channel.nsfw);
    }
}

void ChannelJsonDeserializer::toDiscordDmChannel(const json &j, DiscordDmChannel &channel){
    if(hasValue(j, "owner_id"))
        channel.ownerId = j.at("owner_id").get<std::string>();

    if(hasValue(j, "application_id"))
        channel.applicationId = j.at("application_id").get<std::string>();

    if(hasValue(j, "managed"))
        channel.managed = j.at("managed").get<bool>();
    
    if(hasValue(j, "icon"))
        channel.icon = j.at("icon").get<std::string>();

    if(j.contains("recipients") && j.at("recipients").is_array())
        for(const auto& recipient : j.at("recipients")){
            channel.recipients.push_back(recipient.get<DiscordUser>());
        }
}

void from_json(const json &j, DiscordChannel &channel){
    ChannelJsonDeserializer::toDiscordChannel(j, channel);
}

void from_json(const json& j, DiscordVoiceChannel &channel){
    from_json(j, dynamic_cast<DiscordChannel&>(channel));
    ChannelJsonDeserializer::toDiscordVoiceChannel(j, channel);
}

void from_json(const json& j, DiscordDmChannel &channel){
    from_json(j, dynamic_cast<DiscordChannel&>(channel));
    ChannelJsonDeserializer::toDiscordDmChannel(j, channel);
}