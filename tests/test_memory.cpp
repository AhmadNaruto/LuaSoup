#include "nrp/core/memory.hpp"
#include <cassert>
#include <iostream>

struct DummyObject : public nrp::RefCounted {
    int value{42};
};

int main() {
    std::cout << "Running Memory Architecture Tests..." << std::endl;

    auto& mgr = nrp::MemoryManager::instance();
    mgr.reset();

    nrp::Handle h1 = mgr.register_object<DummyObject>(1, nrp::OwnershipType::Shared);
    assert(h1.is_valid());
    assert(mgr.active_objects() == 1);

    auto ptr = mgr.get(h1);
    assert(ptr != nullptr);
    auto dummy = std::static_pointer_cast<DummyObject>(ptr);
    assert(dummy->value == 42);

    assert(mgr.release(h1));
    assert(mgr.active_objects() == 0);

    // Verify handle invalidation
    assert(mgr.get(h1) == nullptr);

    std::cout << "Memory Architecture Tests Passed!" << std::endl;
    return 0;
}
