#pragma once

#include "job_bot/job_listing.hpp"

#include <string>
#include <unordered_set>

namespace job_bot {

class JobTracker {
public:
    bool addJob(const JobListing& job);
    std::size_t getJobCount() const;

private:
    std::unordered_set<std::string> seenJobIds;
};

} // namespace job_bot
