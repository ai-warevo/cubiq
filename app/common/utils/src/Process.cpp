#include "Process.hpp"
#include "ProcessUtils.hpp"

namespace cubiq::common::utils {

Process::Process(const std::wstring& process_name, DWORD access) {
    m_pid = ProcessUtils::get_process_id(process_name);
    if (m_pid == 0) {
        m_error = ProcessError::NotFound;
    } else {
        m_handle = ProcessUtils::open_process(m_pid, access);
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

Process::Process(DWORD pid, DWORD access) : m_pid(pid) {
    m_handle = ProcessUtils::open_process(m_pid, access);
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

Process::Process(Process&& other) noexcept 
    : m_pid(other.m_pid), m_handle(other.m_handle), m_error(other.m_error) {
    other.m_pid = 0;
    other.m_handle = nullptr;
    other.m_error = ProcessError::None;
}

Process& Process::operator=(Process&& other) noexcept {
    if (this != &other) {
        ProcessUtils::close_handle(m_handle);
        m_pid = other.m_pid;
        m_handle = other.m_handle;
        m_error = other.m_error;
        other.m_pid = 0;
        other.m_handle = nullptr;
        other.m_error = ProcessError::None;
    }
    return *this;
}

Process::~Process() {
    ProcessUtils::close_handle(m_handle);
}

uintptr_t Process::get_module_base(const std::wstring& module_name) const {
    if (!is_valid()) return 0;
    return ProcessUtils::get_module_base(m_pid, module_name);
}

} // namespace cubiq::common::utils
