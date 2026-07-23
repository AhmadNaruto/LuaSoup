#include "nrp/modules/encoding.hpp"
#include "nrp/modules/buffer.hpp"

namespace nrp::modules::encoding {

std::string Encoding::to_utf8(const std::string& input) {
    return input;
}

std::string Encoding::to_base64(const std::string& input) {
    buffer::Buffer buf(input);
    return buf.to_base64();
}

std::string Encoding::from_base64(const std::string& input) {
    return buffer::Buffer::from_base64(input).to_string();
}

std::string Encoding::to_hex(const std::string& input) {
    buffer::Buffer buf(input);
    return buf.to_hex();
}

std::string Encoding::from_hex(const std::string& input) {
    return buffer::Buffer::from_hex(input).to_string();
}

} // namespace nrp::modules::encoding
