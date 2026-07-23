#ifndef NRPC_AST_HPP
#define NRPC_AST_HPP

#include "nrp/core/types.hpp"
#include <string>
#include <vector>
#include <unordered_map>
#include <memory>

namespace nrpc {

enum class TargetArch {
    ARM64,      // Android arm64-v8a (Primary target)
    Generic
};

struct ASTProperty {
    std::string name;
    std::string type_name;
    bool readonly{false};
    bool nullable{false};
    std::string documentation;
};

struct ASTParameter {
    std::string name;
    std::string type_name;
    bool nullable{false};
};

struct ASTMethod {
    std::string name;
    std::string return_type_name;
    std::vector<ASTParameter> parameters;
    std::string documentation;
};

struct ASTClass {
    std::string name;
    std::string parent_class;
    std::vector<ASTProperty> properties;
    std::vector<ASTMethod> methods;
    std::string documentation;
};

struct ASTModule {
    std::string name;
    std::string namespace_name;
    std::string version{"1.0.0"};
    std::string overview;
    std::vector<std::string> responsibilities;
    std::vector<ASTClass> classes;
    TargetArch target_arch{TargetArch::ARM64};
};

struct ASTProject {
    std::string name{"LuaSoup NRP"};
    TargetArch target_arch{TargetArch::ARM64};
    std::unordered_map<std::string, ASTModule> modules;
};

} // namespace nrpc

#endif // NRPC_AST_HPP
