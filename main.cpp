#include "snowflake.h"
#include <iostream>
#include "guild/guild.h"
#include <nlohmann/json.hpp>
#include "bot.h"
#include "https/https.h"
#include "windows.h"
using json = nlohmann::json;

const std::string getToken(){
    auto token = std::getenv("DISCORD_TOKEN");
    return std::string(token);
}

const std::map<std::string, std::string> http_params{
    {"User-Agent", "DiscordBot(discordlib, 0.1"},
    {"Authorization", "Bot " + getToken()}
};

std::string getValue(const std::optional<std::string>& value){
    return value.has_value() ? value.value() : "";
}


void descriptionRole(const DiscordGuildRole& role){
    std::cout << "Role ID: " << role.getId() << "\n"
              << "Role Name: " << role.getName() << "\n"
              << "Role Permissions: " << role.getPermissions() << "\n"
              << "Role Mentionable: " << role.getMentionable() << "\n"
              << "Role Color: " << role.getColor() << "\n"
              << "Role Icon: " << role.getIcon() << "\n";
}

void descriptionChannel(const std::unique_ptr<DiscordChannel>& channel){
    if(channel->getType() == ChannelType::DM){
        auto dmChannel = dynamic_cast<DiscordDmChannel*>(channel.get());
        std::cout << "Channel ID: " << dmChannel->getId() << "\n";
    }

    if(isGuild(channel->getType())){
        std::cout << "GuildId: " << channel->getGuildId() << "\n";
        std::cout << "ParentId: " << channel->getParentId() << "\n";
        std::cout << "Position: " << channel->getPosition() << "\n";
        std::cout << "Timeout: " << channel->getTimeout() << "\n";
        std::cout << "LastMessageId: " << channel->getLastMessageId() << "\n";
        std::cout << "Name: " << channel->getName() << "\n";
        std::cout << "Nsfw: " << channel->getNsfw() << "\n";
    }
    

    if(channel->getType() == ChannelType::GUILD_VOICE){
        auto voiceChannel = dynamic_cast<DiscordVoiceChannel*>(channel.get());
        std::cout << "Bitrate: " << voiceChannel->getBitrate() << "\n";
        std::cout << "UserLimit: " << voiceChannel->getUserLimit() << "\n";
        std::cout << "Rtc Region: " << voiceChannel->getRtcRegion() << "\n";
    }
}

int main(int argc, char** argv){
    SetConsoleOutputCP(65001);

    // BOM bytes
    std::cout << "\xEF\xBB\xBF";

    DiscordBot bot(http_params);
    std::cout << "====User Info====\n";

    const auto user = bot.getDiscordUser(370911037441966080);
    std::cout << "User ID: " << user.getId() << "\n";
    std::cout << "Username: " << user.getUsername() << "\n";
    std::cout << "Is bot: " << user.getBot() << "\n";
    std::cout << "User email: " << user.getEmail() << "\n";
    std::cout << "Verified: " << user.getVerified() << "\n";


    std::cout << "\n\n====Guild Info====\n";

    const auto guild = bot.getDiscordGuild(799333274861174876);
    
    const auto afk_channel_id = guild.getAfkChannelId();
    const auto guild_id = guild.getId();
    const auto rules_channel_id = guild.getRulesChannelId();

    std::cout << "Afk Timeout: " << guild.getAfkTimeout() << "\n";
    std::cout << "Afk ChannelId: " << afk_channel_id << "\n";
    std::cout << "Boost level: " << (uint16_t)guild.getBoostLevel() << "\n";
    std::cout << "Guild id: " << guild_id << "\n";
    std::cout << "Guild name " << guild.getName() << "\n";
    std::cout << "Rules channel id: " << rules_channel_id << "\n";
    std::cout << "Verification level: " << descriptionVerificationLevel(guild.getVerificationLevel()) << "\n";
    std::cout << "Banner: " << guild.getBanner() << "\n";
    std::cout << "Preferred locale: " << guild.getPreferredLocale() << "\n";
    std::cout << "Description: " << guild.getDescription() << "\n";
    std::cout << "Guild icon: " << guild.getIcon() << "\n";
    std::cout << "Guild icon hash: " << guild.getIconHash() << "\n";
    std::cout << "Safety Alerts Channel: " << guild.getSafetyAlertsChannelId() << "\n";

    std::cout << "\n\n=====Description Role======\n";
    const auto roles = guild.getRoles();
    for(const auto& role : roles){
        descriptionRole(role);
        std::cout << "\n";
    }
    auto channels = bot.getDiscordChannels(bot.getDiscordGuilds()[0].getId());
    std::cout << "====Channel Data====\n\n";
    
    for(const auto& ch : channels){
        descriptionChannel(std::move(ch));
        std::cout << "\n";
    }
}