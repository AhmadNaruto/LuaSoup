#ifndef NRP_REFLECTION_REGISTRY_HPP
#define NRP_REFLECTION_REGISTRY_HPP

#include "nrp/core/types.hpp"
#include <string>
#include <vector>
#include <unordered_map>
#include <memory>
#include <mutex>

namespace nrp {

struct PropertyDescriptor {
    std::string name;
    TypeKind type;
    bool readonly{false};
    bool nullable{false};
    std::string documentation;
};

struct ParameterDescriptor {
    std::string name;
    TypeKind type;
    bool nullable{false};
};

struct MethodDescriptor {
    std::string name;
    TypeKind return_type;
    std::vector<ParameterDescriptor> parameters;
    std::string documentation;
};

struct ClassDescriptor {
    std::string name;
    std::string namespace_name;
    std::string parent_class;
    std::vector<PropertyDescriptor> properties;
    std::vector<MethodDescriptor> methods;
    std::string documentation;
};

class ReflectionRegistry {
private:
    std::mutex mutex_;
    std::unordered_map<std::string, ClassDescriptor> classes_;

public:
    static ReflectionRegistry& instance() {
        static ReflectionRegistry reg;
        return reg;
    }

    void register_class(ClassDescriptor desc) {
        std::lock_guard<std::mutex> lock(mutex_);
        classes_[desc.name] = std::move(desc);
    }

    const ClassDescriptor* find_class(const std::string& name) const {
        std::lock_guard<std::mutex> lock(const_cast<std::mutex&>(mutex_));
        auto it = classes_.find(name);
        if (it != classes_.end()) {
            return &it->second;
        }
        return nullptr;
    }

    std::vector<std::string> get_registered_classes() const {
        std::lock_guard<std::mutex> lock(const_cast<std::mutex&>(mutex_));
        std::vector<std::string> names;
        names.reserve(classes_.size());
        for (const auto& [name, _] : classes_) {
            names.push_back(name);
        }
        return names;
    }
};

} // namespace nrp

#endif // NRP_REFLECTION_REGISTRY_HPP
