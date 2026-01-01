#ifndef CHANNEL_JSON_H
#define CHANNEL_JSON_H
#include <nlohmann/json.hpp>
#include "channel.h"

using json = nlohmann::json;

class ChannelJsonDeserializer{
public:
    static void toDiscordVoiceChannel(const json &j, DiscordVoiceChannel &channel);
    static void toDiscordChannel(const json &j, DiscordChannel &channel);
    static void toDiscordDmChannel(const json &j, DiscordDmChannel &channel);
};

void from_json(const json &j, DiscordChannel &channel);
void from_json(const json &j, DiscordVoiceChannel &channel);
void from_json(const json &j, DiscordDmChannel &channel);
#endif