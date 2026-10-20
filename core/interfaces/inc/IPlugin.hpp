#pragma once

#include <functional>
#include "core/interfaces/inc/IGameState.hpp"

namespace cubiq::common::interfaces {

/**
 * @brief Result of a plugin task execution.
 */
enum class TaskResult {
    Continue,
    Stop
};

/**
 * @brief A function type representing a single plugin task step.
 */
using PluginTask = std::function<TaskResult(IGameState&)>;

/**
 * @brief Interface for plugins in the Assembler model.
 */
class IPlugin {
public:
    virtual ~IPlugin() = default;

    /**
     * @brief Enables the plugin and returns its task loop.
     * @param state The game state environment.
     * @return A function that performs the plugin's logic.
     */
    virtual PluginTask enable(IGameState& state) = 0;

    /**
     * @brief Disables the plugin and cleans up resources.
     */
    virtual void disable() = 0;
};

} // namespace cubiq::common::interfaces
