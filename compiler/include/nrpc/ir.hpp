#ifndef NRPC_IR_HPP
#define NRPC_IR_HPP

#include "ast.hpp"
#include <string>
#include <vector>
#include <unordered_map>

namespace nrpc {

struct IRType {
    std::string id;
    std::string name;
    nrp::TypeKind kind;
    bool nullable{false};
};

struct IRProperty {
    std::string id;
    std::string name;
    IRType type;
    bool readonly{false};
};

struct IRMethod {
    std::string id;
    std::string name;
    IRType return_type;
    std::vector<IRProperty> parameters;
};

struct IRClass {
    std::string id;
    std::string name;
    std::string namespace_name;
    std::vector<IRProperty> properties;
    std::vector<IRMethod> methods;
};

struct IRModule {
    std::string id;
    std::string name;
    std::string version;
    std::string target_arch{"arm64-v8a"};
    std::vector<IRClass> classes;
};

struct IRProject {
    std::string name;
    std::string target_abi{"arm64-v8a"};
    std::unordered_map<std::string, IRModule> modules;
};

class IRBuilder {
public:
    static IRModule build_from_ast(const ASTModule& ast);
    static IRProject build_project_from_ast(const ASTProject& ast_proj);
};

} // namespace nrpc

#endif // NRPC_IR_HPP
