#pragma once

#include <iostream>
#include "core/interfaces/inc/IPlugin.hpp"
#include "core/interfaces/inc/IPlayerProvider.hpp"
#include "core/interfaces/inc/IEntity.hpp"
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
        return [this](cubiq::IGameState& state) -> cubiq::TaskResult {
            auto* player_provider = dynamic_cast<cubiq::IPlayerProvider*>(&state);
            if (!player_provider) return cubiq::TaskResult::Stop;

            auto& player = player_provider->get_player();
            auto* health_entity = dynamic_cast<cubiq::common::interfaces::IHealthEntity*>(&player);
            if (!health_entity) return cubiq::TaskResult::Stop;

            auto& mem = state.get_memory();
            this->execute(*health_entity, mem);

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
        std::cout << "[GodModePlugin] Executing god mode..." << std::endl;
        // For now, we just set it to a fixed value or use config if we add it.
        bool success = entity.set_health(mem, 10000);
        std::cout << "[GodModePlugin] Finished executing god mode." << std::endl;
        return success;
    }

private:
    GodModeConfig m_config;
};

} // namespace cubiq::common::cheats::godmode
