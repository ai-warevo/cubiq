#include "Win32Input.hpp"

namespace cubiq::platform::win32 {

bool Win32Input::is_key_down(int vk_code) {
    return (GetAsyncKeyState(vk_code) & 0x8000) != 0;
}

bool Win32Input::is_key_pressed(int vk_code) {
    bool current_state = (GetAsyncKeyState(vk_code) & 0x8000) != 0;
    bool last_state = m_key_states[vk_code];

    if (current_state && !last_state) {
        m_key_states[vk_code] = true;
        return true;
    } else if (!current_state) {
        m_key_states[vk_code] = false;
    }

    return false;
}

} // namespace cubiq::platform::win32
