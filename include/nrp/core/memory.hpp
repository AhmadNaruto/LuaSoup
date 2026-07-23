#ifndef NRP_CORE_MEMORY_HPP
#define NRP_CORE_MEMORY_HPP

#include "handle.hpp"
#include <atomic>
#include <memory>
#include <unordered_map>
#include <mutex>
#include <vector>
#include <string>
#include <iostream>

namespace nrp {

class RefCounted {
private:
    mutable std::atomic<uint32_t> ref_count_{1};
    mutable std::atomic<uint32_t> weak_count_{0};

public:
    RefCounted() = default;
    virtual ~RefCounted() = default;

    void add_ref() const noexcept {
        ref_count_.fetch_add(1, std::memory_order_relaxed);
    }

    bool release() const noexcept {
        if (ref_count_.fetch_sub(1, std::memory_order_acq_rel) == 1) {
            return true;
        }
        return false;
    }

    uint32_t ref_count() const noexcept {
        return ref_count_.load(std::memory_order_relaxed);
    }
};

class MemoryManager {
private:
    struct Slot {
        uint16_t generation{1};
        bool active{false};
        std::shared_ptr<RefCounted> ptr{nullptr};
    };

    mutable std::mutex mutex_;
    std::vector<Slot> slots_;
    std::vector<uint32_t> free_indices_;
    std::atomic<size_t> allocated_bytes_{0};
    std::atomic<size_t> active_objects_{0};

    MemoryManager() {
        slots_.reserve(1024);
    }

public:
    static MemoryManager& instance() {
        static MemoryManager mgr;
        return mgr;
    }

    template <typename T, typename... Args>
    Handle register_object(uint8_t type_id, OwnershipType own, Args&&... args) {
        std::lock_guard<std::mutex> lock(mutex_);
        auto obj = std::make_shared<T>(std::forward<Args>(args)...);

        uint32_t idx;
        if (!free_indices_.empty()) {
            idx = free_indices_.back();
            free_indices_.pop_back();
        } else {
            idx = static_cast<uint32_t>(slots_.size());
            slots_.emplace_back();
        }

        auto& slot = slots_[idx];
        slot.active = true;
        slot.ptr = obj;

        active_objects_.fetch_add(1, std::memory_order_relaxed);
        allocated_bytes_.fetch_add(sizeof(T), std::memory_order_relaxed);

        return Handle::create(type_id, slot.generation, idx, own);
    }

    std::shared_ptr<RefCounted> get(Handle h) const {
        if (!h.is_valid()) return nullptr;
        std::lock_guard<std::mutex> lock(mutex_);

        uint32_t idx = h.index();
        if (idx >= slots_.size()) return nullptr;

        const auto& slot = slots_[idx];
        if (!slot.active || slot.generation != h.generation()) {
            return nullptr;
        }

        return slot.ptr;
    }

    bool release(Handle h) {
        if (!h.is_valid()) return false;
        std::lock_guard<std::mutex> lock(mutex_);

        uint32_t idx = h.index();
        if (idx >= slots_.size()) return false;

        auto& slot = slots_[idx];
        if (!slot.active || slot.generation != h.generation()) {
            return false;
        }

        slot.active = false;
        slot.ptr.reset();
        slot.generation++;
        free_indices_.push_back(idx);

        active_objects_.fetch_sub(1, std::memory_order_relaxed);
        return true;
    }

    size_t active_objects() const noexcept { return active_objects_.load(); }
    size_t allocated_bytes() const noexcept { return allocated_bytes_.load(); }

    void reset() {
        std::lock_guard<std::mutex> lock(mutex_);
        slots_.clear();
        free_indices_.clear();
        active_objects_ = 0;
        allocated_bytes_ = 0;
    }
};

} // namespace nrp

#endif // NRP_CORE_MEMORY_HPP
