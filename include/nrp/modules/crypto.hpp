#ifndef NRP_MODULES_CRYPTO_HPP
#define NRP_MODULES_CRYPTO_HPP

#include <string>
#include <vector>
#include <cstdint>

namespace nrp::modules::crypto {

class Crypto {
public:
    static std::string sha256(const std::string& input);
    static std::string md5(const std::string& input);
    static std::string hmac_sha256(const std::string& key, const std::string& input);
};

} // namespace nrp::modules::crypto

#endif // NRP_MODULES_CRYPTO_HPP
