#ifndef NRP_BRIDGE_CONVERSION_HPP
#define NRP_BRIDGE_CONVERSION_HPP

#include "nrp/core/types.hpp"
#include <string>

namespace nrp::bridge {

class TypeConverter {
public:
    static Value convert_primitive(const Value& val) {
        return val;
    }
};

} // namespace nrp::bridge

#endif // NRP_BRIDGE_CONVERSION_HPP
