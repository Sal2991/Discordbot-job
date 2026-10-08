cmake_minimum_required(VERSION 3.20)

project(discord_job_bot LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp")
    add_executable(discord_job_bot src/main.cpp)
else()
    message(STATUS "Add src/main.cpp when you're ready to start the bot.")
endif()
