#pragma once

#include "core/interfaces/inc/IPlugin.hpp"
#include "core/interfaces/inc/IPlayerProvider.hpp"
#include "core/interfaces/inc/IEntity.hpp"
#include "core/interfaces/inc/IPlayerProviderGameState.hpp"
#include "core/cheats/godmode/inc/GodModeConfig.hpp"
#include "platform/base/inc/IMemoryAccess.hpp"
#include <iostream>

namespace cubiq::common::cheats::godmode {

/**
 * @brief Plugin that provides God Mode functionality.
 */
class GodModePlugin : public cubiq::common::interfaces::IPlugin {
public:
    explicit GodModePlugin(const GodModeConfig& config) 
        : m_config(config) {}

    /**
     * @brief Enables the plugin and returns its task loop.
     */
    cubiq::common::interfaces::PluginTask enable(cubiq::common::interfaces::IGameState& state) override {
        auto* specialized_state = dynamic_cast<cubiq::common::interfaces::IPlayerProviderGameState*>(&state);
        if (!specialized_state) {
            std::cout << "[GodModePlugin] Error: Failed to cast IGameState to IPlayerProviderGameState!" << std::endl;
            return [](cubiq::common::interfaces::IGameState&) { return cubiq::common::interfaces::TaskResult::Stop; };
        }

        struct TaskCache {
            const cubiq::common::interfaces::IPlayer* last_player = nullptr;
            cubiq::common::interfaces::IHealthEntity* cached_health_entity = nullptr;
        };
        auto cache = std::make_shared<TaskCache>();

        return [this, specialized_state, cache](cubiq::common::interfaces::IGameState&) -> cubiq::common::interfaces::TaskResult {
            auto& player = specialized_state->get_player_provider().get_player();
            
            if (&player != cache->last_player) {
                cache->cached_health_entity = dynamic_cast<cubiq::common::interfaces::IHealthEntity*>(&player);
                cache->last_player = &player;
                if (!cache->cached_health_entity) {
                    std::cout << "[GodModePlugin] Error: Player does not implement IHealthEntity!" << std::endl;
                }
            }

            if (cache->cached_health_entity) {
                bool success = this->execute(*cache->cached_health_entity, specialized_state->get_memory());
                if (!success) {
                    std::cout << "[GodModePlugin] Execute failed!" << std::endl;
                }
            }

            return cubiq::common::interfaces::TaskResult::Continue;
        };
    }

    /**
     * @brief Disables the plugin and cleans up resources.
     */
    void disable() override {
        // Reset any internal state if needed.
    }

    /**
     * @brief Executes the god mode logic on the given entity.
     * @param entity The entity to apply god mode to.
     * @param mem The memory access implementation.
     * @return true if the operation succeeded, false otherwise.
     */
    bool execute(cubiq::common::interfaces::IHealthEntity& entity, cubiq::platform::base::IMemoryAccess& mem) const {
        return entity.set_health(mem, m_config.health_value);
    }

private:
    GodModeConfig m_config;
};

} // namespace cubiq::common::cheats::godmode
