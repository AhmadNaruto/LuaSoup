#include "nrp/modules/html.hpp"
#include <sstream>
#include <algorithm>
#include <cctype>

namespace nrp::modules::html {

std::string Node::attr(const std::string& name) const {
    auto it = attributes.find(name);
    if (it != attributes.end()) return it->second;
    return "";
}

void Node::attr(const std::string& name, const std::string& value) {
    attributes[name] = value;
}

bool Node::has_attr(const std::string& name) const {
    return attributes.find(name) != attributes.end();
}

void Node::remove_attr(const std::string& name) {
    attributes.erase(name);
}

bool Node::has_class(const std::string& cls) const {
    std::string classes = attr("class");
    std::istringstream iss(classes);
    std::string item;
    while (iss >> item) {
        if (item == cls) return true;
    }
    return false;
}

void Node::add_class(const std::string& cls) {
    if (!has_class(cls)) {
        std::string current = attr("class");
        if (!current.empty()) current += " ";
        current += cls;
        attr("class", current);
    }
}

void Node::remove_class(const std::string& cls) {
    std::string current = attr("class");
    std::istringstream iss(current);
    std::string item;
    std::string updated;
    while (iss >> item) {
        if (item != cls) {
            if (!updated.empty()) updated += " ";
            updated += item;
        }
    }
    attr("class", updated);
}

std::string Node::text() const {
    if (type == NodeType::Text) {
        return text_content;
    }
    std::string result;
    for (const auto& child : children) {
        result += child->text();
    }
    return result;
}

std::string Node::html() const {
    std::string result;
    for (const auto& child : children) {
        result += child->outer_html();
    }
    return result;
}

std::string Node::outer_html() const {
    if (type == NodeType::Text) {
        return text_content;
    }
    if (type == NodeType::Document) {
        return html();
    }

    std::ostringstream ss;
    ss << "<" << tag;
    for (const auto& [k, v] : attributes) {
        ss << " " << k << "=\"" << v << "\"";
    }
    if (children.empty() && (tag == "img" || tag == "input" || tag == "br" || tag == "hr" || tag == "meta")) {
        ss << " />";
        return ss.str();
    }
    ss << ">";
    ss << html();
    ss << "</" << tag << ">";
    return ss.str();
}

std::vector<std::shared_ptr<Node>> Node::child_elements() const {
    std::vector<std::shared_ptr<Node>> elems;
    for (const auto& child : children) {
        if (child && child->type == NodeType::Element) {
            elems.push_back(child);
        }
    }
    return elems;
}

std::shared_ptr<Node> Node::first_element_child() const {
    for (const auto& child : children) {
        if (child && child->type == NodeType::Element) return child;
    }
    return nullptr;
}

std::shared_ptr<Node> Node::last_element_child() const {
    for (auto it = children.rbegin(); it != children.rend(); ++it) {
        if (*it && (*it)->type == NodeType::Element) return *it;
    }
    return nullptr;
}

std::shared_ptr<Node> Node::next_element_sibling() const {
    auto p = parent();
    if (!p) return nullptr;

    bool found_self = false;
    for (const auto& child : p->children) {
        if (found_self) {
            if (child && child->type == NodeType::Element) return child;
        } else if (child.get() == this) {
            found_self = true;
        }
    }
    return nullptr;
}

std::shared_ptr<Node> Node::previous_element_sibling() const {
    auto p = parent();
    if (!p) return nullptr;

    std::shared_ptr<Node> prev = nullptr;
    for (const auto& child : p->children) {
        if (child.get() == this) {
            return prev;
        }
        if (child && child->type == NodeType::Element) {
            prev = child;
        }
    }
    return nullptr;
}

static bool matches_selector(const Node* node, const std::string& selector) {
    if (!node || node->type != NodeType::Element) return false;
    if (selector.empty()) return false;

    // Tag selector
    if (selector[0] != '.' && selector[0] != '#') {
        return node->tag == selector;
    }
    // Class selector
    if (selector[0] == '.') {
        std::string target_cls = selector.substr(1);
        return node->has_class(target_cls);
    }
    // ID selector
    if (selector[0] == '#') {
        std::string target_id = selector.substr(1);
        return (node->id() == target_id);
    }
    return false;
}

static void collect_nodes(const Node* node, const std::string& selector, std::vector<std::shared_ptr<Node>>& out) {
    if (matches_selector(node, selector)) {
        out.push_back(const_cast<Node*>(node)->shared_from_this());
    }
    for (const auto& child : node->children) {
        collect_nodes(child.get(), selector, out);
    }
}

std::vector<std::shared_ptr<Node>> Node::select(const std::string& selector) const {
    std::vector<std::shared_ptr<Node>> results;
    collect_nodes(this, selector, results);
    return results;
}

std::shared_ptr<Node> Node::select_first(const std::string& selector) const {
    auto results = select(selector);
    return results.empty() ? nullptr : results.front();
}

std::shared_ptr<Node> Node::select_last(const std::string& selector) const {
    auto results = select(selector);
    return results.empty() ? nullptr : results.back();
}

std::shared_ptr<Document> Document::parse(const std::string& html_str) {
    auto doc = std::make_shared<Document>();
    
    size_t i = 0;
    size_t n = html_str.length();
    std::shared_ptr<Node> current = doc;

    while (i < n) {
        if (html_str[i] == '<') {
            if (i + 1 < n && html_str[i + 1] == '/') {
                size_t close_pos = html_str.find('>', i);
                if (close_pos != std::string::npos) {
                    if (auto p = current->parent()) {
                        current = p;
                    }
                    i = close_pos + 1;
                    continue;
                }
            } else if (i + 1 < n && html_str[i + 1] == '!') {
                size_t close_pos = html_str.find('>', i);
                if (close_pos != std::string::npos) {
                    i = close_pos + 1;
                    continue;
                }
            } else {
                size_t close_pos = html_str.find('>', i);
                if (close_pos != std::string::npos) {
                    std::string tag_content = html_str.substr(i + 1, close_pos - i - 1);
                    bool self_closing = false;
                    if (!tag_content.empty() && tag_content.back() == '/') {
                        self_closing = true;
                        tag_content.pop_back();
                    }

                    std::istringstream tag_ss(tag_content);
                    std::string tag_name;
                    tag_ss >> tag_name;

                    auto element = std::make_shared<Node>(NodeType::Element, tag_name);

                    std::string attr_pair;
                    while (tag_ss >> attr_pair) {
                        size_t eq_pos = attr_pair.find('=');
                        if (eq_pos != std::string::npos) {
                            std::string k = attr_pair.substr(0, eq_pos);
                            std::string v = attr_pair.substr(eq_pos + 1);
                            if (v.length() >= 2 && (v.front() == '"' || v.front() == '\'') && v.front() == v.back()) {
                                v = v.substr(1, v.length() - 2);
                            }
                            element->attr(k, v);
                        } else {
                            element->attr(attr_pair, "");
                        }
                    }

                    current->append_child(element);

                    if (!self_closing && tag_name != "img" && tag_name != "input" && tag_name != "br" && tag_name != "hr" && tag_name != "meta") {
                        current = element;
                    }

                    i = close_pos + 1;
                    continue;
                }
            }
        }

        size_t next_tag = html_str.find('<', i);
        if (next_tag == std::string::npos) next_tag = n;

        std::string text = html_str.substr(i, next_tag - i);
        if (!text.empty()) {
            auto text_node = std::make_shared<Node>(NodeType::Text);
            text_node->text_content = text;
            current->append_child(text_node);
        }
        i = next_tag;
    }

    return doc;
}

} // namespace nrp::modules::html
