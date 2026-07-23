#include "nrpc/parser.hpp"
#include "nrpc/analyzer.hpp"
#include "nrpc/ir.hpp"
#include "nrpc/generator.hpp"
#include <cassert>
#include <iostream>

int main() {
    std::cout << "Running NRP Compiler (Android ARM64) Code Generator Tests..." << std::endl;

    auto ast_proj = nrpc::Parser::parse_specs_directory("../specs");
    assert(!ast_proj.modules.empty());

    nrpc::SemanticAnalyzer analyzer;
    assert(analyzer.analyze_project(ast_proj));

    auto ir_proj = nrpc::IRBuilder::build_project_from_ast(ast_proj);
    assert(ir_proj.target_abi == "arm64-v8a");

    std::string jni_code = nrpc::CodeGenerator::generate_project_jni(ir_proj);
    std::string kt_code = nrpc::CodeGenerator::generate_project_kotlin(ir_proj);
    std::string refl_code = nrpc::CodeGenerator::generate_project_reflection(ir_proj);

    assert(jni_code.find("Java_com_luasoup_nrp_NRP_nativeEvalLuau") != std::string::npos);
    assert(kt_code.find("TARGET_ABI: String = \"arm64-v8a\"") != std::string::npos);
    assert(refl_code.find("register_all_metadata()") != std::string::npos);

    std::cout << "JNI, Kotlin, and Reflection Generator Tests Passed Successfully for Android ARM64!" << std::endl;
    return 0;
}
