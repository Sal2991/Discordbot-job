# Discord Job Bot

I'm making a small bot that can check for new internship postings and send them to Discord. I'm using it to practice C++ and learn how to work with APIs and save data.

## What works so far

- A simple struct for a job listing
- A small tracker that remembers job IDs during one run
- A local example that shows a duplicate being skipped

## Still to do

- Connect to real internship listing sources
- Decide how to store seen job IDs between runs
- Add Discord message delivery
- Add config for API keys and channel settings
- Handle network errors and rate limits

Right now this is just the starting logic. It does not fetch real listings or connect to Discord yet.
