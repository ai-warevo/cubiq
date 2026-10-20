#pragma once

#include <iostream>
#include "core/interfaces/inc/IEntity.hpp"
#include "core/interfaces/inc/ICamera.hpp"
#include "core/interfaces/inc/IViewAngleWriter.hpp"
#include "core/interfaces/inc/IPlayerProvider.hpp"
#include "platform/base/inc/IMemoryAccess.hpp"
#include "games/assaultcube/structures/inc/Offsets.hpp"

namespace cubiq::assaultcube::external {

/**
 * @brief Implementation of a player entity for AssaultCube.
 * Acts as the bridge between game memory and core interfaces.
 */
class ACPlayer : public cubiq::common::interfaces::IPlayer {
public:
    ACPlayer(const cubiq::platform::base::IMemoryAccess& mem_reader, uintptr_t module_base)
        : m_mem(mem_reader), m_module_base(module_base), m_local_player(0) {
        update_local_player();
    }

    /**
     * @brief Refreshes the cached local player pointer.
     */
    void update_local_player() {
        m_local_player = m_mem.read<uintptr_t>(m_module_base + cubiq::assaultcube::structures::local_player_ptr);
    }

    // IPositionable implementation (via IHealthEntity)
    cubiq::common::math::Vector3 get_position() const override {
        if (!m_local_player) return {};
        return m_mem.read<cubiq::common::math::Vector3>(m_local_player + cubiq::assaultcube::structures::player_pos_offset);
    }

    // IHealthEntity implementation
    uint32_t get_health(const cubiq::platform::base::IMemoryAccess& mem) const override {
        if (!m_local_player) return 0;
        return mem.read<uint32_t>(m_local_player + cubiq::assaultcube::structures::health_offset);
    }

    /**
     * @brief Sets the health of the entity.
     * @param mem The memory access implementation to use.
     * @param amount The new health value.
     * @return true if the operation succeeded, false otherwise.
     */
    bool set_health(const cubiq::platform::base::IMemoryAccess& mem, uint32_t amount) override {
        if (!m_local_player) {
            std::cout << "[ACPlayer] Failed to find local player! (local_player_ptr read 0)" << std::endl;
            return false;
        }
        uintptr_t health_addr = m_local_player + cubiq::assaultcube::structures::health_offset;
        std::cout << "[ACPlayer] Local Player: 0x" << std::hex << m_local_player << std::dec << std::endl;
        std::cout << "[ACPlayer] Health Address: 0x" << std::hex << health_addr << std::dec << " | Target Value: " << amount << std::endl;
        mem.write<uint32_t>(health_addr, amount);
        return true;
    }

    // ICamera implementation
    cubiq::common::math::Vector3 get_view_angles() const override {
        if (!m_local_player) return {};
        return m_mem.read<cubiq::common::math::Vector3>(m_local_player + cubiq::assaultcube::structures::view_angles_offset);
    }

    // IViewAngleWriter implementation
    void write_view_angles(const cubiq::common::math::Vector3& angles) override {
        if (!m_local_player) return;
        m_mem.write<cubiq::common::math::Vector3>(m_local_player + cubiq::assaultcube::structures::view_angles_offset, angles);
    }

private:
    const cubiq::platform::base::IMemoryAccess& m_mem;
    uintptr_t m_module_base;
    uintptr_t m_local_player;
};

} // namespace cubiq::assaultcube::external
