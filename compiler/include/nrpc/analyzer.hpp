#ifndef NRPC_ANALYZER_HPP
#define NRPC_ANALYZER_HPP

#include "ast.hpp"
#include <string>
#include <vector>

namespace nrpc {

struct SemanticDiagnostic {
    enum class Severity { Error, Warning, Info };
    Severity severity;
    std::string module;
    std::string message;
};

class SemanticAnalyzer {
private:
    std::vector<SemanticDiagnostic> diagnostics_;

public:
    bool analyze_module(const ASTModule& module);
    bool analyze_project(const ASTProject& project);

    const std::vector<SemanticDiagnostic>& diagnostics() const noexcept { return diagnostics_; }
};

} // namespace nrpc

#endif // NRPC_ANALYZER_HPP
