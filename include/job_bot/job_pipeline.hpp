#pragma once

#include "job_bot/job_listing.hpp"
#include "job_bot/job_source.hpp"
#include "job_bot/job_tracker.hpp"

#include <vector>

namespace job_bot {

// Fetch listings from a source and return only valid IDs not previously seen.
// The tracker is updated as new listings are accepted.
std::vector<JobListing> collectNewJobs(JobSource& source, JobTracker& tracker);

} // namespace job_bot
