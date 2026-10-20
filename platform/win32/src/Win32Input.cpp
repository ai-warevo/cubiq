#include "Win32Input.hpp"

namespace cubiq::platform::win32 {

namespace {
constexpr int KEY_DOWN_MASK = 0x8000;
}

int Win32Input::to_vk(cubiq::platform::base::Key key) const {
    switch (key) {
        case cubiq::platform::base::Key::A: return 'A';
        case cubiq::platform::base::Key::B: return 'B';
        case cubiq::platform::base::Key::C: return 'C';
        case cubiq::platform::base::Key::D: return 'D';
        case cubiq::platform::base::Key::E: return 'E';
        case cubiq::platform::base::Key::F: return 'F';
        case cubiq::platform::base::Key::G: return 'G';
        case cubiq::platform::base::Key::H: return 'H';
        case cubiq::platform::base::Key::I: return 'I';
        case cubiq::platform::base::Key::J: return 'J';
        case cubiq::platform::base::Key::K: return 'K';
        case cubiq::platform::base::Key::L: return 'L';
        case cubiq::platform::base::Key::M: return 'M';
        case cubiq::platform::base::Key::N: return 'N';
        case cubiq::platform::base::Key::O: return 'O';
        case cubiq::platform::base::Key::P: return 'P';
        case cubiq::platform::base::Key::Q: return 'Q';
        case cubiq::platform::base::Key::R: return 'R';
        case cubiq::platform::base::Key::S: return 'S';
        case cubiq::platform::base::Key::T: return 'T';
        case cubiq::platform::base::Key::U: return 'U';
        case cubiq::platform::base::Key::V: return 'V';
        case cubiq::platform::base::Key::W: return 'W';
        case cubiq::platform::base::Key::X: return 'X';
        case cubiq::platform::base::Key::Y: return 'Y';
        case cubiq::platform::base::Key::Z: return 'Z';
        case cubiq::platform::base::Key::Up: return VK_UP;
        case cubiq::platform::base::Key::Down: return VK_DOWN;
        case cubiq::platform::base::Key::Left: return VK_LEFT;
        case cubiq::platform::base::Key::Right: return VK_RIGHT;
        case cubiq::platform::base::Key::Enter: return VK_RETURN;
        case cubiq::platform::base::Key::Escape: return VK_ESCAPE;
        case cubiq::platform::base::Key::Space: return VK_SPACE;
        case cubiq::platform::base::Key::Shift: return VK_SHIFT;
        case cubiq::platform::base::Key::Ctrl: return VK_CONTROL;
        case cubiq::platform::base::Key::Alt: return VK_MENU;
        case cubiq::platform::base::Key::F1: return VK_F1;
        case cubiq::platform::base::Key::F2: return VK_F2;
        case cubiq::platform::base::Key::F3: return VK_F3;
        case cubiq::platform::base::Key::F4: return VK_F4;
        case cubiq::platform::base::Key::F5: return VK_F5;
        case cubiq::platform::base::Key::F6: return VK_F6;
        case cubiq::platform::base::Key::F7: return VK_F7;
        case cubiq::platform::base::Key::F8: return VK_F8;
        case cubiq::platform::base::Key::F9: return VK_F9;
        case cubiq::platform::base::Key::F10: return VK_F10;
        case cubiq::platform::base::Key::F11: return VK_F11;
        case cubiq::platform::base::Key::F12: return VK_F12;
        case cubiq::platform::base::Key::Back: return VK_BACK;
        case cubiq::platform::base::Key::Delete: return VK_DELETE;
        case cubiq::platform::base::Key::Insert: return VK_INSERT;
        case cubiq::platform::base::Key::Home: return VK_HOME;
        case cubiq::platform::base::Key::End: return VK_END;
        case cubiq::platform::base::Key::PageUp: return VK_PRIOR;
        case cubiq::platform::base::Key::PageDown: return VK_NEXT;
        default: return 0;
    }
}

bool Win32Input::is_key_down(cubiq::platform::base::Key key) {
    int vk = to_vk(key);
    if (vk == 0) return false;
    return (GetAsyncKeyState(vk) & KEY_DOWN_MASK) != 0;
}

bool Win32Input::is_key_pressed(cubiq::platform::base::Key key) {
    int vk = to_vk(key);
    if (vk == 0) return false;

    bool current_state = (GetAsyncKeyState(vk) & KEY_DOWN_MASK) != 0;
    bool last_state = m_key_states[vk];

    if (current_state && !last_state) {
        m_key_states[vk] = true;
        return true;
    } else if (!current_state) {
        m_key_states[vk] = false;
    }

    return false;
}

} // namespace cubiq::platform::win32
