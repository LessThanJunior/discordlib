#include "channel.h"

// DiscordChannel
snowflake DiscordChannel::getId() const { return id; }
ChannelType DiscordChannel::getType() const { return type; }
snowflake DiscordChannel::getGuildId() const { return guildId; }
uint16_t DiscordChannel::getPosition() const { return position; }
std::vector<PermissionOverwrite> DiscordChannel::getPermissionOverwrites() const { return permissionOverwrites; }
std::string DiscordChannel::getName() const { return name; }
std::string DiscordChannel::getTopic() const { return topic; }
bool DiscordChannel::getNsfw() const { return nsfw; }
snowflake DiscordChannel::getLastMessageId() const { return lastMessageId; }
uint16_t DiscordChannel::getTimeout() const { return timeout; }                       
snowflake DiscordChannel::getParentId() const { return parentId; }                     
uint64_t DiscordChannel::getLastPinTimestamp() const { return lastPinTimestamp; }

// DiscordVoiceChannel
uint32_t DiscordVoiceChannel::getBitrate() const { return bitrate; }
uint16_t DiscordVoiceChannel::getUserLimit() const { return userLimit; }
std::string DiscordVoiceChannel::getRtcRegion() const { return rtcRegion; }

// DiscordDmChannel
std::vector<DiscordUser> DiscordDmChannel::getRecipients() const { return recipients; }
snowflake DiscordDmChannel::getOwnerId() const { return ownerId; }
snowflake DiscordDmChannel::getApplicationId() const { return applicationId; }
bool DiscordDmChannel::getManaged() const { return managed; }
std::string DiscordDmChannel::getIcon() const { return icon; }

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