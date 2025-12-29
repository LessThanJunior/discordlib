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
    std::optional<std::string> icon;
    std::optional<std::string> iconHash;
    std::optional<std::string> splash;
    snowflake ownerId;
    std::optional<snowflake> afkChannelId;
    std::optional<snowflake> rulesChannelId;
    uint64_t afkTimeout;
    VerificationLevel verificationLevel;
    std::vector<DiscordGuildRole> roles;
    std::vector<DiscordGuildEmoji> emojis;
    std::vector<DiscordGuildSticker> stickers;
    std::optional<std::string> vanityUrlCode;
    std::optional<std::string> description;
    std::optional<std::string> banner;
    std::string preferredLocale;
    std::optional<std::string> publicUpdatesChannelId;
    NsfwLevel nsfwLevel;
    bool premiumProgressBarEnabled;
    std::optional<snowflake> safetyAlertsChannelId;
    uint8_t boostLevel;
public:
    friend class DiscordBot;
    snowflake getId() const;
    std::string getName() const;
    snowflake getOwnerId() const;
    std::optional<snowflake> getAfkChannelId() const;
    std::optional<snowflake> getRulesChannelId() const;
    uint64_t getAfkTimeout() const;
    VerificationLevel getVerificationLevel() const;
    std::vector<DiscordGuildRole> getRoles() const;
    std::vector<DiscordGuildEmoji> getEmojis() const;
    std::vector<DiscordGuildSticker> getStickers() const;
    std::optional<std::string> getVanityUrlCode() const;
    std::optional<std::string> getDescription() const;
    std::optional<std::string> getBanner() const;
    std::string getPreferredLocale() const;
    std::optional<std::string> getPublicUpdatesChannelId() const;
    NsfwLevel getNsfwLevel() const;
    bool getPremiumProgressBarEnabled() const;
    std::optional<snowflake> getSafetyAlertsChannelId() const;
    std::optional<std::string> getIcon() const;
    std::optional<std::string> getIconHash() const;
    std::optional<std::string> getSplash() const;
    uint8_t getBoostLevel() const;
};

class DiscordGuildRole{
    snowflake id;
    std::string name;
    uint32_t color;
    RoleColors colors;
    bool hoist;
    std::optional<std::string> icon;
    std::optional<std::string> unicodeEmoji;
    uint32_t position;
    std::string permissions;
    bool managed;
    bool mentionable;
    uint32_t flags;
public:
    friend class DiscordBot;
    snowflake getId() const;
    std::string getName() const;
    uint32_t getColor() const;
    RoleColors getColors() const;
    bool getHoist() const;
    std::optional<std::string> getIcon() const;
    std::optional<std::string> getUnicodeEmoji() const;
    uint32_t getPosition() const;
    std::string getPermissions() const;
    bool getManaged() const;
    bool getMentionable() const;
    uint32_t getFlags() const;
};

class DiscordGuildSticker{
    snowflake id;
public:
    friend class DiscordBot;
};

class DiscordGuildEmoji{
    snowflake id;
    std::optional<snowflake> packId;
    std::string name;
    std::string description;
    std::string tags;
    uint32_t type;
    uint32_t formatType;
    bool available;
    snowflake guild_id;
public:
    friend class DiscordBot;
};

std::string descriptionVerificationLevel(const VerificationLevel& verification);
#endif