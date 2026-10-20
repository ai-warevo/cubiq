#include "Win32Input.hpp"

namespace cubiq::platform::win32 {

int Win32Input::to_vk(cubiq::Key key) const {
    switch (key) {
        case cubiq::Key::A: return 'A';
        case cubiq::Key::B: return 'B';
        case cubiq::Key::C: return 'C';
        case cubiq::Key::D: return 'D';
        case cubiq::Key::E: return 'E';
        case cubiq::Key::F: return 'F';
        case cubiq::Key::G: return 'G';
        case cubiq::Key::H: return 'H';
        case cubiq::Key::I: return 'I';
        case cubiq::Key::J: return 'J';
        case cubiq::Key::K: return 'K';
        case cubiq::Key::L: return 'L';
        case cubiq::Key::M: return 'M';
        case cubiq::Key::N: return 'N';
        case cubiq::Key::O: return 'O';
        case cubiq::Key::P: return 'P';
        case cubiq::Key::Q: return 'Q';
        case cubiq::Key::R: return 'R';
        case cubiq::Key::S: return 'S';
        case cubiq::Key::T: return 'T';
        case cubiq::Key::U: return 'U';
        case cubiq::Key::V: return 'V';
        case cubiq::Key::W: return 'W';
        case cubiq::Key::X: return 'X';
        case cubiq::Key::Y: return 'Y';
        case cubiq::Key::Z: return 'Z';
        case cubiq::Key::Up: return VK_UP;
        case cubiq::Key::Down: return VK_DOWN;
        case cubiq::Key::Left: return VK_LEFT;
        case cubiq::Key::Right: return VK_RIGHT;
        case cubiq::Key::Enter: return VK_RETURN;
        case cubiq::Key::Escape: return VK_ESCAPE;
        case cubiq::Key::Space: return VK_SPACE;
        case cubiq::Key::Shift: return VK_SHIFT;
        case cubiq::Key::Ctrl: return VK_CONTROL;
        case cubiq::Key::Alt: return VK_MENU;
        case cubiq::Key::F1: return VK_F1;
        case cubiq::Key::F2: return VK_F2;
        case cubiq::Key::F3: return VK_F3;
        case cubiq::Key::F4: return VK_F4;
        case cubiq::Key::F5: return VK_F5;
        case cubiq::Key::F6: return VK_F6;
        case cubiq::Key::F7: return VK_F7;
        case cubiq::Key::F8: return VK_F8;
        case cubiq::Key::F9: return VK_F9;
        case cubiq::Key::F10: return VK_F10;
        case cubiq::Key::F11: return VK_F11;
        case cubiq::Key::F12: return VK_F12;
        case cubiq::Key::Back: return VK_BACK;
        case cubiq::Key::Delete: return VK_DELETE;
        case cubiq::Key::Insert: return VK_INSERT;
        case cubiq::Key::Home: return VK_HOME;
        case cubiq::Key::End: return VK_END;
        case cubiq::Key::PageUp: return VK_PRIOR;
        case cubiq::Key::PageDown: return VK_NEXT;
        default: return 0;
    }
}

bool Win32Input::is_key_down(cubiq::Key key) {
    int vk = to_vk(key);
    if (vk == 0) return false;
    return (GetAsyncKeyState(vk) & 0x8000) != 0;
}

bool Win32Input::is_key_pressed(cubiq::Key key) {
    int vk = to_vk(key);
    if (vk == 0) return false;

    bool current_state = (GetAsyncKeyState(vk) & 0x8000) != 0;
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
