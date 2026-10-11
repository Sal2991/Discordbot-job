#include "job_bot/job_tracker.hpp"

namespace job_bot {
namespace {

bool hasText(const std::string& value) {
    return value.find_first_not_of(" \t\n\r") != std::string::npos;
}

bool isComplete(const JobListing& job) {
    return hasText(job.id) && hasText(job.title) &&
           hasText(job.company) && hasText(job.url);
}

} // namespace

bool JobTracker::addJob(const JobListing& job) {
    if (!isComplete(job)) {
        return false;
    }

    return seenJobIds.insert(job.id).second;
}

std::size_t JobTracker::getJobCount() const {
    return seenJobIds.size();
}

} // namespace job_bot
