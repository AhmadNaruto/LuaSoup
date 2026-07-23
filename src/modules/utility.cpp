#include "nrp/modules/utility.hpp"
#include <chrono>
#include <random>
#include <sstream>
#include <iomanip>

namespace nrp::modules::utility {

std::string Utility::generate_uuid() {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_int_distribution<uint32_t> dis;

    std::ostringstream ss;
    ss << std::hex << std::setfill('0');
    ss << std::setw(8) << dis(gen) << "-"
       << std::setw(4) << (dis(gen) & 0xFFFF) << "-"
       << std::setw(4) << ((dis(gen) & 0x0FFF) | 0x4000) << "-"
       << std::setw(4) << ((dis(gen) & 0x3FFF) | 0x8000) << "-"
       << std::setw(8) << dis(gen) << std::setw(4) << (dis(gen) & 0xFFFF);

    return ss.str();
}

int64_t Utility::current_time_millis() {
    auto now = std::chrono::system_clock::now();
    return std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()).count();
}

std::string Utility::trim(const std::string& input) {
    size_t first = input.find_first_not_of(" \t\n\r");
    if (first == std::string::npos) return "";
    size_t last = input.find_last_not_of(" \t\n\r");
    return input.substr(first, (last - first + 1));
}

} // namespace nrp::modules::utility
