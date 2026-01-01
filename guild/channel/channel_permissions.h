#ifndef CHANNEL_PERMISSIONS_H
#define CHANNEL_PERMISSIONS_H
#include <string>

enum class PermissionType{
    ROLE,
    MEMBER
};

class PermissionOverwrite{
    snowflake id;
    PermissionType type;
    std::string allow;
    std::string deny;
};
#endif