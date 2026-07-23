#include "nrpc/parser.hpp"
#include <fstream>
#include <sstream>
#include <filesystem>
#include <algorithm>
#include <cctype>

namespace fs = std::filesystem;

namespace nrpc {

static std::string trim(const std::string& str) {
    auto start = str.find_first_not_of(" \t\r\n");
    if (start == std::string::npos) return "";
    auto end = str.find_last_not_of(" \t\r\n");
    return str.substr(start, end - start + 1);
}

ASTModule Parser::parse_spec_file(const std::string& filepath) {
    ASTModule mod;
    mod.target_arch = TargetArch::ARM64; // Strict Android ARM64 target

    std::ifstream file(filepath);
    if (!file.is_open()) return mod;

    if (filepath.rfind(".json") != std::string::npos) {
        std::stringstream buffer;
        buffer << file.rdbuf();
        std::string content = buffer.str();

        // Extract module name
        auto m_pos = content.find("\"module\"");
        if (m_pos != std::string::npos) {
            auto start = content.find('"', m_pos + 8);
            auto end = content.find('"', start + 1);
            if (start != std::string::npos && end != std::string::npos) {
                mod.name = content.substr(start + 1, end - start - 1);
            }
        }

        // Extract namespace
        auto ns_pos = content.find("\"namespace\"");
        if (ns_pos != std::string::npos) {
            auto start = content.find('"', ns_pos + 11);
            auto end = content.find('"', start + 1);
            if (start != std::string::npos && end != std::string::npos) {
                mod.namespace_name = content.substr(start + 1, end - start - 1);
            }
        }

        return mod;
    }

    std::string line;
    std::string current_heading;
    ASTClass* current_class = nullptr;

    while (std::getline(file, line)) {
        std::string trimmed = trim(line);
        if (trimmed.empty()) continue;

        if (trimmed.rfind("# ", 0) == 0) {
            mod.name = trim(trimmed.substr(2));
            mod.namespace_name = "com.luasoup.nrp." + mod.name;
            std::transform(mod.namespace_name.begin(), mod.namespace_name.end(), mod.namespace_name.begin(), ::tolower);
            continue;
        }

        if (trimmed.rfind("## ", 0) == 0) {
            current_heading = trim(trimmed.substr(3));
            continue;
        }

        if (current_heading == "Responsibilities" && trimmed.rfind("- ", 0) == 0) {
            mod.responsibilities.push_back(trim(trimmed.substr(2)));
        } else if ((current_heading == "Public Objects" || current_heading == "Classes") && trimmed.rfind("- ", 0) == 0) {
            std::string class_name = trim(trimmed.substr(2));
            ASTClass cls;
            cls.name = class_name;
            cls.documentation = "Public object defined in " + mod.name;
            mod.classes.push_back(cls);
            current_class = &mod.classes.back();
        } else if (current_heading == "Supported APIs" && trimmed.rfind("- ", 0) == 0) {
            std::string api = trim(trimmed.substr(2));
            if (current_class) {
                ASTMethod mth;
                size_t paren = api.find('(');
                mth.name = (paren != std::string::npos) ? api.substr(0, paren) : api;
                mth.return_type_name = "Value";
                current_class->methods.push_back(mth);
            }
        }
    }

    if (mod.classes.empty()) {
        ASTClass default_cls;
        default_cls.name = mod.name;
        default_cls.documentation = "Module " + mod.name;
        mod.classes.push_back(default_cls);
    }

    return mod;
}

ASTProject Parser::parse_specs_directory(const std::string& dirpath) {
    ASTProject proj;
    proj.name = "LuaSoup NRP (Android ARM64)";
    proj.target_arch = TargetArch::ARM64;

    if (!fs::exists(dirpath) || !fs::is_directory(dirpath)) {
        return proj;
    }

    std::vector<fs::path> paths;
    for (const auto& entry : fs::directory_iterator(dirpath)) {
        if (entry.is_regular_file() && (entry.path().extension() == ".md" || entry.path().extension() == ".json")) {
            paths.push_back(entry.path());
        }
    }

    std::sort(paths.begin(), paths.end());

    for (const auto& p : paths) {
        ASTModule mod = parse_spec_file(p.string());
        if (!mod.name.empty()) {
            proj.modules[mod.name] = mod;
        }
    }

    return proj;
}

} // namespace nrpc
