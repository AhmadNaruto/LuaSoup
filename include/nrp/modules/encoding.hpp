#ifndef NRP_MODULES_ENCODING_HPP
#define NRP_MODULES_ENCODING_HPP

#include <string>
#include <vector>
#include <cstdint>

namespace nrp::modules::encoding {

class Encoding {
public:
    static std::string to_utf8(const std::string& input);
    static std::string to_base64(const std::string& input);
    static std::string from_base64(const std::string& input);
    static std::string to_hex(const std::string& input);
    static std::string from_hex(const std::string& input);
};

} // namespace nrp::modules::encoding

#endif // NRP_MODULES_ENCODING_HPP
