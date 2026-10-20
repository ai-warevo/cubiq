#pragma once

#include "platform/base/IWindow.hpp"
#include <windows.h>
#include <string>
#include <vector>
#include <optional>

namespace cubiq::platform::win32 {

class Win32Window : public cubiq::platform::base::IWindow {
public:
    explicit Win32Window(HWND hwnd) : m_hwnd(hwnd) {}
    ~Win32Window() override = default;

    std::wstring get_title() const override;
    HWND get_hwnd() const { return m_hwnd; }

private:
    HWND m_hwnd;
};

class Win32WindowManager : public cubiq::platform::base::IWindowManager {
public:
    Win32WindowManager() = default;
    ~Win32WindowManager() override = default;

    std::optional<std::wstring> find_window_by_title(const std::wstring& title) const override;
    std::vector<std::wstring> enumerate_window_titles() const override;

    HWND find_window_by_substring(const std::wstring& substring) const;

private:
    struct TitleList {
        std::vector<std::wstring>* titles;
    };

    static BOOL CALLBACK EnumTitlesCallback(HWND hwnd, LPARAM lParam);

    struct WindowSearchData {
        std::wstring substring;
        HWND found_hwnd = nullptr;
    };

    static BOOL CALLBACK EnumWindowsCallback(HWND hwnd, LPARAM lParam);
};

} // namespace cubiq::platform::win32
