#pragma once

#include "core/interfaces/inc/IPlugin.hpp"
#include "core/interfaces/inc/IPlayerProvider.hpp"
#include "core/interfaces/inc/IEntity.hpp"
#include "core/interfaces/inc/IPlayerProviderGameState.hpp"
#include "core/cheats/godmode/inc/GodModeConfig.hpp"
#include "platform/base/inc/IMemoryAccess.hpp"

namespace cubiq::common::cheats::godmode {

/**
 * @brief Plugin that provides God Mode functionality.
 */
class GodModePlugin : public cubiq::IPlugin {
public:
    explicit GodModePlugin(const GodModeConfig& config) 
        : m_config(config) {}

    /**
     * @brief Enables the plugin and returns its task loop.
     */
    cubiq::PluginTask enable(cubiq::IGameState& state) override {
        auto* specialized_state = dynamic_cast<cubiq::IPlayerProviderGameState*>(&state);
        if (!specialized_state) {
            return [](cubiq::IGameState&) { return cubiq::TaskResult::Stop; };
        }

        return [this, specialized_state](cubiq::IGameState&) -> cubiq::TaskResult {
            auto& player = specialized_state->get_player_provider().get_player();
            
            // We assume the player implements IHealthEntity. 
            // In a more robust system, we might check this once during enable.
            if (auto* health_entity = dynamic_cast<cubiq::common::interfaces::IHealthEntity*>(&player)) {
                this->execute(*health_entity, specialized_state->get_memory());
            }

            return cubiq::TaskResult::Continue;
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
