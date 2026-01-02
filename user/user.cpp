#include "user.h"

snowflake DiscordUser::getId() const {return id;}
std::string DiscordUser::getUsername() const {return username;}
std::string DiscordUser::getDiscriminator() const {return discriminator;}
std::string DiscordUser::getGlobalName() const {return globalName;}
std::string DiscordUser::getAvatar() const {return avatar;}
bool DiscordUser::getBot() const {return bot;}
bool DiscordUser::getSystem() const {return system;}
bool DiscordUser::getMfaEnabled() const {return mfaEnabled;}
std::string DiscordUser::getBanner() const {return banner;}
uint32_t DiscordUser::getAccentColor() const {return accentColor;}
std::string DiscordUser::getLocale() const {return locale;}
bool DiscordUser::getVerified() const {return verified;}
std::string DiscordUser::getEmail() const {return email;}
uint32_t DiscordUser::getFlags() const {return flags;}
NitroType DiscordUser::getNitroType() const {return nitroType;}
uint32_t DiscordUser::getPublicFlags() const {return publicFlags;}