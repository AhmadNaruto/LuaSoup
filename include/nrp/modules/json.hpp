#ifndef NRP_MODULES_JSON_HPP
#define NRP_MODULES_JSON_HPP

#include "nrp/core/types.hpp"
#include <string>

namespace nrp::modules::json {

class Json {
public:
    static Value parse(const std::string& json_str);
    static std::string stringify(const Value& val, bool pretty = false);
};

} // namespace nrp::modules::json

#endif // NRP_MODULES_JSON_HPP
