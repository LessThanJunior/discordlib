#ifndef DISCORD_USER_H
#define DISCORD_USER_H
#include <string>
#include "../snowflake.h"

enum class NitroType{
    NONE,
    NITRO,
    NITRO_CLASSIC,
    NITRO_BASIC
};

class DiscordUser{
    snowflake id;
    std::string username;
    std::string discriminator;
    std::string globalName;
    std::string avatar;
    bool bot = 0;
    bool system = 0;
    bool mfaEnabled = 0;
    std::string banner;
    uint32_t accentColor;
    std::string locale;
    bool verified = 0;
    std::string email;
    uint32_t flags;
    NitroType nitroType;
    uint32_t publicFlags;
public:
    friend class UserJsonDeserializer;
    snowflake getId() const;
    std::string getUsername() const;
    [[deprecated]]std::string getDiscriminator() const;
    std::string getGlobalName() const;
    std::string getAvatar() const;
    bool getBot() const;
    bool getSystem() const;
    bool getMfaEnabled() const;
    std::string getBanner() const;
    uint32_t getAccentColor() const;
    std::string getLocale() const;
    bool getVerified() const;
    std::string getEmail() const;
    uint32_t getFlags() const;
    NitroType getNitroType() const;
    uint32_t getPublicFlags() const;
};
#endif