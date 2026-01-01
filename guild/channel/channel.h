#ifndef GUILD_CHANNEL_H
#define GUILD_CHANNEL_H

#include "../../snowflake.h"
#include "channel_permissions.h"
#include <vector>
#include "../../user/user.h"

enum class ChannelType{
    GUILD_TEXT,
    DM,
    GUILD_VOICE,
    GROUP_DM,
    GUILD_CATEGORY,
    GUILD_ANNOUNCEMENT,
    ANNOUNCEMENT_THREAD = 10,
    PUBLIC_THREAD,
    PRIVATE_THREAD,
    GUILD_STAGE_VOICE,
    GUILD_DIRECTORY,
    GUILD_FORUM,
    GUILD_MEDIA
};

enum class ChannelVideoQualityMode{
    AUTO = 1,	// Discord chooses the quality for optimal performance
    FULL = 2	// 720p
};

enum class ChannelFlags{
    PINNED =                        1 << 1,     // this thread is pinned to the top of its parent GUILD_FORUM or GUILD_MEDIA channel
    REQUIRE_TAG =                   1 << 4,     // whether a tag is required to be specified when creating a thread in a GUILD_FORUM or a GUILD_MEDIA channel
    HIDE_MEDIA_DOWNLOAD_OPTIONS =   1 << 15     // when set hides the embedded media download options. Available only for media channels
};

enum class CnannelSortOrder{
    LATEST_ACTIVITY,
    CREATION_DATE,
};

enum class ChannelForumLayoutType{
    NOT_SET,        // No default has been set for forum channel
    LIST_VIEW,      // Display posts as a list    
    GALLERY_VIEW,   // Display posts as a collection of tiles
};


class DiscordChannel{
    snowflake id;
    ChannelType type;
    snowflake guildId;
    uint16_t position;
    std::vector<PermissionOverwrite> permissionOverwrites;
    std::string name;
    std::string topic;
    bool nsfw;
    snowflake lastMessageId;
    uint16_t bitrate;
    uint16_t userLimit;                     // the user limit of the voice channel
    uint16_t rateLimitPerUser;              // amount of seconds a user has to wait before sending another message
    std::vector<DiscordUser> recipients;
    std::string icon;                       // icon hash of the group DM
    snowflake ownerId;                      // id of the creator of the group DM or thread
    snowflake applicationId;                // application id of the group DM creator if it is bot-created
    bool managed;                           // for group DM channels: whether the channel is managed by an application via the gdm.join OAuth2 scope
    snowflake parentId;                     // for guild channels: id of the parent category for a channel (each parent category can contain up to 50 channels), for threads: id of the text channel this thread was created
    uint64_t lastPinTimestamp;
    std::string rtcRegion;

};

class DiscordVoiceChannel : DiscordChannel{};

class DiscordTextChannel : DiscordChannel{};

class DiscordDMChannel : DiscordChannel{};
#endif