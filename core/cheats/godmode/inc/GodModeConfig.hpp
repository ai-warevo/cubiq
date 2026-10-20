#pragma once

#include "core/config/inc/BaseConfig.hpp"

namespace cubiq::common::cheats::godmode {

struct GodModeConfig : public cubiq::common::config::BaseConfig {
    uint32_t health_value = 10000;
};

} // namespace cubiq::common::cheats::godmode

