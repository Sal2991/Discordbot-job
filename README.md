# Discord Job Bot

An early C++23 prototype for tracking internship listings and, eventually, delivering new listings to Discord. The current repository demonstrates the tracking logic only; it is not yet a working Discord bot.

## Implemented

- A `JobListing` data structure containing an ID, title, company, and URL
- An in-memory `JobTracker` that records non-empty job IDs
- Duplicate detection for IDs during one program run
- A demo that adds one sample listing and skips a second listing with the same ID

## Build and run

Requirements: CMake 3.20+ and a compiler with C++23 support.

```sh
cmake -S . -B build
cmake --build build --config Release
./build/discord_job_bot
```

## Not implemented yet

- Fetching listings from real job APIs or websites
- Discord bot authentication, message delivery, or channel configuration
- Persistent storage of seen IDs between runs
- Network error handling, rate-limit handling, and configuration for secrets

The example uses sample data and does not make network requests. Job IDs are remembered only in memory for the lifetime of the tracker.
