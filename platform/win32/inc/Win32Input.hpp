#pragma once

#include <vector>
#include <unordered_map>
#include <windows.h>
#include "platform/base/inc/IInput.hpp"

namespace cubiq::platform::win32 {

// Re-exporting common WinAPI constants to avoid <windows.h> in core/games
enum class VirtualKey : int {
    Back = VK_BACK,
    F1 = VK_F1,
    Escape = VK_ESCAPE
};

class Win32Input : public cubiq::IInput {
public:
    // Checks if a key is currently held down
    bool is_key_down(cubiq::Key key) override;

    // Checks if a key was pressed since the last check (single press)
    bool is_key_pressed(cubiq::Key key) override;

private:
    int to_vk(cubiq::Key key) const;
    std::unordered_map<int, bool> m_key_states;
};

} // namespace cubiq::platform::win32
