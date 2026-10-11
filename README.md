# Discord Job Bot

An early C++23 prototype for tracking internship listings and preparing concise, Discord-style alert previews. It currently runs locally with sample data; it does **not** connect to Discord or fetch live job listings yet.

## Current features

- A `JobListing` data structure with an ID, title, company, and URL
- In-memory tracking of job IDs, with duplicate detection during one run
- Basic validation that a listing has a non-blank ID, title, company, and URL
- A small formatter that produces a readable alert preview using Discord Markdown
- CMake build and a CTest unit-test target

## Build and run

Requirements: CMake 3.20+ and a compiler with C++23 support.

```sh
cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug
cmake --build build --parallel
ctest --test-dir build --output-on-failure
./build/discord_job_bot
```

The demo uses a sample listing and prints an alert preview to the terminal. It makes no network requests.

## Not implemented yet

- Discord authentication, bot commands, channel configuration, or message delivery
- Fetching listings from job APIs or websites
- Persistent storage of seen IDs between runs
- Network error handling, rate-limit handling, and secret configuration

Job IDs are currently remembered only in memory for the lifetime of the tracker.
