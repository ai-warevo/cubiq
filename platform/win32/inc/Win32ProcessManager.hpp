#pragma once

#include "platform/base/inc/IProcessManager.hpp"
#include <windows.h>
#include <string>
#include <cstdint>
#include <optional>

namespace cubiq::platform::win32 {

class Win32ProcessManager : public cubiq::platform::base::IProcessManager {
public:
    Win32ProcessManager() = default;
    ~Win32ProcessManager() override = default;

    // IProcessManager implementation
    std::optional<uint32_t> get_pid_by_name(const std::wstring& process_name) const override;
    std::unique_ptr<cubiq::platform::base::IProcess> open_process(uint32_t pid) const override;
    std::unique_ptr<cubiq::platform::base::IProcess> open_process_by_name(const std::wstring& process_name) const override;

    // Static helpers for Win32Process and other internal use
    static uint32_t get_process_id_static(const std::wstring& process_name);
    static HANDLE open_process_static(uint32_t pid, DWORD access);
    static uintptr_t get_module_base_static(uint32_t pid, const std::wstring& module_name);
};

} // namespace cubiq::platform::win32
