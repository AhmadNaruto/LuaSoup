#ifndef NRP_MODULES_JS_HPP
#define NRP_MODULES_JS_HPP

#include "nrp/core/types.hpp"
#include <string>

namespace nrp::modules::js {

class JSContext {
public:
    Value eval(const std::string& script);
};

} // namespace nrp::modules::js

#endif // NRP_MODULES_JS_HPP
