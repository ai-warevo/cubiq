# Project cubiq - Common Library Agent Manifest

This manifest contains specific instructions for agents working within `app/common/`.

## 🎯 Core Philosophy (Common)
The common library is the "Brain" of the project. It must be stable, highly modular, and follow strict namespace conventions to prevent collisions and ensure clarity.

## 🏗️ Architecture & Structure (Common)
- `math/`: [lib_math] Vector3, Matrix4x4.
- `structures/`: [lib_structs] Game structures and **Offsets**.
- `cheats/`: [lib_cheats] "The Brain" - Pure algorithmic logic.
- `utils/`: [lib_utils] Helpers (Logger, MemoryUtils).
- `gui/`: [lib_gui] ImGui wrappers and themes.

## ⚠️ Critical Rules for Common Library Development

1. **Namespace Hierarchy**: All code within `app/common/` MUST reside in the `cubiq::common::*` namespace hierarchy. 
   - Example: `app/common/utils/inc/MemoryUtils.hpp` $\rightarrow$ `namespace cubiq::common::utils`.
2. **Strict Inc/Src**: All modules must separate headers (`inc/`) from implementation (`src/`).
3. **Granularity**: Every feature is a module. Avoid monolithic files or large, multi-purpose utility classes.
4. **Single Source of Truth**: Offsets are stored ONLY in `app/common/structures/inc/Offsets.hpp`.

## 🤖 Agent Manifest (Roles)

### [Architect]
- **Focus:** Structural integrity and adherence to the modular design.
- **Instruction:** Ensure no circular dependencies exist and that all new features follow the `inc/src` and "Brain vs Hands" rules. Verify namespace compliance.

### [Developer]
- **Focus:** Writing clean, high-performance, production-grade C++.
- **Instruction:** Follow the `inc/src` rule strictly. Implement logic in `common` and implementation in feature folders. Use modern C++ standards. **NEVER forget the `cubiq::common::` namespace prefix.**

### [SecurityExpert]
- **Focus:** Stability (preventing crashes) and detection vectors.
- **Instruction:** Analyze code for potential memory access violations or patterns that could be flagged by anti-cheats.

---
*Last Updated: 2026-10-15*
