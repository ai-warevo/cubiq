#pragma once

#include <string>
#include <functional>
#include <memory>
#include "platform/base/inc/IMemoryAccess.hpp"
#include "platform/base/inc/IProcessManager.hpp"

namespace cubiq::core::modes::external {

class ExternalEngine {
public:
    using LoopCallback = std::function<void(cubiq::platform::base::IMemoryAccess&, uintptr_t)>;

    ExternalEngine(const std::wstring& process_name, cubiq::platform::base::IProcessManager& process_manager);
    ~ExternalEngine();

    bool attach();
    uintptr_t get_module_base() const;
    void run(LoopCallback loop_callback);
    void stop();

private:
    std::wstring m_process_name;
    bool m_running = false;
    std::unique_ptr<cubiq::platform::base::IProcess> m_process;
    cubiq::platform::base::IProcessManager& m_process_manager;
};

} // namespace cubiq::core::modes::external
