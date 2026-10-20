#pragma once

#include <windows.h>
#include <memory>

namespace cubiq::platform::win32 {

/**
 * @brief RAII deleter for Windows HANDLEs.
 */
struct HandleDeleter {
    void operator()(HANDLE h) const {
        if (h != nullptr && h != INVALID_HANDLE_VALUE) {
            CloseHandle(h);
        }
    }
};

/**
 * @brief A unique_ptr specialization for Windows HANDLEs.
 */
using UniqueHandle = std::unique_ptr<void, HandleDeleter>;

} // namespace cubiq::platform::win32
