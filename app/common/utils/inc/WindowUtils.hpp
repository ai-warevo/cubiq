#pragma once

#include <windows.h>
#include <string>
#include <vector>

namespace cubiq::common::utils {

class WindowUtils {
public:
    static HWND find_window_by_title(const std::wstring& title);

    static HWND find_window_by_substring(const std::wstring& substring);

    static std::vector<std::wstring> enumerate_window_titles();
};

} // namespace cubiq::common::utils
