#ifndef NRP_CORE_RUNTIME_HPP
#define NRP_CORE_RUNTIME_HPP

#include "memory.hpp"
#include "service.hpp"
#include "types.hpp"
#include <string>
#include <memory>
#include <atomic>

namespace nrp {

class Runtime {
private:
    std::string id_;
    std::atomic<bool> initialized_{false};

public:
    explicit Runtime(std::string id = "default");
    ~Runtime();

    void initialize();
    void shutdown();
    bool is_initialized() const noexcept { return initialized_.load(); }
    const std::string& id() const noexcept { return id_; }

    MemoryManager& memory() { return MemoryManager::instance(); }
    ServiceRegistry& services() { return ServiceRegistry::instance(); }
};

} // namespace nrp

#endif // NRP_CORE_RUNTIME_HPP
