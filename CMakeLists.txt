cmake_minimum_required(VERSION 3.20)

project(discord_job_bot VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(job_bot_core
    src/job_tracker.cpp
    src/job_formatter.cpp
)
target_include_directories(job_bot_core PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

add_executable(discord_job_bot src/main.cpp)
target_link_libraries(discord_job_bot PRIVATE job_bot_core)

include(CTest)
if(BUILD_TESTING)
    add_executable(job_bot_tests tests/test_job_bot.cpp)
    target_link_libraries(job_bot_tests PRIVATE job_bot_core)
    add_test(NAME job_bot_tests COMMAND job_bot_tests)
endif()
