#pragma once

#include <iostream>
#include "core/interfaces/inc/IEntity.hpp"
#include "core/interfaces/inc/ICamera.hpp"
#include "core/interfaces/inc/IViewAngleWriter.hpp"
#include "platform/base/inc/IMemoryAccess.hpp"
#include "games/assaultcube/structures/inc/Offsets.hpp"

namespace cubiq::assaultcube::external {

/**
 * @brief Implementation of a player entity for AssaultCube.
 * Acts as the bridge between game memory and core interfaces.
 */
class ACPlayer : public cubiq::common::interfaces::IHealthEntity,
                 public cubiq::common::interfaces::ICamera,
                 public cubiq::common::interfaces::IViewAngleWriter {
public:
    ACPlayer(const cubiq::platform::base::IMemoryAccess& mem_reader, uintptr_t module_base)
        : m_mem(mem_reader), m_module_base(module_base) {}

    // IPositionable implementation (via IHealthEntity)
    cubiq::common::math::Vector3 get_position() const override {
        uintptr_t local_player = m_mem.read<uintptr_t>(m_module_base + cubiq::assaultcube::offsets::local_player_ptr);
        if (!local_player) return {};
        return m_mem.read<cubiq::common::math::Vector3>(local_player + cubiq::assaultcube::offsets::player_pos_offset);
    }

    // IHealthEntity implementation
    uint32_t get_health(const cubiq::platform::base::IMemoryAccess& mem) const override {
        uintptr_t local_player = m_mem.read<uintptr_t>(m_module_base + cubiq::assaultcube::offsets::local_player_ptr);
        if (!local_player) return 0;
        return mem.read<uint32_t>(local_player + cubiq::assaultcube::offsets::health_offset);
    }

    void set_health(const cubiq::platform::base::IMemoryAccess& mem, uint32_t amount) override {
        uintptr_t local_player = m_mem.read<uintptr_t>(m_module_base + cubiq::assaultcube::offsets::local_player_ptr);
        if (!local_player) {
            std::cout << "[ACPlayer] Failed to find local player! (local_player_ptr read 0)" << std::endl;
            return;
        }
        uintptr_t health_addr = local_player + cubiq::assaultcube::offsets::health_offset;
        std::cout << "[ACPlayer] Local Player: 0x" << std::hex << local_player << std::dec << std::endl;
        std::cout << "[ACPlayer] Health Address: 0x" << std::hex << health_addr << std::dec << " | Target Value: " << amount << std::endl;
        mem.write<uint32_t>(health_addr, amount);
    }

    // ICamera implementation
    cubiq::common::math::Vector3 get_view_angles() const override {
        uintptr_t local_player = m_mem.read<uintptr_t>(m_module_base + cubiq::assaultcube::offsets::local_player_ptr);
        if (!local_player) return {};
        return m_mem.read<cubiq::common::math::Vector3>(local_player + cubiq::assaultcube::offsets::view_angles_offset);
    }

    // IViewAngleWriter implementation
    void write_view_angles(const cubiq::common::math::Vector3& angles) override {
        uintptr_t local_player = m_mem.read<uintptr_t>(m_module_base + cubiq::assaultcube::offsets::local_player_ptr);
        if (!local_player) return;
        m_mem.write<cubiq::common::math::Vector3>(local_player + cubiq::assaultcube::offsets::view_angles_offset, angles);
    }

private:
    const cubiq::platform::base::IMemoryAccess& m_mem;
    uintptr_t m_module_base;
};

} // namespace cubiq::assaultcube::external
