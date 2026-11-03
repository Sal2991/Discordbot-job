#pragma once

#include "job_bot/job_listing.hpp"

#include <vector>

namespace job_bot {

// Implementations can fetch listings from an API, website, or local fixture.
// Keeping acquisition behind this interface makes the pipeline independently testable.
class JobSource {
public:
    virtual ~JobSource() = default;
    virtual std::vector<JobListing> fetchJobs() = 0;
};

} // namespace job_bot
