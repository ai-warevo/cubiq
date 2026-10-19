#include <windows.h>
#include <tlhelp32.h>
#include <iostream>
#include <vector>
#include <string>
#include <keystone/keystone.h>
#include "ldisasm.h" // Подключаем автоматический измеритель длины инструкций

#pragma comment(lib, "keystone.lib")

struct FullyDynamicHook {
    bool isActive = false;
    LPVOID allocatedMemory = nullptr;
    DWORD_PTR injectAddress = 0;
    size_t calculatedLength = 0;      // Посчитается автоматом!
    std::vector<BYTE> originalBytes;  // Считается автоматом!
};

// Функция для получения базового адреса
DWORD_PTR GetModuleBaseAddress(DWORD procId, const wchar_t* modName) {
    DWORD_PTR modBaseAddr = 0;
    HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, procId);
    if (hSnap != INVALID_HANDLE_VALUE) {
        MODULEENTRY32 modEntry;
        modEntry.dwSize = sizeof(modEntry);
        if (Module32First(hSnap, &modEntry)) {
            do {
                if (_wcsicmp(modEntry.szModule, modName) == 0) {
                    modBaseAddr = (DWORD_PTR)modEntry.modBaseAddr;
                    break;
                }
            } while (Module32Next(hSnap, &modEntry));
        }
    }
    CloseHandle(hSnap);
    return modBaseAddr;
}

// [ENABLE] — ПОЛНЫЙ АВТОМАТ. Никаких ручных размеров инструкций.
bool EnableAutoCheat(HANDLE hProcess, DWORD_PTR targetAddress, DWORD_PTR playerPointerAddress, FullyDynamicHook& hook) {
    if (hook.isActive) return false;

    hook.injectAddress = targetAddress;

    // 1. АВТО-ВЫЧИСЛЕНИЕ ДЛИНЫ: Читаем буфер с запасом (x86 инструкция макс 15 байт)
    BYTE memoryBuffer[32];
    ReadProcessMemory(hProcess, (LPCVOID)targetAddress, memoryBuffer, sizeof(memoryBuffer), nullptr);

    // Считаем, сколько инструкций суммарно дадут нам >= 5 байт для JMP
    size_t totalLength = 0;
    while (totalLength < 5) {
        // ldisasm возвращает длину конкретной инструкции по указателю (false = 32-бит режим)
        size_t currentInstructionLength = ldisasm(&memoryBuffer[totalLength], false); 
        if (currentInstructionLength == 0) {
            std::cout << "[ОШИБКА] ldisasm не смог распознать инструкцию.\n";
            return false;
        }
        totalLength += currentInstructionLength;
    }

    // Записываем полученную длину в структуру и делаем под нее точный бэкап
    hook.calculatedLength = totalLength;
    hook.originalBytes.resize(totalLength);
    memcpy(hook.originalBytes.data(), memoryBuffer, totalLength);

    std::cout << "[ИНФО] Автомат определил длину затираемого участка: " << hook.calculatedLength << " байт.\n";

    // 2. ALLOC: Выделяем память под Code Cave
    hook.allocatedMemory = VirtualAllocEx(hProcess, nullptr, 2048, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
    if (!hook.allocatedMemory) return false;

    ks_engine *ks;
    if (ks_open(KS_ARCH_X86, KS_MODE_32, &ks) != KS_ERR_OK) {
        VirtualFreeEx(hProcess, hook.allocatedMemory, 0, MEM_RELEASE);
        return false;
    }

    // 3. Переводим АВТОМАТИЧЕСКИ считанные байты в "db 0xXX..."
    std::string originalBytesAsm = "db ";
    for (size_t i = 0; i < hook.calculatedLength; i++) {
        char buf[16];
        sprintf_s(buf, "0x%02X", hook.originalBytes[i]);
        originalBytesAsm += buf;
        if (i < hook.calculatedLength - 1) originalBytesAsm += ", ";
    }

    // 4. Генерируем асм-код. Адрес возврата зависит от автоматически вычисленной длины.
    DWORD_PTR returnAddress = hook.injectAddress + hook.calculatedLength;
    std::string asmCode = 
        "mov eax, [" + std::to_string(playerPointerAddress) + "];"
        "add eax, 0x0E8;"
        "cmp ebx, eax;"
        "je originalcode;"
        "mov dword ptr [ebx+04], 0;"

        "originalcode:;"
        + originalBytesAsm + ";" 

        "jmp " + std::to_string(returnAddress) + ";";

    // 5. Компилируем Code Cave
    unsigned char *encode;
    size_t size;
    size_t count;
    if (ks_asm(ks, asmCode.c_str(), (uint64_t)hook.allocatedMemory, &encode, &size, &count) != KS_ERR_OK) {
        std::cout << "[ОШИБКА] Сбой компиляции.\n";
        ks_close(ks);
        VirtualFreeEx(hProcess, hook.allocatedMemory, 0, MEM_RELEASE);
        return false;
    }

    WriteProcessMemory(hProcess, hook.allocatedMemory, encode, size, nullptr);
    ks_free(encode);

    // 6. Пишем хук (JMP). Оставшееся место автомат сам забьет NOP'ами
    std::string hookCode = "jmp " + std::to_string((DWORD_PTR)hook.allocatedMemory) + ";";
    if (ks_asm(ks, hookCode.c_str(), hook.injectAddress, &encode, &size, &count) == MAP_FAILED ? false : true) { // Проверка Keystone
        std::vector<BYTE> finalHookBytes(encode, encode + size);
        ks_free(encode);

        // Автоматическая добивка NOP (0x90) до расчетной длины
        while (finalHookBytes.size() < hook.calculatedLength) {
            finalHookBytes.push_back(0x90);
        }

        DWORD oldProtect;
        VirtualProtectEx(hProcess, (LPVOID)hook.injectAddress, hook.calculatedLength, PAGE_EXECUTE_READWRITE, &oldProtect);
        WriteProcessMemory(hProcess, (LPVOID)hook.injectAddress, finalHookBytes.data(), finalHookBytes.size(), nullptr);
        VirtualProtectEx(hProcess, (LPVOID)hook.injectAddress, hook.calculatedLength, oldProtect, &oldProtect);
    }

    ks_close(ks);
    hook.isActive = true;
    return true;
}

// [DISABLE] — Чистый возврат
void DisableAutoCheat(HANDLE hProcess, FullyDynamicHook& hook) {
    if (!hook.isActive) return;

    DWORD oldProtect;
    VirtualProtectEx(hProcess, (LPVOID)hook.injectAddress, hook.calculatedLength, PAGE_EXECUTE_READWRITE, &oldProtect);
    
    // Возвращаем ровно то количество байт, которое посчитал автомат
    WriteProcessMemory(hProcess, (LPVOID)hook.injectAddress, hook.originalBytes.data(), hook.calculatedLength, nullptr);
    
    VirtualProtectEx(hProcess, (LPVOID)hook.injectAddress, hook.calculatedLength, oldProtect, &oldProtect);
    VirtualFreeEx(hProcess, hook.allocatedMemory, 0, MEM_RELEASE);

    hook.allocatedMemory = nullptr;
    hook.isActive = false;
    std::cout << "[DISABLE] Чит выгружен.\n";
}

int main() {
    setlocale(LC_ALL, "Russian");

    DWORD processId = 0;
    HWND hWindow = FindWindowW(NULL, L"AssaultCube");
    if (!hWindow) return 1;
    GetWindowThreadProcessId(hWindow, &processId);

    HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, processId);
    DWORD_PTR baseAddress = GetModuleBaseAddress(processId, L"ac_client.exe");

    if (!hProcess || !baseAddress) return 1;

    FullyDynamicHook hook;

    // ВХОДНЫЕ ДАННЫЕ: Передаем ТОЛЬКО адреса. Никаких длин и размеров!
    DWORD_PTR injectAddr = baseAddress + 0x1C223;
    DWORD_PTR playerPtr = baseAddress + 0x17E0A8;

    std::cout << "[NUMPAD 1] — ВКЛ/ВЫКЛ. [END] — Выход.\n";

    while (true) {
        if (GetAsyncKeyState(VK_NUMPAD1) & 1) {
            if (!hook.isActive) EnableAutoCheat(hProcess, injectAddr, playerPtr, hook);
            else DisableAutoCheat(hProcess, hook);
        }
        if (GetAsyncKeyState(VK_END) & 1) {
            if (hook.isActive) DisableAutoCheat(hProcess, hook);
            break;
        }
        Sleep(10);
    }

    CloseHandle(hProcess);
    return 0;
}
