#include "games/assaultcube/external/inc/HealthModulator.hpp"

namespace cubiq::assaultcube::external {

HealthModulator::HealthModulator(const cubiq::platform::base::IMemoryAccess& mem_access, uintptr_t module_base)
    : m_mem(mem_access), m_module_base(module_base) {}

uint32_t HealthModulator::get_health(const cubiq::platform::base::IMemoryAccess& mem) const {
    uintptr_t local_player = mem.read<uintptr_t>(m_module_base + cubiq::assaultcube::structures::local_player_ptr);
    
    // Sanity check: ensure the pointer is within a reasonable range
    if (!mem.is_in_range(local_player, m_module_base, cubiq::platform::base::IMemoryAccess::kDefaultSanityRange)) {
        return 0;
    }

    return mem.read<uint32_t>(local_player + cubiq::assaultcube::structures::health_offset);
}

bool HealthModulator::set_health(const cubiq::platform::base::IMemoryAccess& mem, uint32_t amount) {
    uintptr_t local_player = mem.read<uintptr_t>(m_module_base + cubiq::assaultcube::structures::local_player_ptr);
    
    // Sanity check: ensure the pointer is within a reasonable range
    if (!mem.is_in_range(local_player, m_module_base, cubiq::platform::base::IMemoryAccess::kDefaultSanityRange)) {
        return false;
    }

    mem.write<uint32_t>(local_player + cubiq::assaultcube::structures::health_offset, amount);
    return true;
}

void HealthModulator::set_health(uint32_t amount) {
    set_health(m_mem, amount);
}

} // namespace cubiq::assaultcube::external

