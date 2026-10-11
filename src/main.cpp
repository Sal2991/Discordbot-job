#include "job_bot/job_formatter.hpp"
#include "job_bot/job_tracker.hpp"

#include <iostream>

int main() {
    job_bot::JobTracker tracker;

    const job_bot::JobListing firstJob{
        "intern-001",
        "Software Engineering Intern",
        "Example Company",
        "https://example.com/jobs/intern-001"
    };

    if (tracker.addJob(firstJob)) {
        std::cout << "Preview of a new job alert:\n\n"
                  << job_bot::formatJobAlert(firstJob) << '\n';
    }

    if (!tracker.addJob(firstJob)) {
        std::cout << "\nSkipped a listing we have already seen.\n";
    }

    std::cout << "Tracked listings this run: " << tracker.getJobCount() << '\n';
    return 0;
}
