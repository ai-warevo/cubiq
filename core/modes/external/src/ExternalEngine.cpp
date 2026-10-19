#include "core/modes/external/inc/ExternalEngine.hpp"
#include "core/utils/inc/Process.hpp"
#include "core/utils/inc/ProcessUtils.hpp"
#include "core/utils/inc/MemoryUtils.hpp"
#include <memory>

namespace cubiq::core::modes::external {

ExternalEngine::ExternalEngine(const std::wstring& process_name)
    : m_process_name(process_name) {}

ExternalEngine::~ExternalEngine() {
    stop();
}

bool ExternalEngine::attach() {
    m_process = std::make_unique<cubiq::common::utils::Process>(m_process_name);
    return m_process->is_valid();
}

uintptr_t ExternalEngine::get_module_base() const {
    if (!m_process || !m_process->is_valid()) return 0;
    return m_process->get_module_base(m_process_name);
}

void ExternalEngine::run(LoopCallback loop_callback) {
    if (!m_process || !m_process->is_valid()) return;

    uintptr_t module_base = get_module_base();
    cubiq::common::utils::MemoryReaderWriter mem(m_process->get_handle());

    m_running = true;
    while (m_running) {
        loop_callback(mem, module_base);
        Sleep(10);
    }
}

void ExternalEngine::stop() {
    m_running = false;
}

} // namespace cubiq::core::modes::external

