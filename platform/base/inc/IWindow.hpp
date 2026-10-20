#pragma once

#include <string>
#include <vector>
#include <optional>

namespace cubiq::platform::base {

/**
 * @brief Interface representing a window.
 */
class IWindow {
public:
    virtual ~IWindow() = default;
    virtual std::wstring get_title() const = 0;
};

/**
 * @brief Interface for window management operations.
 */
class IWindowManager {
public:
    virtual ~IWindowManager() = default;

    virtual std::optional<std::wstring> find_window_by_title(const std::wstring& title) const = 0;
    virtual std::vector<std::wstring> enumerate_window_titles() const = 0;
};

} // namespace cubiq::platform::base
