#pragma once
#include <cstdint>
#include<functional>

struct LightHandle {
    uint32_t value{ 0 };

    bool operator==(const LightHandle& other) const {
        return value == other.value;
    }
};

namespace std {
    template<>
    struct hash<LightHandle> {
        size_t operator()(const LightHandle& h) const noexcept {
            return std::hash<uint32_t>{}(h.value);
        }
    };
}
