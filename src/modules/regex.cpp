#include "nrp/modules/regex.hpp"

namespace nrp::modules::regex {

Regex::Regex(const std::string& pattern_str) : pattern_(pattern_str), raw_pattern_(pattern_str) {}

bool Regex::test(const std::string& input) const {
    return std::regex_search(input, pattern_);
}

std::vector<std::string> Regex::match(const std::string& input) const {
    std::smatch matches;
    std::vector<std::string> res;
    if (std::regex_search(input, matches, pattern_)) {
        for (const auto& m : matches) {
            res.push_back(m.str());
        }
    }
    return res;
}

std::string Regex::replace(const std::string& input, const std::string& replacement) const {
    return std::regex_replace(input, pattern_, replacement);
}

std::vector<std::string> Regex::split(const std::string& input) const {
    std::sregex_token_iterator iter(input.begin(), input.end(), pattern_, -1);
    std::sregex_token_iterator end;
    std::vector<std::string> res;
    for (; iter != end; ++iter) {
        res.push_back(*iter);
    }
    return res;
}

} // namespace nrp::modules::regex
