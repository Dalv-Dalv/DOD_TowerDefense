# DOD Tower Defense

## Prerequisites

| Tool | Minimum Version | Notes |
|------|----------------|-------|
| **CMake** | 4.3 | Must be on `PATH` |
| **C++ Compiler** | C++23 support | MSVC 2022, GCC 13, or Clang 17+ |
| **Git** | Any recent version | Required by CMake `FetchContent` to clone dependencies |
| **Internet connection** | — | Needed on first configure to download raylib, ImGui, rlImGui |

> **Windows users:** The easiest compiler setup is [Visual Studio 2022](https://visualstudio.microsoft.com/) (with the *Desktop development with C++* workload) or [MSYS2/MinGW-w64](https://www.msys2.org/).

---

## Dependencies (auto-fetched)

CMake `FetchContent` will automatically download these on first configure — no manual installation needed:

- [raylib 6.0](https://github.com/raysan5/raylib/tree/6.0) — graphics & windowing
- [Dear ImGui v1.92.7](https://github.com/ocornut/imgui/tree/v1.92.7) — debug UI panel
- [rlImGui (Raylib_6_0 branch)](https://github.com/raylib-extras/rlImGui) — raylib <-> ImGui bridge

---

## Building

### 1. Clone the repository

```bash
git clone <your-repo-url>
cd DOD_TowerDefense
```

### 2. Configure with CMake

```bash
cmake -B build -S .
```

> On first run this will clone and compile raylib, ImGui, and rlImGui — this can take a few minutes.

To target a specific generator (e.g. Visual Studio 2022):

```bash
cmake -B build -S . -G "Visual Studio 17 2022"
```

### 3. Build the executable

```bash
cmake --build build --config Release
```

Or for a debug build:

```bash
cmake --build build --config Debug
```

---

## Running

After a successful build the executable is located at:

```
build/Release/DOD_TowerDefense.exe   # Windows Release
build/Debug/DOD_TowerDefense.exe     # Windows Debug
build/DOD_TowerDefense               # Linux / macOS
```

Run it directly from your terminal or file explorer:

```bash
./build/Release/DOD_TowerDefense.exe
```