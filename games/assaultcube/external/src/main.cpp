#include <iostream>
#include <windows.h>
#include "core/cheats/aimbot/inc/AimbotPlugin.hpp"
#include "core/cheats/godmode/inc/GodModePlugin.hpp"
#include "core/modes/external/inc/ExternalEngine.hpp"
#include "core/utils/inc/InputUtils.hpp"
#include "games/assaultcube/external/inc/ACPlayer.hpp"

int main() {
    cubiq::core::modes::external::ExternalEngine engine(L"ac_client.exe");

    if (!engine.attach()) {
        std::wcerr << L"Failed to attach to ac_client.exe" << std::endl;
        return 1;
    }

    std::wcout << L"Attached! [BACKSPACE] GodMode | [F1] Aimbot (Self) | [ESC] Exit" << std::endl;

    cubiq::common::utils::InputUtils input;

    engine.run([&](cubiq::common::utils::IMemoryAccess& mem, uintptr_t module_base) {
        // 1. The Hands: Instantiate the implementation of interfaces for this game
        cubiq::assaultcube::external::ACPlayer player(mem, module_base);

        // 2. Execute Plugins (The Brain)
        if (input.is_key_pressed(VK_BACK)) {
            cubiq::common::cheats::godmode::GodModePlugin godmode({});
            godmode.execute(player, mem);
            std::cout << "God mode applied!" << std::endl;
        }

        if (input.is_key_pressed(VK_F1)) {
            // For demonstration, we aim at the local player itself
            cubiq::common::cheats::aimbot::AimbotPlugin aimbot({ 2.0f, true }); // smoothing = 2.0
            aimbot.execute(player, player, player);
            std::cout << "Aimbot executed (on self)!" << std::endl;
        }

        if (input.is_key_down(VK_ESCAPE)) {
            engine.stop();
        }
    });

    return 0;
}
