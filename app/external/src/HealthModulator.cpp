#include "app/external/inc/HealthModulator.hpp"

namespace cubiq::external {

HealthModulator::HealthModulator(const cubiq::common::utils::MemoryReaderWriter& mem_reader, uintptr_t module_base)
    : m_mem(mem_reader), m_module_base(module_base) {}

void HealthModulator::set_health(uint32_t amount) {
    uintptr_t local_player = m_mem.read<uintptr_t>(m_module_base + cubiq::common::offsets::local_player_ptr);
    if (!local_player) return;

    m_mem.write<uint32_t>(local_player + cubiq::common::offsets::health_offset, amount);
}

} // namespace cubiq::external
