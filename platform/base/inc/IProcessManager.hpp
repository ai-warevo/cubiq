#pragma once

#include <string>
#include <cstdint>
#include <optional>
#include <memory>

namespace cubiq::platform::base {

class IMemoryAccess;

/**
 * @brief Interface representing a process handle.
 */
class IProcess {
public:
    virtual ~IProcess() = default;
    virtual uint32_t get_pid() const = 0;
    virtual std::unique_ptr<IMemoryAccess> get_memory_access() const = 0;
    virtual uintptr_t get_module_base(const std::wstring& module_name) const = 0;
};

/**
 * @brief Interface for process management operations.
 */
class IProcessManager {
public:
    virtual ~IProcessManager() = default;

    virtual std::optional<uint32_t> get_pid_by_name(const std::wstring& process_name) const = 0;
    virtual std::unique_ptr<IProcess> open_process(uint32_t pid) const = 0;
    virtual std::unique_ptr<IProcess> open_process_by_name(const std::wstring& process_name) const = 0;
};

} // namespace cubiq::platform::base
