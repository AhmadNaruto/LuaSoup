#include "nrp/modules/json.hpp"
#include <sstream>
#include <cctype>
#include <stdexcept>

namespace nrp::modules::json {

static void skip_whitespace(const std::string& str, size_t& idx) {
    while (idx < str.length() && (str[idx] == ' ' || str[idx] == '\t' || str[idx] == '\n' || str[idx] == '\r')) {
        idx++;
    }
}

static Value parse_value(const std::string& str, size_t& idx);

static std::string parse_string(const std::string& str, size_t& idx) {
    idx++; // skip starting quote '"'
    std::string res;
    while (idx < str.length()) {
        char c = str[idx++];
        if (c == '"') return res;
        if (c == '\\' && idx < str.length()) {
            char esc = str[idx++];
            switch (esc) {
                case '"': res += '"'; break;
                case '\\': res += '\\'; break;
                case '/': res += '/'; break;
                case 'b': res += '\b'; break;
                case 'f': res += '\f'; break;
                case 'n': res += '\n'; break;
                case 'r': res += '\r'; break;
                case 't': res += '\t'; break;
                default: res += esc; break;
            }
        } else {
            res += c;
        }
    }
    return res;
}

static Value parse_number(const std::string& str, size_t& idx) {
    size_t start = idx;
    if (str[idx] == '-') idx++;
    bool is_float = false;
    while (idx < str.length() && (std::isdigit(str[idx]) || str[idx] == '.' || str[idx] == 'e' || str[idx] == 'E' || str[idx] == '+' || str[idx] == '-')) {
        if (str[idx] == '.' || str[idx] == 'e' || str[idx] == 'E') is_float = true;
        idx++;
    }
    std::string num_str = str.substr(start, idx - start);
    if (is_float) {
        return Value(std::stod(num_str));
    } else {
        return Value(static_cast<int64_t>(std::stoll(num_str)));
    }
}

static Value parse_value(const std::string& str, size_t& idx) {
    skip_whitespace(str, idx);
    if (idx >= str.length()) return Value();

    char c = str[idx];
    if (c == '"') {
        return Value(parse_string(str, idx));
    }
    if (c == '{') {
        idx++; // skip '{'
        ObjectMap map;
        skip_whitespace(str, idx);
        if (idx < str.length() && str[idx] == '}') {
            idx++;
            return Value(map);
        }
        while (idx < str.length()) {
            skip_whitespace(str, idx);
            if (str[idx] != '"') break;
            std::string key = parse_string(str, idx);
            skip_whitespace(str, idx);
            if (idx < str.length() && str[idx] == ':') idx++;
            Value val = parse_value(str, idx);
            map[key] = std::move(val);
            skip_whitespace(str, idx);
            if (idx < str.length() && str[idx] == ',') {
                idx++;
            } else if (idx < str.length() && str[idx] == '}') {
                idx++;
                break;
            }
        }
        return Value(map);
    }
    if (c == '[') {
        idx++; // skip '['
        ArrayValue arr;
        skip_whitespace(str, idx);
        if (idx < str.length() && str[idx] == ']') {
            idx++;
            return Value(arr);
        }
        while (idx < str.length()) {
            arr.push_back(parse_value(str, idx));
            skip_whitespace(str, idx);
            if (idx < str.length() && str[idx] == ',') {
                idx++;
            } else if (idx < str.length() && str[idx] == ']') {
                idx++;
                break;
            }
        }
        return Value(arr);
    }
    if (std::isdigit(c) || c == '-') {
        return parse_number(str, idx);
    }
    if (str.compare(idx, 4, "true") == 0) {
        idx += 4;
        return Value(true);
    }
    if (str.compare(idx, 5, "false") == 0) {
        idx += 5;
        return Value(false);
    }
    if (str.compare(idx, 4, "null") == 0) {
        idx += 4;
        return Value();
    }

    return Value();
}

Value Json::parse(const std::string& json_str) {
    size_t idx = 0;
    return parse_value(json_str, idx);
}

std::string Json::stringify(const Value& val, bool pretty) {
    std::ostringstream ss;
    if (val.is_null()) {
        ss << "null";
    } else if (val.is_bool()) {
        ss << (val.as_bool() ? "true" : "false");
    } else if (val.is_int()) {
        ss << val.as_int();
    } else if (val.is_float()) {
        ss << val.as_float();
    } else if (val.is_string()) {
        ss << "\"" << val.as_string() << "\"";
    } else if (val.is_array()) {
        ss << "[";
        const auto& arr = val.as_array();
        for (size_t i = 0; i < arr.size(); ++i) {
            if (i > 0) ss << ",";
            ss << stringify(arr[i], pretty);
        }
        ss << "]";
    } else if (val.is_object()) {
        ss << "{";
        const auto& obj = val.as_object();
        size_t count = 0;
        for (const auto& [k, v] : obj) {
            if (count++ > 0) ss << ",";
            ss << "\"" << k << "\":" << stringify(v, pretty);
        }
        ss << "}";
    }
    return ss.str();
}

} // namespace nrp::modules::json
