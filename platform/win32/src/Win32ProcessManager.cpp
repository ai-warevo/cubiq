#include "Win32ProcessManager.hpp"
#include "Win32Process.hpp"
#include <windows.h>
#include <TlHelp32.h>
#include <string.h>

namespace cubiq::platform::win32 {

std::optional<uint32_t> Win32ProcessManager::get_pid_by_name(const std::wstring& process_name) const {
    uint32_t pid = get_process_id_static(process_name);
    if (pid == 0) return std::nullopt;
    return pid;
}

std::unique_ptr<cubiq::platform::base::IProcess> Win32ProcessManager::open_process(uint32_t pid) const {
    // We need to create a Win32Process. 
    // But Win32Process constructor takes name or pid.
    // Let's use the PID one.
    return std::make_unique<Win32Process>(pid);
}

std::unique_ptr<cubiq::platform::base::IProcess> Win32ProcessManager::open_process_by_name(const std::wstring& process_name) const {
    uint32_t pid = get_process_id_static(process_name);
    if (pid == 0) return nullptr;
    return std::make_unique<Win32Process>(pid);
}

uint32_t Win32ProcessManager::get_process_id_static(const std::wstring& process_name) {
    uint32_t pid = 0;
    HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (snapshot == INVALID_HANDLE_VALUE) return 0;

    PROCESSENTRY32W entry;
    entry.dwSize = sizeof(entry);

    if (Process32FirstW(snapshot, &entry)) {
        do {
            if (_wcsicmp(process_name.c_str(), entry.szExeFile) == 0) {
                pid = entry.th32ProcessID;
                break;
            }
        } while (Process32NextW(snapshot, &entry));
    }

    CloseHandle(snapshot);
    return pid;
}

HANDLE Win32ProcessManager::open_process_static(uint32_t pid, DWORD access) {
    return OpenProcess(access, FALSE, pid);
}

uintptr_t Win32ProcessManager::get_module_base_static(uint32_t pid, const std::wstring& module_name) {
    uintptr_t base = 0;
    HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, pid);
    if (snapshot == INVALID_HANDLE_VALUE) return 0;

    MODULEENTRY32W entry;
    entry.dwSize = sizeof(entry);

    if (Module32FirstW(snapshot, &entry)) {
        do {
            if (_wcsicmp(module_name.c_str(), entry.szModule) == 0) {
                base = reinterpret_cast<uintptr_t>(entry.modBaseAddr);
                break;
            }
        } while (Module32NextW(snapshot, &entry));
    }

    CloseHandle(snapshot);
    return base;
}

} // namespace cubiq::platform::win32
