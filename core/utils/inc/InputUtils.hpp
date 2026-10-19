#pragma once

#include <windows.h>
#include <vector>
#include <unordered_map>

namespace cubiq::common::utils {

class InputUtils {
public:
    // Checks if a key is currently held down
    static bool is_key_down(int vk_code);

    // Checks if a key was pressed since the last check (single press)
    bool is_key_pressed(int vk_code);

private:
    std::unordered_map<int, bool> m_key_states;
};

} // namespace cubiq::common::utils
