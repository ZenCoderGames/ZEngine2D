# VSCode Configuration for ZEngine2D

This directory contains VSCode configuration files for building, running, and debugging the ZEngine2D project.

## Files

### launch.json
Debug configurations for running the game with various debuggers.

**Configurations:**
- `(Windows) Launch with MSVC Debugger` - **RECOMMENDED** for Windows with Visual Studio installed
- `(Windows) Launch with GDB` - For MinGW/GDB on Windows
- `(Linux/Mac) Launch with GDB/LLDB` - For Unix-based systems
- `(Windows) Launch Release` - Run optimized release build
- `(Windows) Attach to Process` - Attach to running game process

### tasks.json
Build tasks for compiling the project using CMake.

**Tasks:**
- `CMake: Configure` - Initialize CMake build system (Debug)
- `CMake: Build (Debug)` - Compile debug build (**default**: Ctrl+Shift+B)
- `CMake: Build (Release)` - Compile release build
- `CMake: Clean` - Remove build artifacts
- `CMake: Rebuild` - Clean and rebuild from scratch
- `Run Game` - Execute the game without debugging
- `Build and Run` - Build then execute

### settings.json
Project-specific settings for C++ IntelliSense and CMake integration.

## Quick Start

### First Time Setup

1. **Install Required VSCode Extensions:**
   - C/C++ (Microsoft) - `ms-vscode.cpptools`
   - CMake Tools (optional) - `ms-vscode.cmake-tools`

2. **Install Dependencies:**
   - SDL2, SDL2_image, SDL2_ttf, SDL2_mixer
   - Lua 5.1
   - CMake 3.14+
   - Compiler: MSVC (Visual Studio), GCC (MinGW), or Clang

3. **Configure CMake:**
   - Open Terminal in VSCode (Ctrl+`)
   - Run: `cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug`
   - Or use Task: `Ctrl+Shift+P` → "Tasks: Run Task" → "CMake: Configure"

### Building the Project

**Option 1: Keyboard Shortcut**
- Press `Ctrl+Shift+B` (runs default build task)

**Option 2: Task Menu**
- Press `Ctrl+Shift+P`
- Type "Tasks: Run Task"
- Select desired task (e.g., "CMake: Build (Debug)")

**Option 3: Terminal**
```bash
cmake --build build --config Debug
```

### Running and Debugging

**Start Debugging:**
- Press `F5` (starts default launch configuration)
- Or: Click Run → Start Debugging
- Or: Debug panel (Ctrl+Shift+D) → Select config → Press F5

**Run Without Debugging:**
- Press `Ctrl+F5`
- Or: Click Run → Run Without Debugging

**Set Breakpoints:**
- Click left margin in source file (red dot appears)
- Or: Press F9 on desired line

### Debugging Tips

1. **Working Directory**: All configs set `cwd` to `bin/` so asset paths (`../assets/`) work correctly

2. **Auto-Build**: Launch configs have `preLaunchTask` that builds before debugging

3. **Choose Right Debugger**:
   - **MSVC** (`cppvsdbg`): Best for Visual Studio projects, requires VS Build Tools
   - **GDB** (`cppdbg`): For MinGW/GCC toolchain
   - **LLDB**: For macOS/Linux with Clang

4. **Debugging Controls**:
   - `F5` - Continue/Start
   - `F10` - Step Over
   - `F11` - Step Into
   - `Shift+F11` - Step Out
   - `Shift+F5` - Stop Debugging

## Troubleshooting

### "CMake not found"
- Install CMake: https://cmake.org/download/
- Add CMake to PATH
- Restart VSCode

### "SDL2 not found"
- Install SDL2 development libraries
- Update CMake find module paths in `CMakeLists.txt`
- Or set `CMAKE_PREFIX_PATH` to SDL2 location

### "Cannot find ZCoreEngine.exe"
- Run build task first: `Ctrl+Shift+B`
- Check that `bin/` directory exists with executable
- Verify CMakeLists.txt sets output to `bin/`

### Debugger not starting
- **MSVC**: Install Visual Studio Build Tools or Visual Studio Community
- **GDB**: Install MinGW-w64 and ensure `gdb.exe` is in PATH
- Check task output for build errors

### Assets not loading
- Verify working directory is set to `bin/` in launch.json
- Check that assets exist in `assets/` folder
- Asset paths are relative: `../assets/...`

### IntelliSense errors but code compiles
- Reload window: `Ctrl+Shift+P` → "Developer: Reload Window"
- Update C_Cpp.default.includePath in settings.json
- Run CMake configure to generate compile_commands.json

## Customization

### Change Default Configuration
Edit `launch.json` and set `"default"` in the configuration you want to use with F5.

### Add Custom Build Arguments
Edit `tasks.json` and modify the `args` array in build tasks.

### Change Build Type
Switch between Debug/Release:
1. Use "CMake: Configure (Release)" task
2. Then "CMake: Build (Release)" task
3. Or manually: `cmake -DCMAKE_BUILD_TYPE=Release ..`

### Add Environment Variables
Edit `launch.json` and add to `"environment"` array:
```json
"environment": [
    {
        "name": "MY_VAR",
        "value": "my_value"
    }
]
```

## Project Structure

```
ZEngine2D/
├── .vscode/
│   ├── launch.json      ← Debug configurations
│   ├── tasks.json       ← Build tasks
│   ├── settings.json    ← Project settings
│   └── README.md        ← This file
├── build/               ← CMake build directory
├── bin/                 ← Output executables (working directory)
├── src/                 ← Source code
├── assets/              ← Game assets (textures, scripts, fonts)
└── CMakeLists.txt       ← CMake configuration
```

## Additional Resources

- [VSCode C++ Documentation](https://code.visualstudio.com/docs/languages/cpp)
- [CMake Documentation](https://cmake.org/documentation/)
- [SDL2 Documentation](https://wiki.libsdl.org/)
- [ZEngine2D Documentation](https://zencodergames.github.io/ZEngine2D/docs/html/index.html)
