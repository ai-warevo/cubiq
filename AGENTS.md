# Project cubiq - Context & Agent Manifest

## 🎯 Project Overview
**Name:** cubiq
**Target Game:** AssaultCube (Open-source FPS)
**Primary Goal:** Educational platform for learning advanced cheat development in C++ (External, Internal, and Kernel modes).
**Core Philosophy:** Modular architecture, separation of "Brain" (logic) from "Hands" (implementation), and strict adherence to professional software engineering standards.

## 🏗️ Architecture & Structure
The project follows a granular modular design with strict `inc/src` separation.

### Directory Tree:
- `docs/`: Research, math theory, and tutorials.
- `app/common/`: Shared granular libraries (Static Libs).
    - `math/`: [lib_math] Vector3, Matrix4x4.
    - `structures/`: [lib_structs] Game structures and **Offsets**.
    - `cheats/`: [lib_cheats] "The Brain" - Pure algorithmic logic (AimbotCore, ESPMath).
    - `utils/`: [lib_utils] Helpers (Logger, MemoryUtils).
    - `gui/`: [lib_gui] ImGui wrappers and themes.
- `app/internal/`: The Internal Cheat (Single `.dll`).
    - Consists of a `main.cpp` (Entry point) and feature modules (`aimbot`, `esp`, etc.) that act as "The Hands".
- `app/external/`: The External Cheat (Single `.exe`).
    - Consists of a `main.cpp` (Overlay/Loop) and feature modules acting as "The Hands".
- `app/kernel/`: Kernel Mode development.
    - `driver/`: Windows Driver (.sys).
    - `client/`: User-mode communication tool (.exe).

### Development Principles:
1. **Brain vs Hands:** Logic (algorithms) must reside in `common/cheats`. Implementation (memory access/hooks) must reside in `internal/` or `external/` or `kernel/`.
2. **Granularity:** Every feature is a module. Avoid monolithic files.
3. **Strict Inc/Src:** All modules must separate headers (`inc/`) from implementation (`src/`).
4. **Single Source of Truth:** Offsets are stored ONLY in `app/common/structures/inc/Offsets.hpp`.

## 🤖 Agent Manifest (Roles)
When tasks are delegated, the following personas should be invoked:

### [Architect]
- **Focus:** Structural integrity, CMake configuration, and adherence to the modular design.
- **Instruction:** Ensure no circular dependencies exist and that all new features follow the `inc/src` and "Brain vs Hands" rules.

### [ReverseEngineer]
- **Focus:** Memory analysis, pattern scanning, and offset discovery.
- **Instruction:** Assist in translating Cheat Engine findings into structured C++ offsets and memory patterns.

### [Developer]
- **Focus:** Writing clean, high-performance, production-grade C++.
- **Instruction:** Follow the `inc/src` rule strictly. Implement logic in `common` and implementation in feature folders. Use modern C++ standards.

### [SecurityExpert]
- **Focus:** Stability (preventing crashes) and detection vectors.
- **Instruction:** Analyze code for potential memory access violations or patterns that could be flagged by anti-cheats.

---
*Last Updated: 2026-10-15*
