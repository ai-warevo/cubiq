#pragma once

#include <cstdint>
#include "platform/base/inc/IMemoryAccess.hpp"

namespace cubiq {

/**
 * @brief Base environment interface for the Assembler model.
 */
class IGameState {
public:
    virtual ~IGameState() = default;

    /**
     * @brief Provides access to memory operations.
     */
    virtual platform::base::IMemoryAccess& get_memory() = 0;

    /**
     * @brief Returns the base address of the game module.
     */
    virtual uintptr_t get_module_base() = 0;
};

} // namespace cubiq
