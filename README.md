# cubiq — Educational Framework for Advanced C++ Development

<div align="center">

⚠️ **CRITICAL NOTICE — READ CAREFULLY BEFORE PROCEEDING** ⚠️

⚠️ **ВНИМАНИЕ — ПРОЧТИТЕ ПЕРЕД ИЗУЧЕНИЕМ** ⚠️

</div>

---

## ⚖️ LEGAL, SAFETY & ANTI-CHEAT DISCLAIMER (MIT LICENSE INVARIANT)

### 🇬🇧 English Version

**This repository and all assets contained herein are provided strictly for educational, architectural analysis, and research purposes only.**

By compiling, launching, or interacting with the **cubiq** framework, you explicitly acknowledge and agree to the following terms:

* **No Affiliation:** This project is not affiliated, associated, authorized, endorsed by, or in any way officially connected with the developers of AssaultCube, or any of its subsidiaries or affiliates. All product and company names are trademarks™ or registered® trademarks of their respective holders.
* **Anti-Cheat & Account Security Risks:** Automated client manipulation, memory injection, and kernel-mode execution techniques may violate the End User License Agreement (EULA) or Terms of Service (ToS) of commercial software environments. Use of these techniques carries an inherent risk of permanent account termination, software bans, or hardware profiling flags (HWID bans). The authors assume absolute zero liability for any punitive actions executed by anti-cheat telemetry algorithms.
* **System Stability Warning:** This framework includes modules for **Kernel-mode development**. Improper implementation or execution of driver-level code can lead to critical system instability, including but not limited to: Blue Screen of Death (BSOD), data corruption, or operating system failure. Use at your own risk.
* **Warranty Exclusion (As-Is Basis):** THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE, AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES, OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT, OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

---

### 🇷🇺 Русская версия

**Данный репозиторий и все содержащиеся в нем активы предоставляются исключительно в образовательных целях, для архитектурного анализа и исследовательских задач.**

Компилируя, запуская или взаимодействуя с фреймворком **cubiq**, вы прямо подтверждаете свое согласие со следующими условиями:

* **Отсутствие аффилированности:** Данный проект не связан, не ассоциирован, не авторизован и не поддерживается разработчиками AssaultCube или любыми их дочерними компаниями. Все названия продуктов и компаний являются товарными знаками своих владельцев.
* **Риски античитов и безопасности аккаунтов:** Методы манипуляции клиентом, инъекции в память и выполнение кода на уровне ядра могут нарушать Лицензионное соглашение (EULA) или Условия использования (ToS). Использование данных методов несет неотъемлемый риск перманентной блокировки аккаунта, программного бана или блокировки по идентификатору оборудования (HWID). Авторы несут нулевую ответственность за любые карательные меры со стороны античитов.
* **Предупреждение о стабильности системы:** Фреймворк включает модули для **разработки на уровне ядра (Kernel-mode)**. Неправильная реализация или выполнение кода драйвера может привести к критической нестабильности системы, включая, помимо прочего: BSOD (синий экран смерти), повреждение данных или отказ операционной системы. Используйте на свой страх и риск.
* **Отказ от гарантий (Принцип "Как есть"):** ПРОГРАММНОЕ ОБЕСПЕЧЕНИЕ ПРЕДОСТАВЛЯЕТСЯ "КАК ЕСТЬ", БЕЗ КАКИХ-ЛИБО ГАРАНТИЙ, ЯВНЫХ ИЛИ ПОДРАЗУМЕВАЕМЫХ. АВТОРЫ НЕ НЕСУТ ОТВЕТСТВЕННОСТИ ЗА ЛЮБЫЕ ПРЕТЕНЗИИ, УЩЕРБ ИЛИ ИНЫЕ ОБЯЗАТЕЛЬСТВА, ВОЗНИКАЮЩИЕ В РЕЗУЛЬТАТЕ ИСПОЛЬЗОВАНИЯ ДАННОГО ПО.

---

## 🎯 О проекте

**cubiq** — это учебная среда (framework), предназначенная для изучения разработки инструментов взаимодействия с процессами на разных уровнях системы. Проект построен на принципах чистого кода и профессиональной архитектуры.

### Основные цели обучения:
1. **Разноуровневое программирование:** Изучение разницы между External, Internal и Kernel-mode.
2. **Архитектурное мышление:** Разделение "Мозгов" (логика) от "Рук" (реализация).
3. **Профессиональный C++:** Работа с CMake, модульная сборка, управление зависимостями.

## 🏗️ Архитектура проекта (Assembler Model)

Проект перешел от монолитной структуры к модели **Plugin & Engine**, основанной на инверсии управления (IoC). Архитектура разделена на четыре четких уровня:

### 🧠 Четыре слоя системы:

1.  **The Brain (`core/cheats`) — [Plugins]**:
    Независимые, гранулярные алгоритмические модули (например, `AimbotPlugin`, `ESPPlugin`). Они полностью отвязаны от ОС и данных игры; зависимости внедряются через **Dependency Injection**.

2.  **The Engines (`core/modes`) — [Technical Modes]**:
    Техническая реализация режима и его жизненного цикла на уровне ОС (например, `ExternalEngine` управляет окном/overlay, `InternalEngine` управляет хуками/DllMain).

3.  **The Glue (`games/{game}/{mode}`) — [The Assembler]**:
    Слой, определяющий финальное приложение. Он выбирает нужный **Engine**, активирует необходимые **Plugins** и предоставляет им данные через интерфейсы.

4.  **The Data (`games/{game}/structures`) — [Source of Truth]**:
    Оффсеты и структуры памяти, уникальные для каждой конкретной игры.

---

### 📂 Структура каталогов:

- `docs/` — Исследования, теория математики и туториалы.
- `core/` — Ядро фреймворка:
    - `cheats/` — "Мозги" (плагины).
    - `modes/` — "Двигатели" (техническая реализация режимов).
    - `interfaces/` — Контракты и абстракции.
    - `math/`, `structures/`, `utils/`, `gui/` — Базовые компоненты.
- `games/{game}` — Реализации конкретных игр:
    - `external/` — Внешний режим (External).
    - `internal/` — Внутренний режим (Internal).
    - `kernel/` — Режим работы с драйвером (Kernel: Driver + Client).
    - `structures/` — Данные игры (оффсеты).
- `tests/` — Тесты для проверки корректности работы модулей.
- `tools/` — Инструменты сборки и разработки.

---



## 🛠️ Сборка проекта

### Требования:
* C++ Compiler (MSVC рекомендуется).
* CMake (3.15+).
* Make

### Zapusk
```sh
make
```
---
*Разработано в образовательных целях.*
