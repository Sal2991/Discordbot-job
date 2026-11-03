#include "job_bot/job_formatter.hpp"
#include "job_bot/job_pipeline.hpp"
#include "job_bot/job_source.hpp"
#include "job_bot/job_tracker.hpp"

#include <iostream>
#include <vector>

namespace {

class SampleJobSource final : public job_bot::JobSource {
public:
    std::vector<job_bot::JobListing> fetchJobs() override {
        return {
            {
                "intern-001",
                "Software Engineering Intern",
                "Example Company",
                "https://example.com/jobs/intern-001"
            },
            {
                "intern-002",
                "C++ Developer Intern",
                "Sample Systems",
                "https://example.com/jobs/intern-002"
            }
        };
    }
};

} // namespace

int main() {
    job_bot::JobTracker tracker;
    const char* storagePath = "seen_job_ids.txt";

    // A missing first-run file is expected; persistence becomes available after saving.
    tracker.loadSeenIds(storagePath);

    SampleJobSource source;
    const std::vector<job_bot::JobListing> newJobs =
        job_bot::collectNewJobs(source, tracker);

    if (newJobs.empty()) {
        std::cout << "No new listings found.\n";
    }

    for (const job_bot::JobListing& job : newJobs) {
        std::cout << "Preview of a new job alert:\n\n"
                  << job_bot::formatJobAlert(job) << "\n\n";
    }

    if (!tracker.saveSeenIds(storagePath)) {
        std::cerr << "Warning: could not save seen job IDs to "
                  << storagePath << '\n';
        return 1;
    }

    std::cout << "New listings: " << newJobs.size() << '\n'
              << "Tracked listings: " << tracker.getJobCount() << '\n';
    return 0;
}
