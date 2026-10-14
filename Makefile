# Configuration mode: Debug or Release (default: Debug)
CONFIG ?= Release

# Default target: build everything
all: build_common build_internal build_external build_kernel

.PHONY: all build_common build_internal build_external build_kernel clean

# Build common (the foundation)
build_common:
	@echo "Building cubiq_common in $(CONFIG) mode..."
	mkdir -p build/common
	cmake -S . -B build/common -DCOMMON_ONLY=ON -DCMAKE_BUILD_TYPE=$(CONFIG)
	cmake --build build/common --config $(CONFIG)

# Build internal
build_internal: build_common
	@echo "Building cubiq_internal in $(CONFIG) mode..."
	mkdir -p build/internal
	cmake -S . -B build/internal -DINTERNAL_ONLY=ON -DCMAKE_BUILD_TYPE=$(CONFIG)
	cmake --build build/internal --config $(CONFIG)

# Build external
build_external: build_common
	@echo "Building cubiq_external in $(CONFIG) mode..."
	mkdir -p build/external
	cmake -S . -B build/external -DEXTERNAL_ONLY=ON -DCMAKE_BUILD_TYPE=$(CONFIG)
	cmake --build build/external --config $(CONFIG)

# Build kernel
build_kernel: build_common
	@echo "Building cubiq_kernel in $(CONFIG) mode..."
	mkdir -p build/kernel
	cmake -S . -B build/kernel -DKERNEL_ONLY=ON -DCMAKE_BUILD_TYPE=$(CONFIG)
	cmake --build build/kernel --config $(CONFIG)

# Clean build directories
clean:
	@echo "Cleaning build directories..."
	rm -rf build/
