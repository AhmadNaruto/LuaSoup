#include "nrpc/parser.hpp"
#include "nrpc/analyzer.hpp"
#include "nrpc/ir.hpp"
#include "nrpc/generator.hpp"
#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>

namespace fs = std::filesystem;

int main(int argc, char** argv) {
    std::cout << "NRP Compiler (nrpc) v1.0.0 [Target Architecture: Android arm64-v8a]" << std::endl;

    std::string specs_dir = (argc > 1) ? argv[1] : "specs";
    std::cout << "Parsing specification directory: " << specs_dir << "..." << std::endl;

    auto ast_proj = nrpc::Parser::parse_specs_directory(specs_dir);

    nrpc::SemanticAnalyzer analyzer;
    if (!analyzer.analyze_project(ast_proj)) {
        std::cerr << "Semantic analysis failed!" << std::endl;
        for (const auto& diag : analyzer.diagnostics()) {
            std::cerr << " [ERROR] " << diag.message << std::endl;
        }
        return 1;
    }

    for (const auto& diag : analyzer.diagnostics()) {
        std::cout << " [INFO] " << diag.message << std::endl;
    }

    auto ir_proj = nrpc::IRBuilder::build_project_from_ast(ast_proj);
    std::cout << nrpc::CodeGenerator::generate_project_summary(ir_proj) << std::endl;

    // Generate output directories
    fs::create_directories("generated/jni");
    fs::create_directories("generated/reflection");
    fs::create_directories("kotlin/luasoup-sdk/src/main/java/com/luasoup/nrp");

    // Write generated JNI Bridge C++ source
    std::ofstream jni_out("generated/jni/nrp_jni_bridge.cpp");
    if (jni_out.is_open()) {
        jni_out << nrpc::CodeGenerator::generate_project_jni(ir_proj);
        std::cout << " [GENERATED] generated/jni/nrp_jni_bridge.cpp" << std::endl;
    }

    // Write generated Reflection Metadata C++ source
    std::ofstream refl_out("generated/reflection/nrp_reflection_descriptors.cpp");
    if (refl_out.is_open()) {
        refl_out << nrpc::CodeGenerator::generate_project_reflection(ir_proj);
        std::cout << " [GENERATED] generated/reflection/nrp_reflection_descriptors.cpp" << std::endl;
    }

    // Write generated Kotlin SDK source
    std::ofstream kt_out("kotlin/luasoup-sdk/src/main/java/com/luasoup/nrp/GeneratedNRPBridge.kt");
    if (kt_out.is_open()) {
        kt_out << nrpc::CodeGenerator::generate_project_kotlin(ir_proj);
        std::cout << " [GENERATED] kotlin/luasoup-sdk/src/main/java/com/luasoup/nrp/GeneratedNRPBridge.kt" << std::endl;
    }

    std::cout << "Automated Code Generation Completed Successfully for Android ARM64!" << std::endl;
    return 0;
}
