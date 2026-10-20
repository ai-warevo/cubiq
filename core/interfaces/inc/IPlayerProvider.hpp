#pragma once

namespace cubiq {

/**
 * @brief Abstract interface for a player entity.
 */
class IPlayer {
public:
    virtual ~IPlayer() = default;
};

/**
 * @brief Interface for game states that provide access to a player.
 */
class IPlayerProvider {
public:
    virtual ~IPlayerProvider() = default;
    virtual IPlayer& get_player() = 0;
};

} // namespace cubiq
