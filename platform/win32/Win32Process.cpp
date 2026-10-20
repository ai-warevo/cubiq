#include "Win32Process.hpp"
#include "Win32Memory.hpp"
#include "Win32ProcessManager.hpp"
#include <windows.h>

namespace cubiq::platform::win32 {

Win32Process::Win32Process(const std::wstring& process_name, DWORD access) {
    m_pid = Win32ProcessManager::get_process_id_static(process_name);
    if (m_pid == 0) {
        m_error = ProcessError::NotFound;
    } else {
        m_handle = Win32ProcessManager::open_process_static(m_pid, access);
        if (!m_handle) {
            DWORD err = GetLastError();
            if (err == ERROR_ACCESS_DENIED) {
                m_error = ProcessError::AccessDenied;
            } else {
                m_error = ProcessError::Unknown;
            }
        } else {
            m_error = ProcessError::None;
        }
    }
}

Win32Process::Win32Process(DWORD pid, DWORD access) : m_pid(pid) {
    m_handle = Win32ProcessManager::open_process_static(m_pid, access);
    if (!m_handle) {
        DWORD err = GetLastError();
        if (err == ERROR_ACCESS_DENIED) {
            m_error = ProcessError::AccessDenied;
        } else {
            m_error = ProcessError::Unknown;
        }
    } else {
        m_error = ProcessError::None;
    }
}

Win32Process::Win32Process(Win32Process&& other) noexcept 
    : m_pid(other.m_pid), m_handle(other.m_handle), m_error(other.m_error) {
    other.m_pid = 0;
    other.m_handle = nullptr;
    other.m_error = ProcessError::None;
}

Win32Process& Win32Process::operator=(Win32Process&& other) noexcept {
    if (this != &other) {
        if (m_handle && m_handle != INVALID_HANDLE_VALUE) {
            CloseHandle(m_handle);
        }
        m_pid = other.m_pid;
        m_handle = other.m_handle;
        m_error = other.m_error;
        other.m_pid = 0;
        other.m_handle = nullptr;
        other.m_error = ProcessError::None;
    }
    return *this;
}

Win32Process::~Win32Process() {
    if (m_handle && m_handle != INVALID_HANDLE_VALUE) {
        CloseHandle(m_handle);
    }
}

bool Win32Process::is_valid() const { 
    if (m_handle == nullptr || m_handle == INVALID_HANDLE_VALUE) return false;
    
    DWORD exitCode = 0;
    if (GetExitCodeProcess(m_handle, &exitCode)) {
        return exitCode == STILL_ACTIVE;
    }
    return false;
}

std::unique_ptr<cubiq::platform::base::IMemoryAccess> Win32Process::get_memory_access() const {
    if (!is_valid()) return nullptr;
    return std::make_unique<Win32Memory>(m_handle);
}

uintptr_t Win32Process::get_module_base(const std::wstring& module_name) const {
    if (!is_valid()) return 0;
    return Win32ProcessManager::get_module_base_static(m_pid, module_name);
}

} // namespace cubiq::platform::win32
