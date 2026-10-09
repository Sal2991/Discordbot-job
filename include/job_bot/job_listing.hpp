#pragma once

#include <string>

namespace job_bot {

struct JobListing {
    std::string id;
    std::string title;
    std::string company;
    std::string url;
};

} // namespace job_bot
