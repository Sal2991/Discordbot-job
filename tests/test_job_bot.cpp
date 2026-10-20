#include "job_bot/job_formatter.hpp"
#include "job_bot/job_tracker.hpp"

#include <cassert>
#include <filesystem>
#include <string>

int main() {
    const job_bot::JobListing listing{
        "intern-001",
        "Software Engineering Intern",
        "Example Company",
        "https://example.com/jobs/intern-001"
    };

    job_bot::JobTracker tracker;
    assert(tracker.getJobCount() == 0);
    assert(tracker.addJob(listing));
    assert(tracker.getJobCount() == 1);
    assert(!tracker.addJob(listing));
    assert(tracker.getJobCount() == 1);

    auto missingId = listing;
    missingId.id = "";
    assert(!tracker.addJob(missingId));

    auto missingTitle = listing;
    missingTitle.title = " \t";
    assert(!tracker.addJob(missingTitle));

    auto missingCompany = listing;
    missingCompany.company = "";
    assert(!tracker.addJob(missingCompany));

    auto missingUrl = listing;
    missingUrl.url = "";
    assert(!tracker.addJob(missingUrl));

    auto multilineId = listing;
    multilineId.id = "first\nsecond";
    assert(!tracker.addJob(multilineId));

    const std::string expected =
        "📌 **Software Engineering Intern** — Example Company\n"
        "Apply: https://example.com/jobs/intern-001";
    assert(job_bot::formatJobAlert(listing) == expected);

    const auto storagePath =
        std::filesystem::temp_directory_path() / "discord_job_bot_seen_ids_test.txt";
    const std::string path = storagePath.string();

    assert(tracker.saveSeenIds(path));

    job_bot::JobTracker restored;
    assert(restored.loadSeenIds(path));
    assert(restored.getJobCount() == 1);
    assert(!restored.addJob(listing));

    std::filesystem::remove(storagePath);
    assert(!restored.loadSeenIds(path));

    return 0;
}
