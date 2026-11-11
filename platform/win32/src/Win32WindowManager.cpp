#include "Win32WindowManager.hpp"

namespace cubiq::platform::win32 {

namespace {
constexpr size_t MAX_WINDOW_TITLE_LENGTH = 256;
}

std::wstring Win32Window::get_title() const {
    wchar_t title[MAX_WINDOW_TITLE_LENGTH];
    if (GetWindowTextW(m_hwnd, title, sizeof(title) / sizeof(wchar_t)) > 0) {
        return std::wstring(title);
    }
    return L"";
}

std::optional<std::wstring> Win32WindowManager::find_window_by_title(const std::wstring& title) const {
    HWND hwnd = FindWindowW(nullptr, title.c_str());
    if (hwnd) {
        return Win32Window(hwnd).get_title();
    }
    return std::nullopt;
}

std::vector<std::wstring> Win32WindowManager::enumerate_window_titles() const {
    std::vector<std::wstring> titles;
    TitleList data{ &titles };
    EnumWindows(EnumTitlesCallback, reinterpret_cast<LPARAM>(&data));
    return titles;
}

// Callback for EnumWindows to retrieve window titles. 
// lParam is a pointer to TitleList containing the vector of strings.
BOOL CALLBACK Win32WindowManager::EnumTitlesCallback(HWND hwnd, LPARAM lParam) {
    auto* data = reinterpret_cast<TitleList*>(lParam);
    wchar_t title[MAX_WINDOW_TITLE_LENGTH];
    if (GetWindowTextW(hwnd, title, sizeof(title) / sizeof(wchar_t)) > 0) {
        data->titles->push_back(std::wstring(title));
    }
    return TRUE;
}

HWND Win32WindowManager::find_window_by_substring(const std::wstring& substring) const {
    WindowSearchData data{ substring, nullptr };
    EnumWindows(EnumWindowsCallback, reinterpret_cast<LPARAM>(&data));
    return data.found_hwnd;
}

// Callback for EnumWindows to find a window whose title contains the target substring.
// lParam is a pointer to WindowSearchData containing the search criteria and result.
BOOL CALLBACK Win32WindowManager::EnumWindowsCallback(HWND hwnd, LPARAM lParam) {
    auto* data = reinterpret_cast<WindowSearchData*>(lParam);
    wchar_t title[MAX_WINDOW_TITLE_LENGTH];
    if (GetWindowTextW(hwnd, title, sizeof(title) / sizeof(wchar_t)) > 0) {
        std::wstring window_title(title);
        if (window_title.find(data->substring) != std::wstring::npos) {
            data->found_hwnd = hwnd;
            return FALSE; // Stop enumerating once found
        }
    }
    return TRUE;
}

} // namespace cubiq::platform::win32
