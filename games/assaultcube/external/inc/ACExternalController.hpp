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
#include <iostream>
#include <functional>

namespace cubiq::assaultcube::external {

/**
 * @brief Controller that manages plugin execution and input mapping for AssaultCube.
 * Acts as the "Brain" of the system.
 */
class ACExternalController {
public:
    ACExternalController(cubiq::platform::base::IInput& input, 
                         cubiq::common::modes::external::ExternalEngine& engine,
                         const std::vector<std::reference_wrapper<cubiq::common::interfaces::IPlugin>>& plugins)
        : m_input(input), m_engine(engine), m_plugins(plugins) {}

    /**
     * @brief Binds a key to a plugin trigger.
     */
    void bind(cubiq::platform::base::Key key, cubiq::common::interfaces::IPlugin& plugin) {
        m_mappings.insert_or_assign(key, std::ref(plugin));
    }

    /**
     * @brief Executes the control loop: handles input and updates active tasks.
     */
    void update(cubiq::assaultcube::external::ACGameState& state, cubiq::platform::base::IMemoryAccess& mem, uintptr_t module_base) {
        // 0. Update State
        state.update(mem, module_base);

        // 1. Handle Input Mapping
        for (auto const& [key, plugin_ref] : m_mappings) {
            if (m_input.is_key_pressed(key)) {
                std::cout << "[ACExternalController] Key pressed: " << static_cast<int>(key) << ". Triggering plugin." << std::endl;
                trigger_plugin(plugin_ref.get(), state);
            }
        }

        // 2. Handle System Keys
        if (m_input.is_key_down(cubiq::platform::base::Key::Escape)) {
            std::cout << "[ACExternalController] Escape pressed. Stopping engine." << std::endl;
            m_engine.stop();
        }

        // 3. Execute all active tasks and prune finished ones
        std::erase_if(m_active_tasks, [&](auto& pair) {
            auto& [plugin, task] = pair;
            cubiq::common::interfaces::TaskResult result = task(state);
            if (result == cubiq::common::interfaces::TaskResult::Stop) {
                std::cout << "[ACExternalController] Task stopped. Disabling plugin." << std::endl;
                plugin->disable();
                return true;
            }
            return false;
        });
    }

    /**
     * @brief Triggers a plugin (toggles it) and adds its resulting task to the active list.
     */
    void trigger_plugin(cubiq::common::interfaces::IPlugin& plugin, cubiq::common::interfaces::IGameState& state) {
        if (auto it = m_active_tasks.find(&plugin); it != m_active_tasks.end()) {
            // Plugin is already running -> Disable it
            std::cout << "[ACExternalController] Toggling plugin: Disabling." << std::endl;
            plugin.disable();
            m_active_tasks.erase(it);
        } else {
            // Plugin is not running -> Enable it
            std::cout << "[ACExternalController] Toggling plugin: Enabling." << std::endl;
            m_active_tasks[&plugin] = plugin.enable(state);
        }
    }

private:
    cubiq::platform::base::IInput& m_input;
    cubiq::common::modes::external::ExternalEngine& m_engine;
    std::vector<std::reference_wrapper<cubiq::common::interfaces::IPlugin>> m_plugins;
    std::unordered_map<cubiq::platform::base::Key, std::reference_wrapper<cubiq::common::interfaces::IPlugin>> m_mappings;
    std::unordered_map<cubiq::common::interfaces::IPlugin*, cubiq::common::interfaces::PluginTask> m_active_tasks;
};

} // namespace cubiq::assaultcube::external
