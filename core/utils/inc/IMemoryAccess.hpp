#pragma once

#include <cstdint>
#include <cstddef>

namespace cubiq::common::utils {

/**
 * @brief Interface for memory access operations.
 * 
 * This interface allows the "Brain" (logic) to perform memory reads and writes
 * without knowing whether it is using User-mode (ReadProcessMemory), 
 * Kernel-mode (Driver), or another method.
 */
class IMemoryAccess {
public:
    virtual ~IMemoryAccess() = default;

    /**
     * @brief Pure virtual byte-level read operation.
     * @param address The source memory address.
     * @param buffer Pointer to the destination buffer.
     * @param size Number of bytes to read.
     * @return true if successful, false otherwise.
     */
    virtual bool read(uintptr_t address, void* buffer, size_t size) const = 0;

    /**
     * @brief Pure virtual byte-level write operation.
     * @param address The destination memory address.
     * @param buffer Pointer to the source buffer.
     * @param size Number of bytes to write.
     * @return true if successful, false otherwise.
     */
    virtual bool write(uintptr_t address, const void* buffer, size_t size) const = 0;

    /**
     * @brief Templated helper for reading a value of type T.
     * @param address The source memory address.
     * @return The value read from memory, or a default-initialized T on failure.
     */
    template<typename T>
    T read(uintptr_t address) const {
        T buffer{};
        if (read(address, &buffer, sizeof(T))) {
            return buffer;
        }
        return T{};
    }

    /**
     * @brief Templated helper for writing a value of type T.
     * @param address The destination memory address.
     * @param value The value to write.
     * @return true if successful, false otherwise.
     */
    template<typename T>
    bool write(uintptr_t address, T value) const {
        return write(address, &value, sizeof(T));
    }
};

} // namespace cubiq::common::utils
