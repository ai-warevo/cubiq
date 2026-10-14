#include <iostream>
#include <windows.h>
#include <string>
#include "app/common/utils/inc/Process.hpp"
#include "app/common/utils/inc/ProcessUtils.hpp"
#include "app/common/utils/inc/MemoryUtils.hpp"
#include "app/common/utils/inc/InputUtils.hpp"
#include "app/external/inc/HealthModulator.hpp"

int main() {
    std::wstring process_name = L"ac_client.exe";
    
    cubiq::common::utils::Process process(process_name);
    if (!process.is_valid()) {
        std::wcerr << L"Failed to attach to: " << process_name << L" - Reason: ";
        switch (process.get_error()) {
            case cubiq::common::utils::ProcessError::NotFound:
                std::wcerr << L"Process not found. Is the game running?";
                break;
            case cubiq::common::utils::ProcessError::AccessDenied:
                std::wcerr << L"Access denied. Try running as Administrator.";
                break;
            case cubiq::common::utils::ProcessError::Unknown:
                std::wcerr << L"Unknown error occurred.";
                break;
            default:
                std::wcerr << L"No error specified.";
                break;
        }
        std::wcerr << std::endl;
        return 1;
    }

    uintptr_t module_base = process.get_module_base(process_name);
    if (!module_base) {
        std::wcerr << L"Failed to find module base: " << process_name << std::endl;
        return 1;
    }

    cubiq::common::utils::MemoryReaderWriter mem(process.get_handle());
    cubiq::external::HealthModulator health_mod(mem, module_base);
    cubiq::common::utils::InputUtils input;

    std::wcout << L"Attached to " << process_name << L" (PID: " << process.get_pid() << L")" << std::endl;
    std::wcout << L"Module base: 0x" << std::hex << module_base << std::endl;
    std::wcout << L"Press BACKSPACE to set health to 10000. Press ESC to exit." << std::endl;

    while (true) {
        if (!process.is_valid()) {
            std::cout << "Target process lost! Exiting..." << std::endl;
            break;
        }

        if (input.is_key_pressed(VK_BACK)) {
            health_mod.set_health(10000);
            std::cout << "Health set to 10000!" << std::endl;
        }

        if (input.is_key_down(VK_ESCAPE)) {
            break;
        }

        Sleep(10);
    }

    return 0;
}
