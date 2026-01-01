#ifndef GUILD_JSON_H
#define GUILD_JSON_H
#include "guild.h"
#include <nlohmann/json.hpp>

using json = nlohmann::json;


class GuildJsonDeserializer{
public:
    static void toDiscordRole(const json &j, DiscordGuildRole &role);
    static void toDiscordGuild(const json& j, DiscordGuild& guild);
};

void from_json(const json &j, DiscordGuildRole &role);
void from_json(const json& j, DiscordGuild& guild);

#endif