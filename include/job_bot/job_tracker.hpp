#pragma once

#include "job_bot/job_listing.hpp"

#include <cstddef>
#include <string>
#include <unordered_set>

namespace job_bot {

class JobTracker {
public:
    bool addJob(const JobListing& job);
    std::size_t getJobCount() const;

    // Persist one job ID per line. Returns false if the file cannot be read/written.
    bool loadSeenIds(const std::string& path);
    bool saveSeenIds(const std::string& path) const;

private:
    std::unordered_set<std::string> seenJobIds;
};

} // namespace job_bot
