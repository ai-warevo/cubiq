# Task 2: Core Decoupling (Dependency Injection)

## Context
- **Main Plan**: [plan.md](plan.md)
- **Architecture Reference**: [README.md](README.md)
- **Prerequisite**: [plan_task_1.md](plan_task_1.md) must be completed.

## Objective
Refactor the `core/` module to remove all direct dependencies on OS-specific utilities and implement Dependency Injection (DI).

## Done Condition
1. All modules in `core/cheats/` and `core/modes/` receive their dependencies (`IMemoryAccess*`, etc.) via constructors.
2. No component in `core/*` includes any files from `platform/win32/`.
3. All components in `core/*` include only interfaces from `platform/base/`.

## Steps
1. [ ] Audit `core/cheats/` and `core/modes/` for direct calls to `MemoryUtils`, `ProcessUtils`, etc.
2. [ ] Refactor constructors of all plugins (Aimbot, ESP, etc.) to accept interface pointers from `platform/base/`.
3. [ ] Refactor `core/modes/` (Engines) to accept and manage platform implementations via DI.
4. [ ] Remove any remaining direct utility includes in the `core/` directory.

## Verification
- Grep for any usage of `Win32*` or `platform/win32/` inside `core/`.
- Compile check to ensure `core/` only depends on `platform/base/`.
