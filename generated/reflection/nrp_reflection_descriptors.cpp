// Auto-generated Reflection Metadata Registry Descriptors
#include "nrp/reflection/registry.hpp"

namespace nrp::generated {
void register_all_metadata() {
    auto& reg = nrp::ReflectionRegistry::instance();
    reg.register_class({"buffer", "mod_buffer", "", {}, {}, "Specification module"});
    reg.register_class({"crypto", "mod_crypto", "", {}, {}, "Specification module"});
    reg.register_class({"encoding", "mod_encoding", "", {}, {}, "Specification module"});
    reg.register_class({"html", "mod_html", "", {}, {}, "Specification module"});
    reg.register_class({"javascript", "mod_javascript", "", {}, {}, "Specification module"});
    reg.register_class({"json", "mod_json", "", {}, {}, "Specification module"});
    reg.register_class({"luau", "mod_luau", "", {}, {}, "Specification module"});
    reg.register_class({"url", "mod_url", "", {}, {}, "Specification module"});
    reg.register_class({"regex", "mod_regex", "", {}, {}, "Specification module"});
    reg.register_class({"utility", "mod_utility", "", {}, {}, "Specification module"});
}
} // namespace nrp::generated
