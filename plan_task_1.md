# Task 1: Foundation (Platform Layer - Base & Win32)

## Context
- **Main Plan**: [plan.md](plan.md)
- **Architecture Reference**: [README.md](README.md)

## Objective
Create the platform abstraction layer to decouple the core from the OS and implement the first concrete Windows implementation.

## Done Condition
1. `platform/base/` exists and contains pure interfaces (`IMemoryAccess.hpp`, `IProcessManager.hpp`, `IWindow.hpp`).
2. `platform/win32/` exists and contains implementations of these interfaces using WinAPI.
3. No `<windows.h>` or `<tlhelp32.h>` is present outside of `platform/win32/`.
4. Existing utilities in `core/utils/inc/` are moved to `platform/win32/` and renamed (e.g., `Win32Memory.cpp`).

## Steps
1. [ ] Create directory structure: `platform/base/` and `platform/win32/`.
2. [ ] Define interfaces in `platform/base/` based on current `core/utils/inc/` logic (but OS-agnostic).
3. [ ] Move and refactor `core/utils/inc/*.hpp` and `*.cpp` into `platform/win32/`.
4. [ ] Implement Win32-specific logic in `platform/win32/` using `<windows.h>` and `<tlhelp32.h>`.
5. [ ] Clean up all `#include <windows.h>` from the rest of the codebase.

## Verification
- Grep for `<windows.h>` and `<tlhelp32.h>` to ensure they only appear in `platform/win32/`.
- Compile check (if CMake is ready).
