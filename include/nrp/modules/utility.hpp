#ifndef NRP_MODULES_UTILITY_HPP
#define NRP_MODULES_UTILITY_HPP

#include <string>
#include <cstdint>

namespace nrp::modules::utility {

class Utility {
public:
    static std::string generate_uuid();
    static int64_t current_time_millis();
    static std::string trim(const std::string& input);
};

} // namespace nrp::modules::utility

#endif // NRP_MODULES_UTILITY_HPP
