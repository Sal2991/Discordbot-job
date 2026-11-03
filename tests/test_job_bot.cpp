#include "job_bot/job_formatter.hpp"
#include "job_bot/job_pipeline.hpp"
#include "job_bot/job_source.hpp"
#include "job_bot/job_tracker.hpp"

#include <cassert>
#include <filesystem>
#include <string>
#include <utility>
#include <vector>

namespace {

class FakeJobSource final : public job_bot::JobSource {
public:
    explicit FakeJobSource(std::vector<job_bot::JobListing> listings)
        : listings_(std::move(listings)) {}

    std::vector<job_bot::JobListing> fetchJobs() override {
        return listings_;
    }

private:
    std::vector<job_bot::JobListing> listings_;
};

} // namespace

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

    // The source abstraction lets the pipeline be tested without network access.
    const job_bot::JobListing secondListing{
        "intern-002",
        "C++ Developer Intern",
        "Sample Systems",
        "https://example.com/jobs/intern-002"
    };
    FakeJobSource source({listing, secondListing, listing, missingTitle});
    const auto newJobs = job_bot::collectNewJobs(source, tracker);
    assert(newJobs.size() == 1);
    assert(newJobs.front().id == "intern-002");
    assert(tracker.getJobCount() == 2);

    FakeJobSource unchangedSource({listing, secondListing});
    assert(job_bot::collectNewJobs(unchangedSource, tracker).empty());

    const auto storagePath =
        std::filesystem::temp_directory_path() / "discord_job_bot_seen_ids_test.txt";
    const std::string path = storagePath.string();

    assert(tracker.saveSeenIds(path));

    job_bot::JobTracker restored;
    assert(restored.loadSeenIds(path));
    assert(restored.getJobCount() == 2);
    assert(!restored.addJob(listing));
    assert(!restored.addJob(secondListing));

    std::filesystem::remove(storagePath);
    assert(!restored.loadSeenIds(path));

    return 0;
}
