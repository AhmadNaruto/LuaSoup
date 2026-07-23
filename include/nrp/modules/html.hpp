#ifndef NRP_MODULES_HTML_HPP
#define NRP_MODULES_HTML_HPP

#include "nrp/core/types.hpp"
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>

namespace nrp::modules::html {

enum class NodeType {
    Element = 1,
    Text = 3,
    Comment = 8,
    Document = 9
};

class Node : public std::enable_shared_from_this<Node> {
public:
    NodeType type{NodeType::Element};
    std::string tag;
    std::string text_content;
    std::unordered_map<std::string, std::string> attributes;
    std::weak_ptr<Node> parent_node;
    std::vector<std::shared_ptr<Node>> children;

    Node(NodeType t = NodeType::Element, std::string tag_name = "")
        : type(t), tag(std::move(tag_name)) {}

    void append_child(std::shared_ptr<Node> child) {
        if (child) {
            child->parent_node = shared_from_this();
            children.push_back(child);
        }
    }

    // --- JSoup / LexSoup Scraper APIs ---
    std::string attr(const std::string& name) const;
    void attr(const std::string& name, const std::string& value);
    bool has_attr(const std::string& name) const;
    void remove_attr(const std::string& name);

    std::string id() const { return attr("id"); }
    std::string class_name() const { return attr("class"); }
    bool has_class(const std::string& cls) const;
    void add_class(const std::string& cls);
    void remove_class(const std::string& cls);

    std::string text() const;
    std::string html() const;
    std::string outer_html() const;
    std::string tag_name() const { return tag; }

    std::shared_ptr<Node> parent() const { return parent_node.lock(); }
    std::vector<std::shared_ptr<Node>> child_elements() const;
    std::shared_ptr<Node> first_element_child() const;
    std::shared_ptr<Node> last_element_child() const;
    std::shared_ptr<Node> next_element_sibling() const;
    std::shared_ptr<Node> previous_element_sibling() const;

    // --- JSoup CSS Selector Query Engine ---
    std::vector<std::shared_ptr<Node>> select(const std::string& selector) const;
    std::shared_ptr<Node> select_first(const std::string& selector) const;
    std::shared_ptr<Node> select_last(const std::string& selector) const;

    // Backward compatibility aliases
    std::string get_attribute(const std::string& name) const { return attr(name); }
    void set_attribute(const std::string& name, const std::string& value) { attr(name, value); }
    bool has_attribute(const std::string& name) const { return has_attr(name); }
    std::string inner_text() const { return text(); }
    std::shared_ptr<Node> query_selector(const std::string& selector) const { return select_first(selector); }
    std::vector<std::shared_ptr<Node>> query_selector_all(const std::string& selector) const { return select(selector); }
};

class Document : public Node {
public:
    Document() : Node(NodeType::Document, "#document") {}
    
    static std::shared_ptr<Document> parse(const std::string& html_str);

    std::shared_ptr<Node> body() const { return select_first("body"); }
    std::shared_ptr<Node> head() const { return select_first("head"); }
    std::string title() const {
        auto title_elem = select_first("title");
        return title_elem ? title_elem->text() : "";
    }
};

} // namespace nrp::modules::html

#endif // NRP_MODULES_HTML_HPP
