#pragma once

#include "platform/base/inc/IProcessManager.hpp"
#include <windows.h>
#include <string>
#include <memory>

namespace cubiq::platform::win32 {

enum class ProcessError {
    None,
    NotFound,
    AccessDenied,
    Unknown
};

/**
 * @brief RAII wrapper for Windows HANDLEs.
 */
class ScopedHandle {
public:
    ScopedHandle() : m_handle(nullptr) {}
    explicit ScopedHandle(HANDLE h) : m_handle(h) {}
    ~ScopedHandle() { reset(); }

    ScopedHandle(const ScopedHandle&) = delete;
    ScopedHandle& operator=(const ScopedHandle&) = delete;

    ScopedHandle(ScopedHandle&& other) noexcept : m_handle(other.m_handle) {
        other.m_handle = nullptr;
    }

    ScopedHandle& operator=(ScopedHandle&& other) noexcept {
        if (this != &other) {
            reset();
            m_handle = other.m_handle;
            other.m_handle = nullptr;
        }
        return *this;
    }

    void reset(HANDLE h = nullptr) {
        if (m_handle && m_handle != INVALID_HANDLE_VALUE) {
            CloseHandle(m_handle);
        }
        m_handle = h;
    }

    HANDLE get() const { return m_handle; }
    operator HANDLE() const { return m_handle; }
    explicit operator bool() const { return m_handle && m_handle != INVALID_HANDLE_VALUE; }

private:
    HANDLE m_handle;
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
    
    HANDLE get_handle() const { return m_handle.get(); }
    ProcessError get_error() const { return m_error; }
    uintptr_t get_module_base(const std::wstring& module_name) const;

private:
    uint32_t m_pid = 0;
    ScopedHandle m_handle;
    ProcessError m_error = ProcessError::None;
};

} // namespace cubiq::platform::win32
