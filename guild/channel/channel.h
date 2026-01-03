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
    bool nsfw = 0;
    snowflake lastMessageId;
    uint16_t timeout;                       // amount of seconds a user has to wait before sending another message
    snowflake parentId;                     // for guild channels: id of the parent category for a channel (each parent category can contain up to 50 channels), for threads: id of the text channel this thread was created
    uint64_t lastPinTimestamp;
public:
    virtual ~DiscordChannel() {}
    friend class ChannelJsonDeserializer;
    snowflake getId() const;
    ChannelType getType() const;
    snowflake getGuildId() const;
    uint16_t getPosition() const;
    std::vector<PermissionOverwrite> getPermissionOverwrites() const;
    std::string getName() const;
    std::string getTopic() const;
    bool getNsfw() const;
    snowflake getLastMessageId() const;
    uint16_t getTimeout() const;                       
    snowflake getParentId() const;                     
    uint64_t getLastPinTimestamp() const;
};

class DiscordVoiceChannel : public DiscordChannel{
    uint32_t bitrate;
    uint16_t userLimit;
    std::string rtcRegion;
public:
    friend class ChannelJsonDeserializer;
    uint32_t getBitrate() const;
    uint16_t getUserLimit() const;
    std::string getRtcRegion() const;
};

class DiscordTextChannel : public DiscordChannel{};

class DiscordDmChannel : public DiscordChannel{
    std::vector<DiscordUser> recipients;
    snowflake ownerId;                      // id of the creator of the group DM or thread
    snowflake applicationId;                // application id of the group DM creator if it is bot-created
    bool managed = 0;                       // for group DM channels: whether the channel is managed by an application via the gdm.join OAuth2 scope
    std::string icon;                       // icon hash of the group DM
public:
    friend class ChannelJsonDeserializer;
    std::vector<DiscordUser> getRecipients() const;
    snowflake getOwnerId() const;
    snowflake getApplicationId() const;
    bool getManaged() const;
    std::string getIcon() const;
};

bool isGuild(ChannelType type);
#endif