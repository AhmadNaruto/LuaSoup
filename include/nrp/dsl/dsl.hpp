#ifndef NRP_DSL_HPP
#define NRP_DSL_HPP

#include "nrp/modules/html.hpp"
#include "nrp/modules/json.hpp"
#include "nrp/modules/crypto.hpp"
#include <string>
#include <memory>
#include <vector>

namespace nrp::dsl {

// 1. HTML Fluent DSL Builder
class HTMLBuilder {
private:
    std::shared_ptr<modules::html::Node> root_;
    std::shared_ptr<modules::html::Node> current_;

public:
    explicit HTMLBuilder(std::string root_tag = "div") {
        root_ = std::make_shared<modules::html::Node>(modules::html::NodeType::Element, std::move(root_tag));
        current_ = root_;
    }

    HTMLBuilder& attr(const std::string& k, const std::string& v) {
        current_->attr(k, v);
        return *this;
    }

    HTMLBuilder& id(const std::string& val) {
        return attr("id", val);
    }

    HTMLBuilder& add_class(const std::string& cls) {
        current_->add_class(cls);
        return *this;
    }

    HTMLBuilder& text(const std::string& txt) {
        auto tnode = std::make_shared<modules::html::Node>(modules::html::NodeType::Text);
        tnode->text_content = txt;
        current_->append_child(tnode);
        return *this;
    }

    HTMLBuilder& tag(const std::string& child_tag) {
        auto elem = std::make_shared<modules::html::Node>(modules::html::NodeType::Element, child_tag);
        current_->append_child(elem);
        current_ = elem;
        return *this;
    }

    std::string build_html() const {
        return root_->outer_html();
    }
};

// 2. JSON Fluent DSL Builder
class JSONBuilder {
private:
    ObjectMap map_;

public:
    JSONBuilder() = default;

    JSONBuilder& set(const std::string& key, Value val) {
        map_[key] = std::move(val);
        return *this;
    }

    JSONBuilder& set(const std::string& key, const std::string& val) {
        map_[key] = Value(val);
        return *this;
    }

    JSONBuilder& set(const std::string& key, const char* val) {
        map_[key] = Value(std::string(val));
        return *this;
    }

    JSONBuilder& set(const std::string& key, int32_t val) {
        map_[key] = Value(static_cast<int64_t>(val));
        return *this;
    }

    JSONBuilder& set(const std::string& key, int64_t val) {
        map_[key] = Value(val);
        return *this;
    }

    JSONBuilder& set(const std::string& key, bool val) {
        map_[key] = Value(val);
        return *this;
    }

    std::string build_json() const {
        return modules::json::Json::stringify(Value(map_));
    }
};

} // namespace nrp::dsl

#endif // NRP_DSL_HPP
