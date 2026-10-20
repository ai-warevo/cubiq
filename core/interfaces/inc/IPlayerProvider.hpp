#pragma once

#include "core/interfaces/inc/IEntity.hpp"
#include "core/interfaces/inc/ICamera.hpp"
#include "core/interfaces/inc/IViewAngleWriter.hpp"

namespace cubiq {

/**
 * @brief Abstract interface for a player entity.
 */
class IPlayer : public cubiq::common::interfaces::IPositionable,
                public cubiq::common::interfaces::ICamera,
                public cubiq::common::interfaces::IViewAngleWriter {
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
