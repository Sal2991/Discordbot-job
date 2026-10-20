#include "job_bot/job_formatter.hpp"
#include "job_bot/job_tracker.hpp"

#include <iostream>

int main() {
    job_bot::JobTracker tracker;
    const char* storagePath = "seen_job_ids.txt";

    // A missing first-run file is expected; persistence becomes available after saving.
    tracker.loadSeenIds(storagePath);

    const job_bot::JobListing firstJob{
        "intern-001",
        "Software Engineering Intern",
        "Example Company",
        "https://example.com/jobs/intern-001"
    };

    if (tracker.addJob(firstJob)) {
        std::cout << "Preview of a new job alert:\n\n"
                  << job_bot::formatJobAlert(firstJob) << '\n';
    } else {
        std::cout << "Skipped a listing we have already seen.\n";
    }

    if (!tracker.saveSeenIds(storagePath)) {
        std::cerr << "Warning: could not save seen job IDs to "
                  << storagePath << '\n';
        return 1;
    }

    std::cout << "Tracked listings: " << tracker.getJobCount() << '\n';
    return 0;
}
