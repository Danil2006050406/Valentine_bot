cmake_minimum_required(VERSION 3.10)
project(TgBotProject)

set(CMAKE_CXX_STANDARD 17)

find_package(OpenSSL REQUIRED)

add_executable(bot Valentine.cpp)

target_link_libraries(bot
    TgBot
    OpenSSL::SSL
    OpenSSL::Crypto
)
