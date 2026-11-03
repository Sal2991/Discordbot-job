#include "job_bot/job_pipeline.hpp"

namespace job_bot {

std::vector<JobListing> collectNewJobs(JobSource& source, JobTracker& tracker) {
    std::vector<JobListing> newJobs;

    for (const JobListing& job : source.fetchJobs()) {
        if (tracker.addJob(job)) {
            newJobs.push_back(job);
        }
    }

    return newJobs;
}

} // namespace job_bot
