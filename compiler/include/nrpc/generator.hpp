#ifndef NRPC_GENERATOR_HPP
#define NRPC_GENERATOR_HPP

#include "ir.hpp"
#include <string>

namespace nrpc {

class CodeGenerator {
public:
    static std::string generate_kotlin(const IRModule& ir);
    static std::string generate_luau(const IRModule& ir);
    static std::string generate_jni(const IRModule& ir);
    static std::string generate_reflection(const IRModule& ir);
    static std::string generate_docs(const IRModule& ir);

    static std::string generate_project_jni(const IRProject& proj);
    static std::string generate_project_kotlin(const IRProject& proj);
    static std::string generate_project_reflection(const IRProject& proj);

    static std::string generate_project_summary(const IRProject& proj);
};

} // namespace nrpc

#endif // NRPC_GENERATOR_HPP
