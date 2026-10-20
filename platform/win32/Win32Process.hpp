#pragma once

#include "platform/base/IProcessManager.hpp"
#include <windows.h>
#include <string>

namespace cubiq::platform::win32 {

enum class ProcessError {
    None,
    NotFound,
    AccessDenied,
    Unknown
};

class Win32Process : public cubiq::platform::base::IProcess {
public:
    explicit Win32Process(const std::wstring& process_name, DWORD access = PROCESS_ALL_ACCESS);
    explicit Win32Process(DWORD pid, DWORD access = PROCESS_ALL_ACCESS);

    Win32Process(const Win32Process&) = delete;
    Win32Process& operator=(const Win32Process&) = delete;

    Win32Process(Win32Process&& other) noexcept;
    Win32Process& operator=(Win32Process&& other) noexcept;

    ~Win32Process() override;

    bool is_valid() const;
    uint32_t get_pid() const override { return m_pid; }
    std::unique_ptr<cubiq::platform::base::IMemoryAccess> get_memory_access() const override;
    
    HANDLE get_handle() const { return m_handle; }
    ProcessError get_error() const { return m_error; }
    uintptr_t get_module_base(const std::wstring& module_name) const;

private:
    uint32_t m_pid = 0;
    HANDLE m_handle = nullptr;
    ProcessError m_error = ProcessError::None;
};

} // namespace cubiq::platform::win32
