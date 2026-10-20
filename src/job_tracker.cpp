#include "job_bot/job_tracker.hpp"

#include <fstream>
#include <string>

namespace job_bot {
namespace {

bool hasText(const std::string& value) {
    return value.find_first_not_of(" \t\n\r") != std::string::npos;
}

bool isComplete(const JobListing& job) {
    return hasText(job.id) && hasText(job.title) &&
           hasText(job.company) && hasText(job.url) &&
           job.id.find_first_of("\r\n") == std::string::npos;
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

bool JobTracker::loadSeenIds(const std::string& path) {
    std::ifstream input(path);
    if (!input) {
        return false;
    }

    std::unordered_set<std::string> loadedIds;
    std::string id;
    while (std::getline(input, id)) {
        if (hasText(id) && id.find_first_of("\r\n") == std::string::npos) {
            loadedIds.insert(id);
        }
    }

    if (input.bad()) {
        return false;
    }

    seenJobIds.insert(loadedIds.begin(), loadedIds.end());
    return true;
}

bool JobTracker::saveSeenIds(const std::string& path) const {
    std::ofstream output(path, std::ios::trunc);
    if (!output) {
        return false;
    }

    for (const std::string& id : seenJobIds) {
        output << id << '\n';
        if (!output) {
            return false;
        }
    }

    return output.good();
}

} // namespace job_bot
