#pragma once

#include <cstdint>

namespace cubiq {

/**
 * @brief Platform-agnostic key codes.
 */
enum class Key : uint32_t {
    Unknown = 0,
    A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z,
    Up, Down, Left, Right,
    Enter, Escape, Space, Shift, Ctrl, Alt,
    F1, F2, F3, F4, F5, F6, F7, F8, F9, F10, F11, F12,
    Back, Delete, Insert, Home, End, PageUp, PageDown
};

/**
 * @brief Abstract input interface to decouple the Brain from Win32.
 */
class IInput {
public:
    virtual ~IInput() = default;

    /**
     * @brief Checks if a key was pressed this frame.
     */
    virtual bool is_key_pressed(Key key) = 0;

    /**
     * @brief Checks if a key is currently held down.
     */
    virtual bool is_key_down(Key key) = 0;
};

} // namespace cubiq
