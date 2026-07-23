#include "nrp/modules/url.hpp"
#include <sstream>
#include <iomanip>
#include <cctype>

namespace nrp::modules::url {

std::string URL::encode(const std::string& value) {
    std::ostringstream escaped;
    escaped.fill('0');
    escaped << std::hex;

    for (char c : value) {
        if (std::isalnum(static_cast<unsigned char>(c)) || c == '-' || c == '_' || c == '.' || c == '~') {
            escaped << c;
        } else {
            escaped << '%' << std::setw(2) << std::uppercase << static_cast<int>(static_cast<unsigned char>(c));
        }
    }

    return escaped.str();
}

std::string URL::decode(const std::string& value) {
    std::string result;
    result.reserve(value.length());

    for (size_t i = 0; i < value.length(); ++i) {
        if (value[i] == '%') {
            if (i + 2 < value.length()) {
                int hex = 0;
                std::istringstream iss(value.substr(i + 1, 2));
                if (iss >> std::hex >> hex) {
                    result += static_cast<char>(hex);
                    i += 2;
                }
            }
        } else if (value[i] == '+') {
            result += ' ';
        } else {
            result += value[i];
        }
    }

    return result;
}

URL URL::parse(const std::string& url_str) {
    URL u;
    size_t pos = 0;

    // Scheme
    size_t scheme_end = url_str.find("://");
    if (scheme_end != std::string::npos) {
        u.scheme = url_str.substr(0, scheme_end);
        pos = scheme_end + 3;
    }

    // Host & Port
    size_t path_start = url_str.find('/', pos);
    std::string host_port;
    if (path_start != std::string::npos) {
        host_port = url_str.substr(pos, path_start - pos);
        pos = path_start;
    } else {
        host_port = url_str.substr(pos);
        pos = url_str.length();
    }

    size_t port_pos = host_port.find(':');
    if (port_pos != std::string::npos) {
        u.host = host_port.substr(0, port_pos);
        u.port = std::stoi(host_port.substr(port_pos + 1));
    } else {
        u.host = host_port;
        u.port = (u.scheme == "https") ? 443 : 80;
    }

    // Path, Query, Hash
    if (pos < url_str.length()) {
        std::string rest = url_str.substr(pos);
        size_t hash_pos = rest.find('#');
        if (hash_pos != std::string::npos) {
            u.hash = rest.substr(hash_pos + 1);
            rest = rest.substr(0, hash_pos);
        }

        size_t query_pos = rest.find('?');
        if (query_pos != std::string::npos) {
            u.path = rest.substr(0, query_pos);
            u.query = rest.substr(query_pos + 1);

            // Parse Query Params
            std::istringstream qss(u.query);
            std::string pair;
            while (std::getline(qss, pair, '&')) {
                size_t eq = pair.find('=');
                if (eq != std::string::npos) {
                    u.query_params[decode(pair.substr(0, eq))] = decode(pair.substr(eq + 1));
                } else if (!pair.empty()) {
                    u.query_params[decode(pair)] = "";
                }
            }
        } else {
            u.path = rest;
        }
    }

    if (u.path.empty()) u.path = "/";
    return u;
}

std::string URL::to_string() const {
    std::ostringstream ss;
    if (!scheme.empty()) ss << scheme << "://";
    ss << host;
    if (port != 0 && port != 80 && port != 443) ss << ":" << port;
    ss << path;
    if (!query.empty()) ss << "?" << query;
    if (!hash.empty()) ss << "#" << hash;
    return ss.str();
}

} // namespace nrp::modules::url
