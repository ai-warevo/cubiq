#pragma once

#include "app/common/utils/inc/MemoryUtils.hpp"
#include "app/common/structures/inc/Offsets.hpp"

namespace cubiq::external {

class HealthModulator {
public:
    HealthModulator(const cubiq::common::utils::MemoryReaderWriter& mem_reader, uintptr_t module_base);
    void set_health(uint32_t amount);

private:
    const cubiq::common::utils::MemoryReaderWriter& m_mem;
    uintptr_t m_module_base;
};

} // namespace cubiq::external
