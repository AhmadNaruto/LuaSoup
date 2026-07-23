#ifndef NRP_CORE_SERVICE_HPP
#define NRP_CORE_SERVICE_HPP

#include <string>
#include <memory>
#include <unordered_map>
#include <typeindex>
#include <mutex>
#include <functional>
#include <vector>

namespace nrp {

class Service {
public:
    virtual ~Service() = default;
    virtual std::string name() const = 0;
    virtual void initialize() = 0;
    virtual void shutdown() = 0;
};

// 1. Cache Service (LRU Key-Value Cache)
class CacheService : public Service {
private:
    std::mutex mutex_;
    std::unordered_map<std::string, std::string> cache_;

public:
    std::string name() const override { return "CacheService"; }
    void initialize() override {}
    void shutdown() override { std::lock_guard<std::mutex> lock(mutex_); cache_.clear(); }

    void put(const std::string& key, const std::string& val) {
        std::lock_guard<std::mutex> lock(mutex_);
        cache_[key] = val;
    }

    std::string get(const std::string& key) const {
        std::lock_guard<std::mutex> lock(const_cast<std::mutex&>(mutex_));
        auto it = cache_.find(key);
        return (it != cache_.end()) ? it->second : "";
    }
};

// 2. Event Service (Pub-Sub Listener System)
class EventService : public Service {
public:
    using EventHandler = std::function<void(const std::string& event, const std::string& payload)>;

private:
    mutable std::mutex mutex_;
    std::unordered_map<std::string, std::vector<EventHandler>> listeners_;

public:
    std::string name() const override { return "EventService"; }
    void initialize() override {}
    void shutdown() override { std::lock_guard<std::mutex> lock(mutex_); listeners_.clear(); }

    void subscribe(const std::string& event, EventHandler handler) {
        std::lock_guard<std::mutex> lock(mutex_);
        listeners_[event].push_back(handler);
    }

    void emit(const std::string& event, const std::string& payload) {
        std::lock_guard<std::mutex> lock(mutex_);
        auto it = listeners_.find(event);
        if (it != listeners_.end()) {
            for (const auto& handler : it->second) {
                handler(event, payload);
            }
        }
    }
};

// 3. Configuration Service
class ConfigurationService : public Service {
private:
    mutable std::mutex mutex_;
    std::unordered_map<std::string, std::string> configs_;

public:
    std::string name() const override { return "ConfigurationService"; }
    void initialize() override {}
    void shutdown() override { std::lock_guard<std::mutex> lock(mutex_); configs_.clear(); }

    void set(const std::string& key, const std::string& val) {
        std::lock_guard<std::mutex> lock(mutex_);
        configs_[key] = val;
    }

    std::string get(const std::string& key, const std::string& default_val = "") const {
        std::lock_guard<std::mutex> lock(mutex_);
        auto it = configs_.find(key);
        return (it != configs_.end()) ? it->second : default_val;
    }
};

// 4. Feature Service (Feature Flags)
class FeatureService : public Service {
private:
    mutable std::mutex mutex_;
    std::unordered_map<std::string, bool> flags_;

public:
    std::string name() const override { return "FeatureService"; }
    void initialize() override {}
    void shutdown() override { std::lock_guard<std::mutex> lock(mutex_); flags_.clear(); }

    void enable(const std::string& feature) {
        std::lock_guard<std::mutex> lock(mutex_);
        flags_[feature] = true;
    }

    bool is_enabled(const std::string& feature) const {
        std::lock_guard<std::mutex> lock(mutex_);
        auto it = flags_.find(feature);
        return (it != flags_.end()) ? it->second : false;
    }
};

class ServiceRegistry {
private:
    mutable std::mutex mutex_;
    std::unordered_map<std::type_index, std::shared_ptr<Service>> services_;

public:
    static ServiceRegistry& instance() {
        static ServiceRegistry reg;
        return reg;
    }

    template <typename T, typename... Args>
    std::shared_ptr<T> register_service(Args&&... args) {
        std::lock_guard<std::mutex> lock(mutex_);
        auto svc = std::make_shared<T>(std::forward<Args>(args)...);
        svc->initialize();
        services_[std::type_index(typeid(T))] = svc;
        return svc;
    }

    template <typename T>
    std::shared_ptr<T> get_service() const {
        std::lock_guard<std::mutex> lock(mutex_);
        auto it = services_.find(std::type_index(typeid(T)));
        if (it != services_.end()) {
            return std::static_pointer_cast<T>(it->second);
        }
        return nullptr;
    }

    void shutdown_all() {
        std::lock_guard<std::mutex> lock(mutex_);
        for (auto& [type, svc] : services_) {
            if (svc) {
                svc->shutdown();
            }
        }
        services_.clear();
    }
};

} // namespace nrp

#endif // NRP_CORE_SERVICE_HPP
