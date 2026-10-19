#pragma once

#include "core/math/inc/Vector3.hpp"

namespace cubiq::common::interfaces {

/**
 * @brief Interface for writing view angles to the game.
 */
class IViewAngleWriter {
public:
    virtual ~IViewAngleWriter() = default;

    /**
     * @brief Writes new view angles to the game.
     * @param angles The new angles as a Vector3.
     */
    virtual void write_view_angles(const cubiq::common::math::Vector3& angles) = 0;
};

} // namespace cubiq::common::interfaces

