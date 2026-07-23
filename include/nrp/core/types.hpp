#ifndef NRP_CORE_TYPES_HPP
#define NRP_CORE_TYPES_HPP

#include "handle.hpp"
#include <string>
#include <vector>
#include <unordered_map>
#include <variant>
#include <memory>
#include <cstdint>

namespace nrp {

enum class TypeKind : uint8_t {
    Null = 0,
    Boolean = 1,
    Integer = 2,
    Float = 3,
    String = 4,
    Buffer = 5,
    Array = 6,
    Object = 7,
    Handle = 8,
    Function = 9
};

struct Value;

using ArrayValue = std::vector<Value>;
using ObjectMap = std::unordered_map<std::string, Value>;

struct Value {
    using VariantType = std::variant<
        std::monostate,         // Null
        bool,                   // Boolean
        int64_t,                // Integer
        double,                 // Float
        std::string,            // String
        std::vector<uint8_t>,   // Buffer
        std::shared_ptr<ArrayValue>, // Array
        std::shared_ptr<ObjectMap>,  // Object Map
        Handle                  // Native Handle
    >;

    VariantType data;

    Value() : data(std::monostate{}) {}
    Value(bool v) : data(v) {}
    Value(int32_t v) : data(static_cast<int64_t>(v)) {}
    Value(int64_t v) : data(v) {}
    Value(double v) : data(v) {}
    Value(const std::string& v) : data(v) {}
    Value(const char* v) : data(std::string(v)) {}
    Value(std::vector<uint8_t> v) : data(std::move(v)) {}
    Value(ArrayValue v) : data(std::make_shared<ArrayValue>(std::move(v))) {}
    Value(ObjectMap v) : data(std::make_shared<ObjectMap>(std::move(v))) {}
    Value(Handle h) : data(h) {}

    TypeKind kind() const noexcept {
        return static_cast<TypeKind>(data.index());
    }

    bool is_null() const noexcept { return kind() == TypeKind::Null; }
    bool is_bool() const noexcept { return kind() == TypeKind::Boolean; }
    bool is_int() const noexcept { return kind() == TypeKind::Integer; }
    bool is_float() const noexcept { return kind() == TypeKind::Float; }
    bool is_string() const noexcept { return kind() == TypeKind::String; }
    bool is_buffer() const noexcept { return kind() == TypeKind::Buffer; }
    bool is_array() const noexcept { return kind() == TypeKind::Array; }
    bool is_object() const noexcept { return kind() == TypeKind::Object; }
    bool is_handle() const noexcept { return kind() == TypeKind::Handle; }

    bool as_bool() const { return std::get<bool>(data); }
    int64_t as_int() const { return std::get<int64_t>(data); }
    double as_float() const { return std::get<double>(data); }
    const std::string& as_string() const { return std::get<std::string>(data); }
    const std::vector<uint8_t>& as_buffer() const { return std::get<std::vector<uint8_t>>(data); }
    const ArrayValue& as_array() const { return *std::get<std::shared_ptr<ArrayValue>>(data); }
    const ObjectMap& as_object() const { return *std::get<std::shared_ptr<ObjectMap>>(data); }
    Handle as_handle() const { return std::get<Handle>(data); }
};

} // namespace nrp

#endif // NRP_CORE_TYPES_HPP
