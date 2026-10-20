# Task 3: Orchestration & Composition Root

## Context
- **Main Plan**: [plan.md](plan.md)
- **Architecture Reference**: [README.md](README.md)
- **Prerequisite**: [plan_task_2.md](plan_task_2.md) must be completed.

## Objective
Implement the "Assembler" logic by creating a Composition Root in the game's entry point, tying Engines, Plugins, and Platform implementations together.

## Done Condition
1. `games/{game}/{mode}/main.cpp` exists and acts as the Composition Root.
2. The application is fully assembled: `Platform Implementation` $\rightarrow$ `Engine` $\rightarrow$ `Plugins`.
3. No logic in `core/` or `platform/` handles the instantiation of concrete OS-specific classes.

## Steps
1. [ ] Identify/Create the entry point for a specific game mode (e.g., `games/assaultcube/external/main.cpp`).
2. [ ] Implement the assembly logic:
    * Instantiate concrete platform objects (`Win32Memory`, etc.).
    * Instantiate the Engine (`ExternalEngine`).
    * Instantiate Plugins (`Aimbot`, etc.) and inject dependencies.
3. [ ] Ensure the `Engine` manages the lifecycle of the injected components.

## Verification
- Run the application to ensure it starts and correctly initializes all modules via the Assembler.
- Verify that no "glue" code is leaked into the `core/` or `platform/` layers.
