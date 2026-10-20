#pragma once

#include <iostream>
#include "core/interfaces/inc/IEntity.hpp"
#include "core/cheats/godmode/inc/GodModeConfig.hpp"
#include "platform/base/inc/IMemoryAccess.hpp"

namespace cubiq::common::cheats::godmode {

/**
 * @brief Plugin that provides God Mode functionality.
 */
class GodModePlugin {
public:
    explicit GodModePlugin(const GodModeConfig& config) 
        : m_config(config) {}

    /**
     * @brief Executes the god mode logic on the given entity.
     * @param entity The entity to apply god mode to.
     * @param mem The memory access implementation.
     */
    void execute(cubiq::common::interfaces::IHealthEntity& entity, cubiq::platform::base::IMemoryAccess& mem) const {
        std::cout << "[GodModePlugin] Executing god mode..." << std::endl;
        // For now, we just set it to a fixed value or use config if we add it.
        entity.set_health(mem, 10000); 
        std::cout << "[GodModePlugin] Finished executing god mode." << std::endl;
    }

private:
    GodModeConfig m_config;
};

} // namespace cubiq::common::cheats::godmode
