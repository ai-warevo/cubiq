#pragma once

#include "core/interfaces/inc/IGameState.hpp"
#include "core/interfaces/inc/IPlayerProvider.hpp"
#include "core/interfaces/inc/IPlayerProviderGameState.hpp"
#include "games/assaultcube/external/inc/ACPlayer.hpp"
#include <memory>

namespace cubiq::assaultcube::external {

/**
 * @brief Implementation of the game state for AssaultCube.
 * Manages the lifecycle of the ACPlayer and provides access to memory and module base.
 */
class ACGameState : public cubiq::IPlayerProviderGameState, public cubiq::IPlayerProvider {
public:
    ACGameState() 
        : m_mem(nullptr), m_module_base(0), m_player(nullptr) {}

    ACGameState(cubiq::platform::base::IMemoryAccess& mem_access, uintptr_t module_base)
        : m_mem(&mem_access), m_module_base(module_base), 
          m_player(std::make_unique<ACPlayer>(*m_mem, m_module_base)) {}

    cubiq::platform::base::IMemoryAccess& get_memory() override { return *m_mem; }
    uintptr_t get_module_base() override { return m_module_base; }
    cubiq::IPlayer& get_player() override { return *m_player; }

    /**
     * @brief Provides access to the player provider.
     */
    cubiq::IPlayerProvider& get_player_provider() override { return *this; }

    /**
     * @brief Refreshes the internal player data with new memory access or module base.
     */
    void update(cubiq::platform::base::IMemoryAccess& mem, uintptr_t module_base) {
        if (m_mem != &mem || m_module_base != module_base) {
            m_mem = &mem;
            m_module_base = module_base;
            m_player = std::make_unique<ACPlayer>(*m_mem, m_module_base);
        }
    }

private:
    cubiq::platform::base::IMemoryAccess* m_mem;
    uintptr_t m_module_base;
    std::unique_ptr<cubiq::assaultcube::external::ACPlayer> m_player;
};

} // namespace cubiq::assaultcube::external
