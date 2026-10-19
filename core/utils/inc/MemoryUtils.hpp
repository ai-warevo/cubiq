#pragma once

#include <windows.h>
#include <cstdint>
#include "IMemoryAccess.hpp"

namespace cubiq::common::utils {

class MemoryReaderWriter : public IMemoryAccess {
public:
    explicit MemoryReaderWriter(HANDLE process_handle) : m_process_handle(process_handle) {}
    ~MemoryReaderWriter() override = default;

    bool read(uintptr_t address, void* buffer, size_t size) const override {
        return ReadProcessMemory(m_process_handle, reinterpret_cast<LPCVOID>(address), buffer, size, nullptr);
    }

    bool write(uintptr_t address, const void* buffer, size_t size) const override {
        return WriteProcessMemory(m_process_handle, reinterpret_cast<LPVOID>(address), buffer, size, nullptr);
    }

private:
    HANDLE m_process_handle;
};

} // namespace cubiq::common::utils
