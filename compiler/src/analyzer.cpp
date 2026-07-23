#include "nrpc/analyzer.hpp"

namespace nrpc {

bool SemanticAnalyzer::analyze_module(const ASTModule& module) {
    if (module.name.empty()) {
        diagnostics_.push_back({SemanticDiagnostic::Severity::Error, "", "Module name cannot be empty"});
        return false;
    }

    if (module.target_arch != TargetArch::ARM64) {
        diagnostics_.push_back({SemanticDiagnostic::Severity::Warning, module.name, "Target architecture is not strictly ARM64"});
    }

    return true;
}

bool SemanticAnalyzer::analyze_project(const ASTProject& project) {
    diagnostics_.clear();
    bool valid = true;

    if (project.modules.empty()) {
        diagnostics_.push_back({SemanticDiagnostic::Severity::Error, "", "No specifications found in project"});
        return false;
    }

    for (const auto& [name, mod] : project.modules) {
        if (!analyze_module(mod)) {
            valid = false;
        }
    }

    diagnostics_.push_back({
        SemanticDiagnostic::Severity::Info,
        "",
        "Successfully analyzed " + std::to_string(project.modules.size()) + " modules for Android ARM64."
    });

    return valid;
}

} // namespace nrpc
