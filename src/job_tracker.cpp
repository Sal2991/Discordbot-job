#include "job_bot/job_tracker.hpp"

namespace job_bot {

bool JobTracker::addJob(const JobListing& job) {
    if (job.id.empty()) {
        return false;
    }

    return seenJobIds.insert(job.id).second;
}

std::size_t JobTracker::getJobCount() const {
    return seenJobIds.size();
}

} // namespace job_bot
