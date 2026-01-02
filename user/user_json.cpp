#include "user_json.h"
#include "../utils/utils.h"

void UserJsonDeserializer::toDiscordUser(const json &j, DiscordUser &user){
    if(hasValue(j, "accent_color"))
        j.at("accent_color").get_to(user.accentColor);

    if(hasValue(j, "avatar"))
        j.at("avatar").get_to(user.avatar);

    if(hasValue(j, "banner"))
        j.at("banner").get_to(user.banner);

    if(hasValue(j, "bot"))
        j.at("bot").get_to(user.bot);

    if(hasValue(j, "discriminator"))
        j.at("discriminator").get_to(user.discriminator);

    if(hasValue(j, "email"))
        j.at("email").get_to(user.email);

    if(hasValue(j, "flags"))
        j.at("flags").get_to(user.flags);

    if(hasValue(j, "username"))
        j.at("username").get_to(user.username);
    
    if(hasValue(j, "locale"))
        j.at("locale").get_to(user.locale);

    if(hasValue(j, "global_name"))
        j.at("global_name").get_to(user.globalName);
    
    if(hasValue(j, "nitro_type"))
        j.at("nitro_type").get_to(user.nitroType);
    
    if(hasValue(j, "mfa_enabled"))
        j.at("mfa_enabled").get_to(user.mfaEnabled);

    if(hasValue(j, "system"))
        j.at("system").get_to(user.system);

    if(hasValue(j, "verified"))
        j.at("verified").get_to(user.verified);
    
    if(hasValue(j, "id"))
        user.id = j.at("id").get<std::string>();
}

void from_json(const json &j, DiscordUser &user){
    UserJsonDeserializer::toDiscordUser(j, user);
}