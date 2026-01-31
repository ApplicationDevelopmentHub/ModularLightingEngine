#pragma once
#include <cstdint>
#include <functional>

struct PrimitiveHandle {
    uint32_t value = 0;
};

inline bool operator==(PrimitiveHandle a, PrimitiveHandle b) {
    return a.value == b.value;
}

namespace std {
    template<>
    struct hash<PrimitiveHandle> {
        size_t operator()(const PrimitiveHandle& h) const noexcept {
            return hash<uint32_t>{}(h.value);
        }
    };
}
