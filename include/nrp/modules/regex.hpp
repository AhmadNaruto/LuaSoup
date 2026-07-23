#ifndef NRP_MODULES_REGEX_HPP
#define NRP_MODULES_REGEX_HPP

#include <string>
#include <vector>
#include <regex>

namespace nrp::modules::regex {

class Regex {
private:
    std::regex pattern_;
    std::string raw_pattern_;

public:
    explicit Regex(const std::string& pattern_str);

    bool test(const std::string& input) const;
    std::vector<std::string> match(const std::string& input) const;
    std::string replace(const std::string& input, const std::string& replacement) const;
    std::vector<std::string> split(const std::string& input) const;
};

} // namespace nrp::modules::regex

#endif // NRP_MODULES_REGEX_HPP
