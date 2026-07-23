#ifndef NRP_LUAU_ENGINE_HPP
#define NRP_LUAU_ENGINE_HPP

#include "nrp/core/types.hpp"
#include <string>
#include <vector>
#include <memory>

struct lua_State;

namespace nrp::luau {

class LuauEngine {
private:
    lua_State* L_{nullptr};
    bool initialized_{false};

    void register_native_modules();

public:
    LuauEngine();
    ~LuauEngine();

    void initialize();
    void shutdown();
    bool is_initialized() const noexcept { return initialized_; }

    Value eval(const std::string& script);
    Value call_function(const std::string& func_name, const std::vector<Value>& args = {});

    lua_State* state() const noexcept { return L_; }
};

} // namespace nrp::luau

#endif // NRP_LUAU_ENGINE_HPP
