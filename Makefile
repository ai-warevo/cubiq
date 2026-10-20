# Configuration mode: Debug or Release (default: Release)
CONFIG ?= Release
ARGS ?=
EXTRA_CMAKE_ARGS ?=

# Parse positional arguments for 'make build <game> <type>' and 'make run <game> <type>'
ifeq ($(firstword $(MAKECMDGOALS)),build)
  GAME := $(word 2,$(MAKECMDGOALS))
  TYPE := $(word 3,$(MAKECMDGOALS))
endif

ifeq ($(firstword $(MAKECMDGOALS)),run)
  GAME := $(word 2,$(MAKECMDGOALS))
  TYPE := $(word 3,$(MAKECMDGOALS))
endif

export GAME TYPE ARCH CONFIG

.PHONY: help build run clean _common _build_logic

help:
	@echo "Cubiq Build System"
	@echo ""
	@echo "Usage:"
	@echo "  make help                      Show this help message"
	@echo "  make build <game> <type>       Build a specific game component"
	@echo "  make run <game> <type>         Build and run a specific game component"
	@echo "  make clean                     Remove all build artifacts"
	@echo ""
	@echo "Arguments:"
	@echo "  <game>    Name of the game (e.g., assaultcube, killingfloor2)"
	@echo "  <type>    Type: common, internal, external, kernel_driver, kernel_client"
	@echo ""
	@echo "Examples:"
	@echo "  make build assaultcube common ARCH=Win32"
	@echo "  make build assaultcube external ARCH=Win32"
	@echo "  make build assaultcube internal ARCH=Win32"
	@echo "  make build assaultcube kernel_driver ARCH=x64"
	@echo "  make build assaultcube kernel_client ARCH=Win32"
	@echo "  make run assaultcube external ARCH=Win32"
	@echo "  make run assaultcube kernel_client ARCH=Win32"
	@echo ""
	@echo "Options:"
	@echo "  ARCH=x64|Win32                 MANDATORY: Specify architecture"
	@echo "  CONFIG=Debug|Release           Set build configuration (default: Release)"
	@echo "  ARGS=\"...\"                     Pass arguments to the running binary"
	@echo "  EXTRA_CMAKE_ARGS=\"...\"        Pass additional -D flags to CMake"
	@echo ""

# Internal target to ensure common is built first
_common:
	@echo "Building cubiq_common in $(CONFIG) mode with ARCH=$(ARCH)..."
	mkdir -p build/common_$(ARCH)
	cmake -S . -B build/common_$(ARCH) -DCOMMON_ONLY=ON -DCMAKE_BUILD_TYPE=$(CONFIG) -A $(ARCH) $(EXTRA_CMAKE_ARGS)
	cmake --build build/common_$(ARCH) --config $(CONFIG)

# Main build target: make build <game> <type>
build:
	@if [ -z "$(ARCH)" ]; then \
		echo "Error: ARCH is mandatory (e.g., ARCH=x64 or ARCH=Win32)."; \
		exit 1; \
	fi
	@if [ -z "$(GAME)" ] || [ -z "$(TYPE)" ]; then \
		echo "Error: Missing arguments. Type 'make help' for usage."; \
		exit 1; \
	fi
	@if [ "$(TYPE)" != "common" ]; then "$(MAKE)" _common; fi
	@"$(MAKE)" _build_logic

_build_logic:
	@case "$(TYPE)" in \
		common) TYPE_FLAG="COMMON_ONLY"; BUILD_DIR="common_$(ARCH)" ;; \
		internal) TYPE_FLAG="INTERNAL_ONLY"; BUILD_DIR="$(GAME)_internal_$(ARCH)" ;; \
		external) TYPE_FLAG="EXTERNAL_ONLY"; BUILD_DIR="$(GAME)_external_$(ARCH)" ;; \
		kernel_driver) TYPE_FLAG="DRIVER_ONLY"; BUILD_DIR="$(GAME)_kernel_driver_$(ARCH)" ;; \
		kernel_client) TYPE_FLAG="CLIENT_ONLY"; BUILD_DIR="$(GAME)_kernel_client_$(ARCH)" ;; \
		*) echo "Error: Invalid type '$(TYPE)'. Use common, internal, external, kernel_driver, or kernel_client."; exit 1 ;; \
	esac; \
	echo "Building $(GAME) $(TYPE) in $(CONFIG) mode with ARCH=$(ARCH)..."; \
	mkdir -p build/$$BUILD_DIR; \
	cmake -S . -B build/$$BUILD_DIR -DGAME_NAME=$(GAME) -D$$TYPE_FLAG=ON -DCMAKE_BUILD_TYPE=$(CONFIG) -A $(ARCH) $(EXTRA_CMAKE_ARGS); \
	cmake --build build/$$BUILD_DIR --config $(CONFIG)


# Main run target: make run <game> <type>
run: build
	@if [ -z "$(ARCH)" ]; then \
		echo "Error: ARCH is mandatory (e.g., ARCH=x64 or ARCH=Win32)."; \
		exit 1; \
	fi
	@if [ -z "$(GAME)" ] || [ -z "$(TYPE)" ]; then \
		echo "Error: Missing arguments. Type 'make help' for usage."; \
		exit 1; \
	fi
	@case "$(TYPE)" in \
		internal) DIR="$(GAME)_internal_$(ARCH)" ;; \
		external) DIR="$(GAME)_external_$(ARCH)" ;; \
		kernel_driver) DIR="$(GAME)_kernel_driver_$(ARCH)" ;; \
		kernel_client) DIR="$(GAME)_kernel_client_$(ARCH)" ;; \
		*) echo "Error: Invalid type '$(TYPE)'. Use internal, external, kernel_driver, or kernel_client."; exit 1 ;; \
	esac; \
	echo "Running $(GAME) $(TYPE) in $(CONFIG) mode..."; \
	BINARY=$$(find build/$$DIR -name "*.exe" ! -path "*/CMakeFiles/*" | head -n 1); \
	if [ -z "$$BINARY" ]; then \
		echo "Error: Could not find binary for $(GAME) $(TYPE) in build/$$DIR"; \
		exit 1; \
	fi; \
	echo "Found binary: $$BINARY"; \
	if [ -z "$(ARGS)" ]; then \
		powershell -Command "Start-Process '$$BINARY' -Verb RunAs"; \
	else \
		powershell -Command "Start-Process '$$BINARY' -ArgumentList '$(ARGS)' -Verb RunAs"; \
	fi

# Clean build directories
clean:
	@echo "Cleaning build directories..."
	rm -rf build/

# Catch-all to prevent "No rule to make target" errors for the arguments
%:
	@:
