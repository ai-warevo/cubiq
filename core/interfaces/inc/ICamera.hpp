#pragma once

#include "core/math/inc/Vector3.hpp"

namespace cubiq::common::interfaces {

/**
 * @brief Interface for a camera or view representation.
 */
class ICamera {
public:
    virtual ~ICamera() = default;

    /**
     * @brief Gets the current position of the camera.
     * @return The position as a Vector3.
     */
    virtual cubiq::common::math::Vector3 get_position() const = 0;

    /**
     * @brief Gets the current view angles (pitch, yaw, roll).
     * @return The angles as a Vector3.
     */
    virtual cubiq::common::math::Vector3 get_view_angles() const = 0;
};

} // namespace cubiq::common::interfaces

