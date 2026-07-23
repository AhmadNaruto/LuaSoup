#ifndef NRP_CORE_HANDLE_HPP
#define NRP_CORE_HANDLE_HPP

#include <cstdint>
#include <cstddef>
#include <functional>
#include <string>

namespace nrp {

enum class OwnershipType : uint8_t {
    Shared = 0,
    Unique = 1,
    Borrowed = 2,
    Weak = 3
};

struct Handle {
    uint64_t id{0};

    constexpr Handle() = default;
    constexpr explicit Handle(uint64_t id_) : id(id_) {}

    constexpr bool is_valid() const noexcept { return id != 0; }
    constexpr uint32_t index() const noexcept { return static_cast<uint32_t>(id & 0xFFFFFFFF); }
    constexpr uint16_t generation() const noexcept { return static_cast<uint16_t>((id >> 32) & 0xFFFF); }
    constexpr uint8_t type_id() const noexcept { return static_cast<uint8_t>((id >> 48) & 0xFF); }
    constexpr OwnershipType ownership() const noexcept { 
        return static_cast<OwnershipType>((id >> 56) & 0xFF); 
    }

    static constexpr Handle create(uint8_t type, uint16_t gen, uint32_t idx, OwnershipType own = OwnershipType::Shared) noexcept {
        uint64_t val = static_cast<uint64_t>(idx) |
                       (static_cast<uint64_t>(gen) << 32) |
                       (static_cast<uint64_t>(type) << 48) |
                       (static_cast<uint64_t>(own) << 56);
        return Handle(val);
    }

    constexpr bool operator==(const Handle& other) const noexcept { return id == other.id; }
    constexpr bool operator!=(const Handle& other) const noexcept { return id != other.id; }
    constexpr bool operator<(const Handle& other) const noexcept { return id < other.id; }
};

struct HandleHash {
    std::size_t operator()(const Handle& h) const noexcept {
        return std::hash<uint64_t>{}(h.id);
    }
};

} // namespace nrp

#endif // NRP_CORE_HANDLE_HPP
