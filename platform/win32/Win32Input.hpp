#pragma once

#include <vector>
#include <unordered_map>
#include <windows.h>

namespace cubiq::platform::win32 {

// Re-exporting common WinAPI constants to avoid <windows.h> in core/games
enum class VirtualKey : int {
    Back = VK_BACK,
    F1 = VK_F1,
    Escape = VK_ESCAPE
};

class Win32Input {
public:
    // Checks if a key is currently held down
    static bool is_key_down(int vk_code);

    // Checks if a key was pressed since the last check (single press)
    bool is_key_pressed(int vk_code);

private:
    std::unordered_map<int, bool> m_key_states;
};

} // namespace cubiq::platform::win32
