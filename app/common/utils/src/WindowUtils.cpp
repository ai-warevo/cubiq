#include "WindowUtils.hpp"

namespace cubiq::common::utils {

struct WindowSearchData {
    std::wstring substring;
    HWND found_hwnd = nullptr;
};

static BOOL CALLBACK EnumWindowsCallback(HWND hwnd, LPARAM lParam) {
    auto* data = reinterpret_cast<WindowSearchData*>(lParam);
    wchar_t title[256];
    if (GetWindowTextW(hwnd, title, sizeof(title) / sizeof(wchar_t)) > 0) {
        std::wstring window_title(title);
        if (window_title.find(data->substring) != std::wstring::npos) {
            data->found_hwnd = hwnd;
            return FALSE; // Stop enumerating
        }
    }
    return TRUE;
}

HWND WindowUtils::find_window_by_title(const std::wstring& title) {
    return FindWindowW(nullptr, title.c_str());
}

HWND WindowUtils::find_window_by_substring(const std::wstring& substring) {
    WindowSearchData data{ substring, nullptr };
    EnumWindows(EnumWindowsCallback, reinterpret_cast<LPARAM>(&data));
    return data.found_hwnd;
}

struct TitleList {
    std::vector<std::wstring>* titles;
};

static BOOL CALLBACK EnumTitlesCallback(HWND hwnd, LPARAM lParam) {
    auto* data = reinterpret_cast<TitleList*>(lParam);
    wchar_t title[256];
    if (GetWindowTextW(hwnd, title, sizeof(title) / sizeof(wchar_t)) > 0) {
        data->titles->push_back(std::wstring(title));
    }
    return TRUE;
}

std::vector<std::wstring> WindowUtils::enumerate_window_titles() {
    std::vector<std::wstring> titles;
    TitleList data{ &titles };
    EnumWindows(EnumTitlesCallback, reinterpret_cast<LPARAM>(&data));
    return titles;
}

} // namespace cubiq::common::utils
