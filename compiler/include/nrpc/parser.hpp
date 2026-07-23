#ifndef NRPC_PARSER_HPP
#define NRPC_PARSER_HPP

#include "ast.hpp"
#include <string>
#include <vector>

namespace nrpc {

class Parser {
public:
    static ASTModule parse_spec_file(const std::string& filepath);
    static ASTProject parse_specs_directory(const std::string& dirpath);
};

} // namespace nrpc

#endif // NRPC_PARSER_HPP
