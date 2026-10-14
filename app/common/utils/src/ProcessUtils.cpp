#include "ProcessUtils.hpp"
#include <windows.h>
#include <TlHelp32.h>
#include <string.h>
#include <iostream>

namespace cubiq::common::utils {

DWORD ProcessUtils::get_process_id(const std::wstring& process_name) {
    DWORD pid = 0;
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

    if (pid == 0) {
        std::wcout << L"[DEBUG] Process '" << process_name << L"' not found. Listing all processes:" << std::endl;
        if (Process32FirstW(snapshot, &entry)) {
            do {
                std::wcout << L"  - " << entry.szExeFile << std::endl;
            } while (Process32NextW(snapshot, &entry));
        }
    }

    CloseHandle(snapshot);
    return pid;
}

HANDLE ProcessUtils::open_process(DWORD pid, DWORD access) {
    return OpenProcess(access, FALSE, pid);
}

HANDLE ProcessUtils::open_process_by_name(const std::wstring& process_name, DWORD access, DWORD* out_pid) {
    DWORD pid = get_process_id(process_name);
    if (pid == 0) return nullptr;
    if (out_pid) *out_pid = pid;
    return open_process(pid, access);
}

void ProcessUtils::close_handle(HANDLE handle) {
    if (handle != nullptr && handle != INVALID_HANDLE_VALUE) {
        CloseHandle(handle);
    }
}

uintptr_t ProcessUtils::get_module_base(DWORD pid, const std::wstring& module_name) {
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

} // namespace cubiq::common::utils
