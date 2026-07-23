#ifndef NRP_CORE_ERROR_HPP
#define NRP_CORE_ERROR_HPP

#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <stdexcept>

namespace nrp::error {

enum class ErrorCategory {
    Validation,
    Parser,
    Regex,
    HTML,
    JSON,
    Crypto,
    JavaScript,
    Runtime,
    Bridge
};

enum class Severity {
    Fatal,
    Error,
    Warning,
    Info
};

struct StackFrame {
    std::string function_name;
    std::string file_name;
    int line_number{0};
};

class StackTrace {
public:
    std::vector<StackFrame> frames;

    void push_frame(std::string func, std::string file, int line) {
        frames.push_back({std::move(func), std::move(file), line});
    }

    std::string to_string() const {
        std::string res;
        for (const auto& f : frames) {
            res += "  at " + f.function_name + " (" + f.file_name + ":" + std::to_string(f.line_number) + ")\n";
        }
        return res;
    }
};

class DiagnosticContext {
public:
    std::string module_name;
    std::string operation;
    std::unordered_map<std::string, std::string> metadata;

    void set(const std::string& key, const std::string& val) {
        metadata[key] = val;
    }
};

class NRPException : public std::runtime_error {
private:
    ErrorCategory category_;
    Severity severity_;
    std::string code_;
    DiagnosticContext context_;
    StackTrace stack_trace_;

public:
    NRPException(ErrorCategory cat, std::string code, std::string message, Severity sev = Severity::Error)
        : std::runtime_error(message), category_(cat), severity_(sev), code_(std::move(code)) {}

    ErrorCategory category() const noexcept { return category_; }
    Severity severity() const noexcept { return severity_; }
    const std::string& code() const noexcept { return code_; }
    const DiagnosticContext& context() const noexcept { return context_; }
    const StackTrace& stack_trace() const noexcept { return stack_trace_; }

    void set_context(DiagnosticContext ctx) { context_ = std::move(ctx); }
    void set_stack_trace(StackTrace st) { stack_trace_ = std::move(st); }
};

} // namespace nrp::error

#endif // NRP_CORE_ERROR_HPP
