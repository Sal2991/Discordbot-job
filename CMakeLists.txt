cmake_minimum_required(VERSION 3.20)

project(discord_job_bot VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(discord_job_bot
    src/main.cpp
    src/job_tracker.cpp
)

target_include_directories(discord_job_bot PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)
