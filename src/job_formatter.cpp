#include "job_bot/job_formatter.hpp"

namespace job_bot {

std::string formatJobAlert(const JobListing& job) {
    return "📌 **" + job.title + "** — " + job.company + "\n"
           "Apply: " + job.url;
}

} // namespace job_bot
