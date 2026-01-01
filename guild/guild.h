#ifndef GUILD_H
#define GUILD_H
#include "../snowflake.h"
#include <string>
#include <optional>
#include <vector>

class DiscordGuildRole;
class DiscordGuildSticker;
class DiscordGuildEmoji;

enum class VerificationLevel{
    NONE,
    LOW,
    MEDIUM,
    HIGH,
    VERY_HIGH
};

enum class NsfwLevel{
    DEFAULT,
    EXPLICIT,
    SAFE,
    AGE_RESTRICTED
};

struct RoleColors{
    uint32_t primaryColor;
    uint32_t secondaryColor;
    uint32_t tertiaryColor;
};

class DiscordGuild{
    snowflake id;
    std::string name;
    std::string icon;
    std::string iconHash;
    std::string splash;
    snowflake ownerId;
    snowflake afkChannelId;
    snowflake rulesChannelId;
    uint64_t afkTimeout;
    VerificationLevel verificationLevel;
    std::vector<DiscordGuildRole> roles;
    std::vector<DiscordGuildEmoji> emojis;
    std::vector<DiscordGuildSticker> stickers;
    std::string vanityUrlCode;
    std::string description;
    std::string banner;
    std::string preferredLocale;
    std::string publicUpdatesChannelId;
    NsfwLevel nsfwLevel;
    bool premiumProgressBarEnabled;
    snowflake safetyAlertsChannelId;
    uint8_t boostLevel;
public:
    friend class GuildJsonDeserializer;
    snowflake getId() const;
    std::string getName() const;
    snowflake getOwnerId() const;
    snowflake getAfkChannelId() const;
    snowflake getRulesChannelId() const;
    uint64_t getAfkTimeout() const;
    VerificationLevel getVerificationLevel() const;
    std::vector<DiscordGuildRole> getRoles() const;
    std::vector<DiscordGuildEmoji> getEmojis() const;
    std::vector<DiscordGuildSticker> getStickers() const;
    std::string getVanityUrlCode() const;
    std::string getDescription() const;
    std::string getBanner() const;
    std::string getPreferredLocale() const;
    std::string getPublicUpdatesChannelId() const;
    NsfwLevel getNsfwLevel() const;
    bool getPremiumProgressBarEnabled() const;
    snowflake getSafetyAlertsChannelId() const;
    std::string getIcon() const;
    std::string getIconHash() const;
    std::string getSplash() const;
    uint8_t getBoostLevel() const;
};

class DiscordGuildRole{
    snowflake id;
    std::string name;
    uint32_t color;
    RoleColors colors;
    bool hoist;
    std::string icon;
    std::string unicodeEmoji;
    uint32_t position;
    std::string permissions;
    bool managed;
    bool mentionable;
    uint32_t flags;
public:
    friend class GuildJsonDeserializer;
    snowflake getId() const;
    std::string getName() const;
    uint32_t getColor() const;
    RoleColors getColors() const;
    bool getHoist() const;
    std::string getIcon() const;
    std::string getUnicodeEmoji() const;
    uint32_t getPosition() const;
    std::string getPermissions() const;
    bool getManaged() const;
    bool getMentionable() const;
    uint32_t getFlags() const;
};

class DiscordGuildSticker{
    snowflake id;
public:
    friend class GuildJsonDeserializer;
};

class DiscordGuildEmoji{
    snowflake id;
    snowflake packId;
    std::string name;
    std::string description;
    std::string tags;
    uint32_t type;
    uint32_t formatType;
    bool available;
    snowflake guild_id;
public:
    friend class GuildJsonDeserializer;
};

std::string descriptionVerificationLevel(const VerificationLevel& verification);
#endif