#pragma once

#include "job_bot/job_listing.hpp"

#include <string>

namespace job_bot {

// Formats a listing as a concise message suitable for a Discord post preview.
std::string formatJobAlert(const JobListing& job);

} // namespace job_bot
