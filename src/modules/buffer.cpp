#include "nrp/modules/buffer.hpp"
#include <sstream>
#include <iomanip>

namespace nrp::modules::buffer {

static const char HEX_CHARS[] = "0123456789abcdef";

std::string Buffer::to_hex() const {
    std::string res;
    res.reserve(data_.size() * 2);
    for (uint8_t b : data_) {
        res.push_back(HEX_CHARS[(b >> 4) & 0x0F]);
        res.push_back(HEX_CHARS[b & 0x0F]);
    }
    return res;
}

static const char B64_CHARS[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

std::string Buffer::to_base64() const {
    std::string ret;
    int i = 0;
    int j = 0;
    uint8_t char_array_3[3];
    uint8_t char_array_4[4];
    size_t in_len = data_.size();
    const uint8_t* bytes_to_encode = data_.data();

    while (in_len--) {
        char_array_3[i++] = *(bytes_to_encode++);
        if (i == 3) {
            char_array_4[0] = static_cast<uint8_t>((char_array_3[0] & 0xfc) >> 2);
            char_array_4[1] = static_cast<uint8_t>(((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4));
            char_array_4[2] = static_cast<uint8_t>(((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6));
            char_array_4[3] = static_cast<uint8_t>(char_array_3[2] & 0x3f);

            for(i = 0; (i < 4) ; i++)
                ret += B64_CHARS[char_array_4[i]];
            i = 0;
        }
    }

    if (i) {
        for(j = i; j < 3; j++)
            char_array_3[j] = '\0';

        char_array_4[0] = static_cast<uint8_t>((char_array_3[0] & 0xfc) >> 2);
        char_array_4[1] = static_cast<uint8_t>(((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4));
        char_array_4[2] = static_cast<uint8_t>(((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6));

        for (j = 0; (j < i + 1); j++)
            ret += B64_CHARS[char_array_4[j]];

        while((i++ < 3))
            ret += '=';
    }

    return ret;
}

Buffer Buffer::from_hex(const std::string& hex) {
    std::vector<uint8_t> bytes;
    bytes.reserve(hex.length() / 2);
    for (size_t i = 0; i < hex.length(); i += 2) {
        std::string byteString = hex.substr(i, 2);
        uint8_t byte = static_cast<uint8_t>(strtol(byteString.c_str(), nullptr, 16));
        bytes.push_back(byte);
    }
    return Buffer(bytes.data(), bytes.size());
}

Buffer Buffer::from_base64(const std::string& b64) {
    // Basic Base64 decoder implementation
    std::vector<uint8_t> out;
    std::vector<int> T(256, -1);
    for (int i=0; i<64; i++) T[B64_CHARS[i]] = i;

    int val=0, valb=-8;
    for (uint8_t c : b64) {
        if (T[c] == -1) break;
        val = (val << 6) + T[c];
        valb += 6;
        if (valb >= 0) {
            out.push_back(static_cast<uint8_t>((val >> valb) & 0xFF));
            valb -= 8;
        }
    }
    return Buffer(out.data(), out.size());
}

} // namespace nrp::modules::buffer
