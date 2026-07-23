#ifndef NRP_MODULES_BUFFER_HPP
#define NRP_MODULES_BUFFER_HPP

#include <vector>
#include <string>
#include <cstdint>
#include <cstddef>

namespace nrp::modules::buffer {

class Buffer {
private:
    std::vector<uint8_t> data_;

public:
    Buffer() = default;
    explicit Buffer(size_t size) : data_(size, 0) {}
    Buffer(const uint8_t* ptr, size_t len) : data_(ptr, ptr + len) {}
    explicit Buffer(std::string str) : data_(str.begin(), str.end()) {}

    size_t size() const noexcept { return data_.size(); }
    const uint8_t* data() const noexcept { return data_.data(); }
    uint8_t* data() noexcept { return data_.data(); }

    std::string to_string() const { return std::string(data_.begin(), data_.end()); }
    std::string to_hex() const;
    std::string to_base64() const;

    static Buffer from_hex(const std::string& hex);
    static Buffer from_base64(const std::string& b64);
};

} // namespace nrp::modules::buffer

#endif // NRP_MODULES_BUFFER_HPP
