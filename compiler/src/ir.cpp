#include "nrpc/ir.hpp"

namespace nrpc {

IRModule IRBuilder::build_from_ast(const ASTModule& ast) {
    IRModule ir;
    ir.id = "mod_" + ast.name;
    ir.name = ast.name;
    ir.version = ast.version.empty() ? "1.0.0" : ast.version;
    ir.target_arch = "arm64-v8a";

    for (const auto& cls : ast.classes) {
        IRClass ir_cls;
        ir_cls.id = "cls_" + cls.name;
        ir_cls.name = cls.name;
        ir_cls.namespace_name = ast.namespace_name;

        for (const auto& prop : cls.properties) {
            IRProperty ir_p;
            ir_p.id = "prop_" + prop.name;
            ir_p.name = prop.name;
            ir_p.type = {prop.type_name, prop.type_name, nrp::TypeKind::String, prop.nullable};
            ir_p.readonly = prop.readonly;
            ir_cls.properties.push_back(ir_p);
        }

        for (const auto& mth : cls.methods) {
            IRMethod ir_m;
            ir_m.id = "mth_" + mth.name;
            ir_m.name = mth.name;
            ir_m.return_type = {mth.return_type_name, mth.return_type_name, nrp::TypeKind::Object, false};
            for (const auto& param : mth.parameters) {
                IRProperty p;
                p.name = param.name;
                p.type = {param.type_name, param.type_name, nrp::TypeKind::String, param.nullable};
                ir_m.parameters.push_back(p);
            }
            ir_cls.methods.push_back(ir_m);
        }

        ir.classes.push_back(ir_cls);
    }

    return ir;
}

IRProject IRBuilder::build_project_from_ast(const ASTProject& ast_proj) {
    IRProject ir_proj;
    ir_proj.name = ast_proj.name;
    ir_proj.target_abi = "arm64-v8a";

    for (const auto& [name, mod] : ast_proj.modules) {
        ir_proj.modules[name] = build_from_ast(mod);
    }

    return ir_proj;
}

} // namespace nrpc
