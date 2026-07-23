#ifndef NRP_MODULES_CRYPTO_HPP
#define NRP_MODULES_CRYPTO_HPP

#include <string>
#include <vector>
#include <cstdint>

namespace nrp::modules::crypto {

enum class AesMode { ECB, CBC, CTR, GCM };
enum class AesPadding { PKCS7, NoPadding };

class Crypto {
public:
    // Hash Algorithms (specs/090_crypto_module.md)
    static std::string md5(const std::string& input);
    static std::string sha1(const std::string& input);
    static std::string sha224(const std::string& input);
    static std::string sha256(const std::string& input);
    static std::string sha384(const std::string& input);
    static std::string sha512(const std::string& input);

    // HMAC Algorithms
    static std::string hmac_sha1(const std::string& key, const std::string& input);
    static std::string hmac_sha256(const std::string& key, const std::string& input);
    static std::string hmac_sha512(const std::string& key, const std::string& input);

    // AES Symmetric Encryption (AES-128, AES-192, AES-256)
    static std::vector<uint8_t> aes_encrypt(const std::vector<uint8_t>& key,
                                           const std::vector<uint8_t>& iv,
                                           const std::vector<uint8_t>& data,
                                           AesMode mode = AesMode::CBC,
                                           AesPadding padding = AesPadding::PKCS7);

    static std::vector<uint8_t> aes_decrypt(const std::vector<uint8_t>& key,
                                           const std::vector<uint8_t>& iv,
                                           const std::vector<uint8_t>& data,
                                           AesMode mode = AesMode::CBC,
                                           AesPadding padding = AesPadding::PKCS7);

    // Secure Random Generator
    static std::vector<uint8_t> random_bytes(size_t length);
};

} // namespace nrp::modules::crypto

#endif // NRP_MODULES_CRYPTO_HPP
