#include "core/modes/external/inc/ExternalEngine.hpp"
#include <thread>
#include <chrono>

namespace cubiq::core::modes::external {

ExternalEngine::ExternalEngine(const std::wstring& process_name, cubiq::platform::base::IProcessManager& process_manager)
    : m_process_name(process_name), m_process_manager(process_manager) {}

ExternalEngine::~ExternalEngine() {
    stop();
}

bool ExternalEngine::attach() {
    m_process = m_process_manager.open_process_by_name(m_process_name);
    return m_process != nullptr;
}

uintptr_t ExternalEngine::get_module_base() const {
    if (!m_process) return 0;
    // For now, we'll assume the first module is the base if no name is provided.
    // But let's just use a dummy name or something for now to satisfy the interface.
    return m_process->get_module_base(L""); 
}

void ExternalEngine::run(LoopCallback loop_callback) {
    if (!m_process) return;

    uintptr_t module_base = get_module_base();
    auto mem = m_process->get_memory_access();

    m_running = true;
    while (m_running) {
        loop_callback(*mem, module_base);
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
}

void ExternalEngine::stop() {
    m_running = false;
}

} // namespace cubiq::core::modes::external
