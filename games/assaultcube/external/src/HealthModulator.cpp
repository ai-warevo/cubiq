#include "games/assaultcube/external/inc/HealthModulator.hpp"

namespace cubiq::external {

HealthModulator::HealthModulator(const cubiq::platform::base::IMemoryAccess& mem_access, uintptr_t module_base)
    : m_mem(mem_access), m_module_base(module_base) {}

uint32_t HealthModulator::get_health(const cubiq::platform::base::IMemoryAccess& mem) const {
    uintptr_t local_player = mem.read<uintptr_t>(m_module_base + cubiq::assaultcube::offsets::local_player_ptr);
    if (!local_player) return 0;
    return mem.read<uint32_t>(local_player + cubiq::assaultcube::offsets::health_offset);
}

void HealthModulator::set_health(const cubiq::platform::base::IMemoryAccess& mem, uint32_t amount) {
    uintptr_t local_player = mem.read<uintptr_t>(m_module_base + cubiq::assaultcube::offsets::local_player_ptr);
    if (!local_player) return;

    mem.write<uint32_t>(local_player + cubiq::assaultcube::offsets::health_offset, amount);
}

void HealthModulator::set_health(uint32_t amount) {
    set_health(m_mem, amount);
}

} // namespace cubiq::external

