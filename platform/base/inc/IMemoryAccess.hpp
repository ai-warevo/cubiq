#pragma once

#include <cstdint>
#include <cstddef>

namespace cubiq::platform::base {

/**
 * @brief Interface for memory access operations.
 */
class IMemoryAccess {
public:
    /**
     * @brief A heuristic range for sanity checking pointers read from external process memory.
     */
    static constexpr size_t kDefaultSanityRange = 0x7FFFFFFF;

    virtual ~IMemoryAccess() = default;

    /**
     * @brief Pure virtual byte-level read operation.
     */
    virtual bool read(uintptr_t address, void* buffer, size_t size) const = 0;

    /**
     * @brief Pure virtual byte-level write operation.
     */
    virtual bool write(uintptr_t address, const void* buffer, size_t size) const = 0;

    /**
     * @brief Checks if an address is within a valid range.
     */
    virtual bool is_in_range(uintptr_t address, uintptr_t base, size_t size) const = 0;

    /**
     * @brief Templated helper for reading a value of type T.
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
     */
    template<typename T>
    bool write(uintptr_t address, T value) const {
        return write(address, &value, sizeof(T));
    }
};

} // namespace cubiq::platform::base
