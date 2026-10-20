#pragma once

#include "core/interfaces/inc/IPlugin.hpp"
#include "core/interfaces/inc/IPlayerProvider.hpp"
#include "core/interfaces/inc/IEntity.hpp"
#include "core/interfaces/inc/ICamera.hpp"
#include "core/interfaces/inc/IViewAngleWriter.hpp"
#include "core/interfaces/inc/IPlayerProviderGameState.hpp"
#include "core/math/inc/MathConstants.hpp"
#include <cmath>
#include <iostream>

namespace cubiq::common::cheats::aimbot {

/**
 * @brief Plugin that provides Aimbot functionality.
 */
class AimbotPlugin : public cubiq::IPlugin {
public:
    struct Config {
        float smoothing = 1.0f;
        bool enabled = true;
    };

    explicit AimbotPlugin(const Config& config) : m_config(config) {}

    /**
     * @brief Enables the plugin and returns its task loop.
     */
    cubiq::PluginTask enable(cubiq::IGameState& state) override {
        auto* specialized_state = dynamic_cast<cubiq::IPlayerProviderGameState*>(&state);
        if (!specialized_state) {
            std::cout << "[AimbotPlugin] Error: Failed to cast IGameState to IPlayerProviderGameState!" << std::endl;
            return [](cubiq::IGameState&) { return cubiq::TaskResult::Stop; };
        }

        return [this, specialized_state](cubiq::IGameState&) -> cubiq::TaskResult {
            if (!m_config.enabled) return cubiq::TaskResult::Stop;

            auto& player = specialized_state->get_player_provider().get_player();
            
            execute(player, player, player);

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
     * @brief Executes the aimbot logic on a target.
     * @param target The entity to aim at.
     * @param camera The current camera view.
     * @param writer The interface to apply angles.
     */
    void execute(const cubiq::common::interfaces::IPositionable& target,
                 const cubiq::common::interfaces::ICamera& camera,
                 cubiq::common::interfaces::IViewAngleWriter& writer) const {
        if (!m_config.enabled) return;

        auto target_pos = target.get_position();
        auto cam_pos = camera.get_position();
        auto current_angles = camera.get_view_angles();

        // Calculate delta
        float dx = target_pos.x - cam_pos.x;
        float dy = target_pos.y - cam_pos.y;
        float dz = target_pos.z - cam_pos.z;

        // Calculate yaw and pitch (simplified)
        float yaw = std::atan2(dy, dx);
        float distance_xz = std::sqrt(dx * dx + dy * dy);
        float pitch = std::atan2(-dz, distance_xz);

        const float rad_to_deg = cubiq::common::math::constants::RAD_TO_DEG;

        cubiq::common::math::Vector3 target_angles;
        target_angles.x = pitch * rad_to_deg; // Pitch
        target_angles.y = yaw * rad_to_deg;   // Yaw
        target_angles.z = 0.0f;

        // Apply smoothing (very basic)
        if (m_config.smoothing > 1.0f) {
            target_angles.x = current_angles.x + (target_angles.x - current_angles.x) / m_config.smoothing;
            target_angles.y = current_angles.y + (target_angles.y - current_angles.y) / m_config.smoothing;
        }

        writer.write_view_angles(target_angles);
    }

private:
    Config m_config;
};

} // namespace cubiq::common::cheats::aimbot

