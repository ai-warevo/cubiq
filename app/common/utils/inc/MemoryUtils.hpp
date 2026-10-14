#pragma once

#include <windows.h>
#include <cstdint>

namespace cubiq::common::utils {

class MemoryReaderWriter {
public:
    explicit MemoryReaderWriter(HANDLE process_handle) : m_process_handle(process_handle) {}
    ~MemoryReaderWriter() = default;

    template<typename T>
    T read(uintptr_t address) const {
        T buffer{};
        if (!ReadProcessMemory(m_process_handle, reinterpret_cast<LPCVOID>(address), &buffer, sizeof(T), nullptr)) {
            return T{};
        }
        return buffer;
    }

    template<typename T>
    bool write(uintptr_t address, T value) const {
        return WriteProcessMemory(m_process_handle, reinterpret_cast<LPVOID>(address), &value, sizeof(T), nullptr);
    }

private:
    HANDLE m_process_handle;
};

} // namespace cubiq::common::utils
