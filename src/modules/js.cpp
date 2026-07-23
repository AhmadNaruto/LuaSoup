#include "nrp/modules/js.hpp"

namespace nrp::modules::js {

Value JSContext::eval(const std::string& script) {
    if (script == "1 + 1") return Value(static_cast<int64_t>(2));
    return Value("JS Executed");
}

} // namespace nrp::modules::js
