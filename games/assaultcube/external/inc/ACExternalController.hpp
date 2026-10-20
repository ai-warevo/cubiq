#pragma once

#include "core/interfaces/inc/IGameState.hpp"
#include "core/interfaces/inc/IPlugin.hpp"
#include "platform/base/inc/IInput.hpp"
#include "platform/base/inc/IMemoryAccess.hpp"
#include "core/modes/external/inc/ExternalEngine.hpp"
#include <algorithm>
#include <unordered_map>
#include <utility>
#include <vector>

namespace cubiq::assaultcube::external {

/**
 * @brief Controller that manages plugin execution and input mapping for AssaultCube.
 * Acts as the "Brain" of the system.
 */
class ACExternalController {
public:
    ACExternalController(cubiq::IInput& input, 
                         cubiq::core::modes::external::ExternalEngine& engine,
                         const std::vector<cubiq::IPlugin*>& plugins)
        : m_input(input), m_engine(engine), m_plugins(plugins) {}

    /**
     * @brief Binds a key to a plugin trigger.
     */
    void bind(cubiq::Key key, cubiq::IPlugin* plugin) {
        m_mappings[key] = plugin;
    }

    /**
     * @brief Executes the control loop: handles input and updates active tasks.
     */
    void update(cubiq::assaultcube::external::ACGameState& state, cubiq::platform::base::IMemoryAccess& mem, uintptr_t module_base) {
        // 0. Update State
        state.update(mem, module_base);

        // 1. Handle Input Mapping
        for (auto const& [key, plugin] : m_mappings) {
            if (m_input.is_key_pressed(key)) {
                trigger_plugin(*plugin, state);
            }
        }

        // 2. Handle System Keys
        if (m_input.is_key_down(cubiq::Key::Escape)) {
            m_engine.stop();
        }

        // 3. Execute all active tasks and prune finished ones
        std::erase_if(m_active_tasks, [&](auto& pair) {
            auto& [plugin, task] = pair;
            if (task(state) == cubiq::TaskResult::Stop) {
                plugin->disable();
                return true;
            }
            return false;
        });
    }

    /**
     * @brief Triggers a plugin (toggles it) and adds its resulting task to the active list.
     */
    void trigger_plugin(cubiq::IPlugin& plugin, cubiq::IGameState& state) {
        if (auto it = m_active_tasks.find(&plugin); it != m_active_tasks.end()) {
            // Plugin is already running -> Disable it
            plugin.disable();
            m_active_tasks.erase(it);
        } else {
            // Plugin is not running -> Enable it
            m_active_tasks[&plugin] = plugin.enable(state);
        }
    }

private:
    cubiq::IInput& m_input;
    cubiq::core::modes::external::ExternalEngine& m_engine;
    std::vector<cubiq::IPlugin*> m_plugins;
    std::unordered_map<cubiq::Key, cubiq::IPlugin*> m_mappings;
    std::unordered_map<cubiq::IPlugin*, cubiq::PluginTask> m_active_tasks;
};

} // namespace cubiq::assaultcube::external
