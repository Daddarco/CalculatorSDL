# CalculatorSDL

Una calcolatrice semplice scritta in **C** utilizzando **SDL3** e **Cross-Platform** (Linux e Windows).

## Requisiti
- **CMake** (versione 3.25 o superiore)
- **Compilatore C** (GCC, Clang o MSVC)
- **Librerie (Linux)**: `libdecor-devel` (Fedora) o `libdecor-0-dev` (Ubuntu),... per supporto Wayland.

## Compilazione da sorgente

1. **Clona il repository**:
   ```bash
   git clone https://github.com/Daddarco/CalculatorSDL.git
   cd CalculatorSDL
   ```

2. **Configura il progetto**:
   ```bash
   cmake -B build -DCMAKE_BUILD_TYPE=Release
   ```
   *(La prima volta potrebbe richiedere qualche minuto per scaricare e compilare SDL3)*

3. **Compila**:
   ```bash
   cmake --build build --config Release
   ```

4. **Avvia**:
   - **Linux**: `./build/CalculatorSDL`
   - **Windows**: `build\Release\CalculatorSDL.exe`

## 📦 Release
Gli eseguibili pre-compilati per **Windows** e **Linux** sono disponibili nella sezione [Releases](https://github.com/Daddarco/CalculatorSDL/releases).
