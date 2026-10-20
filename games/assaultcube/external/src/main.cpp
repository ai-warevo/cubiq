#include <iostream>
#include "core/cheats/aimbot/inc/AimbotPlugin.hpp"
#include "core/cheats/godmode/inc/GodModePlugin.hpp"
#include "core/modes/external/inc/ExternalEngine.hpp"
#include "platform/win32/inc/Win32Input.hpp"
#include "platform/win32/inc/Win32ProcessManager.hpp"
#include "games/assaultcube/external/inc/ACPlayer.hpp"

int main() {
    cubiq::platform::win32::Win32ProcessManager process_manager;
    cubiq::core::modes::external::ExternalEngine engine(L"ac_client.exe", process_manager);

    if (!engine.attach()) {
        std::wcerr << L"Failed to attach to ac_client.exe" << std::endl;
        return 1;
    }

    // --- Composition Root: Instantiate long-lived components ---
    cubiq::common::cheats::aimbot::AimbotPlugin aimbot({ 2.0f, true });
    cubiq::common::cheats::godmode::GodModePlugin godmode({});
    // ------------------------------------------------------------

    std::wcout << L"Attached! [BACKSIDE] GodMode | [F1] Aimbot (Self) | [ESC] Exit" << std::endl;

    cubiq::platform::win32::Win32Input input;

    engine.run([&](cubiq::platform::base::IMemoryAccess& mem, uintptr_t module_base) {
        // 1. The Hands: Instantiate the implementation of interfaces for this game
        cubiq::assaultcube::external::ACPlayer player(mem, module_base);

        // 2. Execute Plugins (The Brain)
        if (input.is_key_pressed(static_cast<int>(cubiq::platform::win32::VirtualKey::Back))) {
            if (godmode.execute(player, mem)) {
                std::cout << "God mode applied!" << std::endl;
            } else {
                std::cout << "Failed to apply God mode!" << std::endl;
            }
        }

        if (input.is_key_pressed(static_cast<int>(cubiq::platform::win32::VirtualKey::F1))) {
            aimbot.execute(player, player, player);
            std::cout << "Aimbot executed (on self)!" << std::endl;
        }

        if (input.is_key_down(static_cast<int>(cubiq::platform::win32::VirtualKey::Escape))) {
            engine.stop();
        }
    });

    return 0;
}