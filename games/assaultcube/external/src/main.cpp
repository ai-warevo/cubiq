#include <iostream>
#include <vector>
#include "core/cheats/aimbot/inc/AimbotPlugin.hpp"
#include "core/cheats/godmode/inc/GodModePlugin.hpp"
#include "core/modes/external/inc/ExternalEngine.hpp"
#include "platform/win32/inc/Win32Input.hpp"
#include "platform/win32/inc/Win32ProcessManager.hpp"
#include "games/assaultcube/external/inc/ACGameState.hpp"
#include "games/assaultcube/external/inc/ACExternalController.hpp"

int main() {
    // 1. Instantiate Platform Components
    cubiq::platform::win32::Win32ProcessManager process_manager;
    cubiq::platform::win32::Win32Input input;

    // 2. Instantiate Engine
    cubiq::core::modes::external::ExternalEngine engine(L"ac_client.exe", process_manager);

    if (!engine.attach()) {
        std::wcerr << L"Failed to attach to ac_client.exe" << std::endl;
        return 1;
    }

    // 3. Instantiate Plugins
    cubiq::common::cheats::aimbot::AimbotPlugin aimbot({ 2.0f, true });
    cubiq::common::cheats::godmode::GodModePlugin godmode({});
    std::vector<cubiq::IPlugin*> plugins = { &aimbot, &godmode };

    // 4. Instantiate Game State & Controller
    cubiq::assaultcube::external::ACGameState state;
    cubiq::assaultcube::external::ACExternalController controller(input, engine, plugins);

    // Bindings
    controller.bind(cubiq::Key::Back, &godmode);
    controller.bind(cubiq::Key::F1, &aimbot);

    std::wcout << L"Attached! [BACKSIDE] GodMode | [F1] Aimbot (Self) | [ESC] Exit" << std::endl;

    // 5. Execute Loop
    engine.run([&](cubiq::platform::base::IMemoryAccess& mem, uintptr_t module_base) {
        controller.update(state, mem, module_base);
    });

    return 0;
}