#pragma once

#include <windows.h>
#include <string>
#include <cstdint>

namespace cubiq::common::utils {

enum class ProcessError {
    None,
    NotFound,
    AccessDenied,
    Unknown
};

class Process {
public:
    explicit Process(const std::wstring& process_name, DWORD access = PROCESS_ALL_ACCESS);

    explicit Process(DWORD pid, DWORD access = PROCESS_ALL_ACCESS);

    Process(const Process&) = delete;
    Process& operator=(const Process&) = delete;

    Process(Process&& other) noexcept;
    Process& operator=(Process&& other) noexcept;

    ~Process();

    bool is_valid() const { 
        if (m_handle == nullptr || m_handle == INVALID_HANDLE_VALUE) return false;
        
        DWORD exitCode = 0;
        if (GetExitCodeProcess(m_handle, &exitCode)) {
            return exitCode == STILL_ACTIVE;
        }
        return false;
    }

    DWORD get_pid() const { return m_pid; }
    HANDLE get_handle() const { return m_handle; }
    ProcessError get_error() const { return m_error; }

    uintptr_t get_module_base(const std::wstring& module_name) const;

private:
    DWORD m_pid = 0;
    HANDLE m_handle = nullptr;
    ProcessError m_error = ProcessError::None;
};

} // namespace cubiq::common::utils
