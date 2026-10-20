#pragma once

#include "core/interfaces/inc/IEntity.hpp"
#include "platform/base/inc/IMemoryAccess.hpp"
#include "games/assaultcube/structures/inc/Offsets.hpp"

namespace cubiq::external {

class HealthModulator : public cubiq::common::interfaces::IHealthEntity {
public:
    HealthModulator(const cubiq::platform::base::IMemoryAccess& mem_access, uintptr_t module_base);

    // IPositionable implementation (placeholder for now)
    cubiq::common::math::Vector3 get_position() const override { return {}; }

    // IHealthEntity implementation
    uint32_t get_health(const cubiq::platform::base::IMemoryAccess& mem) const override;
    bool set_health(const cubiq::platform::base::IMemoryAccess& mem, uint32_t amount) override;

    // Convenience method for existing code
    void set_health(uint32_t amount);

private:
    const cubiq::platform::base::IMemoryAccess& m_mem;
    uintptr_t m_module_base;
};

} // namespace cubiq::external

