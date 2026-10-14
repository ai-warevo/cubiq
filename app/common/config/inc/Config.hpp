#pragma once

#include "app/common/cheats/onehitkill/inc/OneHitKillConfig.hpp"
#include "app/common/cheats/godmode/inc/GodModeConfig.hpp"

namespace cubiq::common::config {

struct Config {
    cubiq::common::cheats::onehitkill::OneHitKillConfig onehitkill;
    cubiq::common::cheats::godmode::GodModeConfig godmode;
};

} // namespace cubiq::common::config
