#pragma once

#include <cstdint>
#include "core/math/inc/Vector3.hpp"
#include "platform/base/IMemoryAccess.hpp"

namespace cubiq::common::interfaces {

/**
 * @brief Base interface for any object that has a position in 3D space.
 */
class IPositionable {
public:
    virtual ~IPositionable() = default;

    /**
     * @brief Gets the current position of the entity.
     * @return The position as a Vector3.
     */
    virtual cubiq::common::math::Vector3 get_position() const = 0;
};

/**
 * @brief Interface for entities that have health.
 */
class IHealthEntity : public IPositionable {
public:
    virtual ~IHealthEntity() = default;

    /**
     * @brief Gets the current health of the entity.
     * @param mem The memory access implementation to use.
     * @return The current health value.
     */
    virtual uint32_t get_health(const cubiq::platform::base::IMemoryAccess& mem) const = 0;

    /**
     * @brief Sets the health of the entity.
     * @param mem The memory access implementation to use.
     * @param amount The new health value.
     */
    virtual void set_health(const cubiq::platform::base::IMemoryAccess& mem, uint32_t amount) = 0;
};

} // namespace cubiq::common::interfaces

