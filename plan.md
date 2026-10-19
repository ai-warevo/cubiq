# Project Cubiq: Framework Transformation Plan

## 🎯 Main Goal
To transform **cubiq** from a single-game cheat project into a professional-grade, modular **Cheat Development Framework**. 

The ultimate objective is to create an environment where developing a cheat for a new game requires only defining its memory structures (offsets) and implementing a thin "glue" layer that **assembles** the desired functionality from available core plugins.

---

## 🧠 The Core Philosophy: Assembler Architecture
We move away from monolithic libraries towards a **Plugin & Engine** model based on **Inversion of Control (IoC)**. The architecture is divided into four distinct layers:

1.  **The Brain (`core/logic`) — [Plugins]**: Independent, granular algorithmic modules (e.g., `AimbotPlugin`, `ESPPlugin`). They are strictly decoupled from OS and game data; they receive dependencies via **Dependency Injection**.
2.  **The Engines (`core/modes`) — [Technical Modes & Lifecycle]**: The technical implementation of a mode and its OS-level lifecycle (e.g., `ExternalEngine` managing `WinMain`/Overlay, `InternalEngine` managing `DllMain`/Hooks).
3.  **The Glue (`games/{game}/implementation`) — [The Assembler]**: The layer that defines the final application. It selects which **Engine** to use, which **Plugins** to activate, and provides the data via interfaces.
4.  **The Data (`games/{game}/structures`) — [Source of Truth]**: Offsets and memory layouts unique to each game.

---

## 🛠️ The Problem (Current State)
Currently, the project is "coupled":
- **Logic depends on Data**: Algorithms in `app/common/cheats` directly include `Offsets.hpp`.
- **Implementation depends on Logic**: The modes (Internal/External) are mixed with game-specific code.
- **Lifecycle Leakage**: Game-specific code is responsible for OS-level entry points (`main`, `DllMain`), making it hard to reuse the "mode" logic.
- **Monolithic Interfaces**: We assume every object has "health" or "life", which breaks for non-shooter genres.
- **Platform Coupling**: Direct usage of `<windows.h>` and `<tlhelp32.h>` prevents testing without a live OS/Process environment.

---

## 🚀 Transformation Roadmap

### Phase 1: Structural Reorganization & Extraction (The "Great Split")
**What:** Rename directories and, most importantly, **extract** generic mode logic and lifecycle management from game-specific code.
**How:** 
- Create `core/modes/{external, internal, kernel}` to house the technical engines and OS entry points (`WinMain`, `DllMain` logic).
- Analyze `app/external`, `app/internal`, etc., and move the *generic engine logic* (e.g., overlay management, hook orchestration) into `core/modes`.
- Move the *game-specific implementation* (the "Glue") into `games/assaultcube/{external, internal, kernel}`.
- Create `core/logic/` for independent plugins.
**Why:** To establish the physical boundaries of the framework and ensure that Engines are reusable across all games.

### Phase 2: Interface Segregation & Platform Abstraction (The "Contract")
**What:** Replace monolithic interfaces with small, specialized ones and abstract the OS layer.
**How:** 
- **Granular Interfaces**: Create `core/interfaces/IPositionable`, `IValue`, `ILifeCycle`.
- **Platform Abstraction Layer (PAL)**: Create `core/platform/` containing interfaces like `IProcessManager` (replacing `tlhelp32.h`) and `IMemory`. 
- **Dependency Injection**: Ensure all `core/logic` modules receive their dependencies via constructors, never via static calls or global state.
**Why:** To allow support for any genre and enable **Unit Testing** by allowing Mock implementations of the OS and Memory.

### Phase 3: Logic Decoupling (The "Pluginization")
**What:** Refactor all algorithms into independent plugins that depend only on granular interfaces.
**How:** 
- Change `Aimbot::calculate(uintptr_t target)` $\rightarrow$ `Aimbot::execute(IPositionable* target)`.
- Ensure plugins have zero knowledge of game offsets or specific memory access methods.
**Why:** To make the "Brain" truly modular and pluggable.

### Phase 4: Implementation & Verification (The "First Assembler")
**What:** Re-implement AssaultCube as the first "client" of the new framework.
**How:** 
- Create `games/assaultcube/structures/`.
- Implement the Glue layer that connects `ACMemory` and `ACPlayer` to the core interfaces.
- In `main.cpp`, **assemble** the application by selecting the `ExternalEngine` (which handles the entry point) and specific plugins (`AimbotPlugin`, etc.).
**Why:** To prove the framework works as a true assembler/orchestrator.

---

## 📈 Success Criteria
1.  **Zero Game Knowledge in Core**: A developer can look at `core/logic/aimbot` and not find a single mention of "AssaultCube" or any specific offset.
2.  **Genre Agnostic**: The framework can support an RTS or RPG by simply using different plugins and interfaces.
3.  **Zero Bloat**: The final binary for a game contains *only* the code for the selected engines and plugins.
4.  **Testability**: Core logic can be verified via Unit Tests using Mock implementations of `IPlatform` and `IMemory`.
5.  **Rapid Prototyping**: Adding a new game is a matter of "assembling" existing parts in a new `games/` folder.
