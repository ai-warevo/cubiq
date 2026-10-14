# Default target: build everything
all: build_common build_internal build_external build_kernel

.PHONY: all build_common build_internal build_external build_kernel clean

# Build common (the foundation)
build_common:
	@echo "Building cubiq_common..."
	mkdir -p build/common
	cmake -S . -B build/common -DCOMMON_ONLY=ON
	cmake --build build/common

# Build internal
build_internal: build_common
	@echo "Building cubiq_internal..."
	mkdir -p build/internal
	cmake -S . -B build/internal -DINTERNAL_ONLY=ON
	cmake --build build/internal

# Build external
build_external: build_common
	@echo "Building cubiq_external..."
	mkdir -p build/external
	cmake -S . -B build/external -DEXTERNAL_ONLY=ON
	cmake --build build/external

# Build kernel
build_kernel: build_common
	@echo "Building cubiq_kernel..."
	mkdir -p build/kernel
	cmake -S . -B build/kernel -DKERNEL_ONLY=ON
	cmake --build build/kernel

# Clean build directories
clean:
	@echo "Cleaning build directories..."
	rm -rf build/
