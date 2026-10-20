#pragma once

#include "core/interfaces/inc/IGameState.hpp"
#include "core/interfaces/inc/IPlayerProvider.hpp"

namespace cubiq {

/**
 * @brief A specialized game state for environments that provide access to players.
 */
class IPlayerProviderGameState : public IGameState {
public:
    virtual ~IPlayerProviderGameState() = default;

    /**
     * @brief Provides access to player-related operations.
     */
    virtual IPlayerProvider& get_player_provider() = 0;
};

} // namespace cubiq
