#pragma once

#include <windows.h>
#include <string>
#include <cstdint>

namespace cubiq::common::utils {

class ProcessUtils {
public:
    static DWORD get_process_id(const std::wstring& process_name);

    static HANDLE open_process(DWORD pid, DWORD access = PROCESS_ALL_ACCESS);

    static HANDLE open_process_by_name(const std::wstring& process_name, DWORD access = PROCESS_ALL_ACCESS, DWORD* out_pid = nullptr);

    static void close_handle(HANDLE handle);

    static uintptr_t get_module_base(DWORD pid, const std::wstring& module_name);
};

} // namespace cubiq::common::utils
