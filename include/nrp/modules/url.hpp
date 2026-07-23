#ifndef NRP_MODULES_URL_HPP
#define NRP_MODULES_URL_HPP

#include <string>
#include <unordered_map>

namespace nrp::modules::url {

struct URL {
    std::string scheme;
    std::string host;
    int port{0};
    std::string path;
    std::string query;
    std::string hash;
    std::unordered_map<std::string, std::string> query_params;

    static URL parse(const std::string& url_str);
    std::string to_string() const;

    static std::string encode(const std::string& str);
    static std::string decode(const std::string& str);
};

} // namespace nrp::modules::url

#endif // NRP_MODULES_URL_HPP
