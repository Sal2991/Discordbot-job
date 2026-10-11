#include "job_bot/job_formatter.hpp"
#include "job_bot/job_tracker.hpp"

#include <cassert>
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

    const std::string expected =
        "📌 **Software Engineering Intern** — Example Company\n"
        "Apply: https://example.com/jobs/intern-001";
    assert(job_bot::formatJobAlert(listing) == expected);
    return 0;
}
