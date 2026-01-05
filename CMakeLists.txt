cmake_minimum_required(VERSION 3.12)
project(discordlib VERSION 0.1)
add_executable(${PROJECT_NAME} 
    main.cpp
    guild/guild.cpp
    guild/guild_json.cpp
    guild/channel/channel.cpp
    guild/channel/channel_json.cpp
    https/https.cpp
    bot/bot.cpp
    snowflake/snowflake.cpp
    user/user.cpp
    user/user_json.cpp
    utils/utils.cpp
)

if (WIN32 AND NOT Boost_FOUND)
    set(BOOST_ROOT "E:/Boost/")
endif()

target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/bot
    ${CMAKE_CURRENT_SOURCE_DIR}/guild
    ${CMAKE_CURRENT_SOURCE_DIR}/https
    ${CMAKE_CURRENT_SOURCE_DIR}/snowflake
    ${CMAKE_CURRENT_SOURCE_DIR}/user
    ${CMAKE_CURRENT_SOURCE_DIR}/utils
    ${CMAKE_CURRENT_SOURCE_DIR}/libs/json/include
)

find_package(Boost 1.90 REQUIRED)
find_package(OpenSSL REQUIRED)

target_link_libraries(${PROJECT_NAME} PRIVATE
    OpenSSL::SSL
    OpenSSL::Crypto
    Boost::boost
    ws2_32
    crypt32
)