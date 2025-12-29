#include "guild.h"
#include "../https/https.h"
#include <nlohmann/json.hpp>
#include <iostream>
#include <string>

using json = nlohmann::json;

// DiscordGuild

snowflake DiscordGuild::getId() const {return id;}
std::string DiscordGuild::getName() const {return name;}
snowflake DiscordGuild::getOwnerId() const {return ownerId;}
std::optional<snowflake> DiscordGuild::getAfkChannelId() const {return afkChannelId;}
std::optional<snowflake> DiscordGuild::getRulesChannelId() const {return rulesChannelId;}
uint64_t DiscordGuild::getAfkTimeout() const {return afkTimeout;}
VerificationLevel DiscordGuild::getVerificationLevel() const {return verificationLevel;}
std::vector<DiscordGuildRole> DiscordGuild::getRoles() const {return roles;}
std::vector<DiscordGuildEmoji> DiscordGuild::getEmojis() const {return emojis;}
std::vector<DiscordGuildSticker> DiscordGuild::getStickers() const {return stickers;}
uint8_t DiscordGuild::getBoostLevel() const {return boostLevel;}
std::optional<std::string> DiscordGuild::getVanityUrlCode() const {return vanityUrlCode;}
std::optional<std::string> DiscordGuild::getDescription() const {return description;}
std::optional<std::string> DiscordGuild::getBanner() const {return banner;}
std::string DiscordGuild::getPreferredLocale() const {return preferredLocale;};
std::optional<std::string> DiscordGuild::getPublicUpdatesChannelId() const {return publicUpdatesChannelId;}
NsfwLevel DiscordGuild::getNsfwLevel() const {return nsfwLevel;}
bool DiscordGuild::getPremiumProgressBarEnabled() const {return premiumProgressBarEnabled;}
std::optional<snowflake> DiscordGuild::getSafetyAlertsChannelId() const {return safetyAlertsChannelId;}
std::optional<std::string> DiscordGuild::getIcon() const {return icon;}
std::optional<std::string> DiscordGuild::getIconHash() const {return iconHash;}
std::optional<std::string> DiscordGuild::getSplash() const {return splash;}


// DiscordGuildRole

snowflake DiscordGuildRole::getId() const {return id;}
std::string DiscordGuildRole::getName() const {return name;}
uint32_t DiscordGuildRole::getColor() const {return color;}
RoleColors DiscordGuildRole::getColors() const {return colors;}
bool DiscordGuildRole::getHoist() const {return hoist;}
std::optional<std::string> DiscordGuildRole::getIcon() const {return icon;}
std::optional<std::string> DiscordGuildRole::getUnicodeEmoji() const {return unicodeEmoji;}
uint32_t DiscordGuildRole::getPosition() const {return position;}
std::string DiscordGuildRole::getPermissions() const {return permissions;}
bool DiscordGuildRole::getManaged() const {return managed;}
bool DiscordGuildRole::getMentionable() const {return mentionable;}
uint32_t DiscordGuildRole::getFlags() const {return flags;}



std::string descriptionVerificationLevel(const VerificationLevel& verification){
    switch (verification)
    {
        case VerificationLevel::NONE:
            return "unrestricted";
            break;
        case VerificationLevel::LOW:
            return "must have verified email on account";
            break;
        case VerificationLevel::MEDIUM:
            return "must be registered on Discord for longer than 5 minutes";
            break;
        case VerificationLevel::HIGH:
            return "must be a member of the server for longer than 10 minutes";
            break;
        case VerificationLevel::VERY_HIGH:
            return "must have a verified phone number";
            break;
        default:
            return "not valid verification level";
            break;
    }
}