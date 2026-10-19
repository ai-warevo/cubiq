#pragma once

#include <string>
#include <functional>
#include <memory>
#include "core/utils/inc/IMemoryAccess.hpp"

namespace cubiq::common::utils { class Process; }

namespace cubiq::core::modes::external {

class ExternalEngine {
public:
    using LoopCallback = std::function<void(cubiq::common::utils::IMemoryAccess&, uintptr_t)>;

    ExternalEngine(const std::wstring& process_name);
    ~ExternalEngine();

    bool attach();
    uintptr_t get_module_base() const;
    void run(LoopCallback loop_callback);
    void stop();

private:
    std::wstring m_process_name;
    bool m_running = false;
    std::unique_ptr<cubiq::common::utils::Process> m_process;
};

} // namespace cubiq::core::modes::external
