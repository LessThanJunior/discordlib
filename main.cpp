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


int main(){
    SetConsoleOutputCP(65001);
    std::cout << "\xEF\xBB\xBF";

    DiscordBot bot(http_params);
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

    std::cout << "\n====Json Data====" << "\n";
    std::cout << bot.getJson().dump(4);
    
}