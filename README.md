# Discord Job Bot

An early C++23 prototype for tracking internship listings and preparing concise, Discord-style alert previews. It currently runs locally with sample data; it does **not** connect to Discord or fetch live job listings yet.

## Current features

- A `JobListing` data structure with an ID, title, company, and URL
- In-memory tracking of job IDs, with duplicate detection
- Optional persistence of seen IDs to a newline-delimited text file, so duplicate detection survives restarts
- Basic validation that a listing has a non-blank ID, title, company, and URL
- A small formatter that produces a readable alert preview using Discord Markdown
- CMake build and a CTest unit-test target covering validation, formatting, and persistence

## Build and run

Requirements: CMake 3.20+ and a compiler with C++23 support.

```sh
cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug
cmake --build build --parallel
ctest --test-dir build --output-on-failure
./build/discord_job_bot
```

The demo uses sample data and prints an alert preview. It reads and writes `seen_job_ids.txt` in the current working directory. On first run, the file may not exist; it is created when the demo saves its tracked IDs. The demo makes no network requests.

## Not implemented yet

- Discord authentication, bot commands, channel configuration, or message delivery
- Fetching listings from job APIs or websites
- Structured storage, migrations, or cross-process locking
- Network error handling, rate-limit handling, and secret configuration

The text-file persistence is intentionally a small prototype; it is not designed for concurrent processes or large datasets.
