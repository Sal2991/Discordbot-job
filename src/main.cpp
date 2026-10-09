#include "job_bot/job_tracker.hpp"

#include <iostream>

int main() {
    job_bot::JobTracker tracker;

    job_bot::JobListing firstJob{
        "intern-001",
        "Software Engineering Intern",
        "Example Company",
        "https://example.com/jobs/intern-001"
    };

    job_bot::JobListing sameJob = firstJob;

    if (tracker.addJob(firstJob)) {
        std::cout << "Added: " << firstJob.title << '\n';
    }

    if (!tracker.addJob(sameJob)) {
        std::cout << "Already saw this job: " << sameJob.title << '\n';
    }

    std::cout << "Saved job count: " << tracker.getJobCount() << '\n';
    return 0;
}
