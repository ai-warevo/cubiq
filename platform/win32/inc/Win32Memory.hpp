#pragma once

#include "platform/base/inc/IMemoryAccess.hpp"
#include <windows.h>

namespace cubiq::platform::win32 {

/**
 * @brief Win32 implementation of IMemoryAccess using ReadProcessMemory/WriteProcessMemory.
 */
class Win32Memory : public cubiq::platform::base::IMemoryAccess {
public:
    explicit Win32Memory(HANDLE process_handle) : m_process_handle(process_handle) {}
    ~Win32Memory() override = default;

    bool read(uintptr_t address, void* buffer, size_t size) const override {
        return ReadProcessMemory(m_process_handle, reinterpret_cast<LPCVOID>(address), buffer, size, nullptr);
    }

    bool write(uintptr_t address, const void* buffer, size_t size) const override {
        return WriteProcessMemory(m_process_handle, reinterpret_cast<LPVOID>(address), buffer, size, nullptr);
    }

private:
    HANDLE m_process_handle;
};

} // namespace cubiq::platform::win32
