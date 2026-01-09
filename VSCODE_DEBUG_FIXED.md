# VSCode Debug Issues - FIXED

## Problem

When attempting to debug in VSCode (pressing F5), you encountered:
```
The preLaunchTask "CMake: Build (Debug)" terminated with exit code 1
```

## Root Causes

### 1. CMake Not in PATH
The tasks.json used `"command": "cmake"` which relies on CMake being in the system PATH. Since CMake was just installed, it wasn't available in VSCode's environment.

### 2. Incorrect Executable Paths
The launch.json was configured to look for the executable at:
```
${workspaceFolder}/bin/ZCoreEngine.exe
```

But CMake with Visual Studio generator creates configuration-specific subdirectories:
```
${workspaceFolder}/bin/Debug/ZCoreEngine.exe  (for Debug builds)
${workspaceFolder}/bin/Release/ZCoreEngine.exe  (for Release builds)
```

### 3. Incorrect Working Directory
The working directory was set to `${workspaceFolder}/bin` but needs to be `${workspaceFolder}/bin/Debug` so that relative asset paths (`../assets/...`) resolve correctly.

## Fixes Applied

### Fix 1: Use Full Path to CMake

**File**: `.vscode/tasks.json`

Changed all occurrences of:
```json
"command": "cmake"
```

To:
```json
"command": "C:/Program Files/CMake/bin/cmake.exe"
```

This ensures CMake is found regardless of PATH configuration.

### Fix 2: Update Executable Paths in launch.json

**File**: `.vscode/launch.json`

#### Debug Configurations
Changed from:
```json
"program": "${workspaceFolder}/bin/ZCoreEngine.exe",
"cwd": "${workspaceFolder}/bin"
```

To:
```json
"program": "${workspaceFolder}/bin/Debug/ZCoreEngine.exe",
"cwd": "${workspaceFolder}/bin/Debug"
```

This was updated for:
- `(Windows) Launch with MSVC Debugger` (default debug config)
- `(Windows) Launch with GDB`

#### Release Configuration
Changed from:
```json
"program": "${workspaceFolder}/bin/ZCoreEngine.exe",
"cwd": "${workspaceFolder}/bin"
```

To:
```json
"program": "${workspaceFolder}/bin/Release/ZCoreEngine.exe",
"cwd": "${workspaceFolder}/bin/Release"
```

### Fix 3: Update Run Task

**File**: `.vscode/tasks.json`

Updated the "Run Game" task:
```json
{
    "label": "Run Game",
    "type": "shell",
    "command": "${workspaceFolder}/bin/Debug/ZCoreEngine.exe",
    "windows": {
        "command": "${workspaceFolder}/bin/Debug/ZCoreEngine.exe"
    },
    "options": {
        "cwd": "${workspaceFolder}/bin/Debug"
    }
}
```

## How to Debug Now

### Method 1: Press F5 (Recommended)

1. Open VSCode in the project folder
2. Press `F5` (or click Run → Start Debugging)
3. The following happens automatically:
   - Pre-launch task runs: `CMake: Build (Debug)`
   - CMake configures the project (if needed)
   - Project builds with MSVC
   - Debugger attaches to `bin/Debug/ZCoreEngine.exe`
   - Game window opens
4. Set breakpoints by clicking left margin of source files
5. Use debug controls:
   - `F5` - Continue
   - `F10` - Step Over
   - `F11` - Step Into
   - `Shift+F11` - Step Out
   - `Shift+F5` - Stop Debugging

### Method 2: Run Without Debugging

1. Press `Ctrl+F5` (or Run → Run Without Debugging)
2. Game runs without debugger attached
3. Faster startup, but no breakpoints

### Method 3: Using Debug Panel

1. Click Debug icon in left sidebar (or `Ctrl+Shift+D`)
2. Select configuration from dropdown: "(Windows) Launch with MSVC Debugger"
3. Click green play button or press `F5`

### Method 4: Using Tasks

Build only (no debug):
1. Press `Ctrl+Shift+B` - Runs default build task
2. Or: `Ctrl+Shift+P` → "Tasks: Run Task" → "CMake: Build (Debug)"

Run after building:
1. `Ctrl+Shift+P` → "Tasks: Run Task" → "Run Game"
2. Or: `Ctrl+Shift+P` → "Tasks: Run Task" → "Build and Run"

## Verifying the Fix

### Test the Build Task
```bash
# In VSCode Terminal (Ctrl+`)
cd C:\Navin\Development\ZEngine2D
"C:/Program Files/CMake/bin/cmake.exe" --build build --config Debug
```

Should output:
```
MSBuild version 17.11.9+...
...
ZCoreEngine.vcxproj -> C:\Navin\Development\ZEngine2D\bin\Debug\ZCoreEngine.exe
```

### Check Files Exist
All these should exist:
- ✓ `C:\Navin\Development\ZEngine2D\bin\Debug\ZCoreEngine.exe` (~963 KB)
- ✓ `C:\Navin\Development\ZEngine2D\bin\Debug\SDL2.dll` and 25+ other DLLs
- ✓ `C:\Navin\Development\ZEngine2D\assets\scripts\Tetris.lua`

### Test Manual Run
```bash
cd C:\Navin\Development\ZEngine2D\bin\Debug
./ZCoreEngine.exe
```

Game window should open showing Tetris playfield.

## Debug Configuration Details

### Available Launch Configurations

1. **(Windows) Launch with MSVC Debugger** - DEFAULT
   - Uses Visual Studio debugger (`cppvsdbg`)
   - Best integration with MSVC-compiled code
   - Shows detailed error messages
   - Recommended for Windows development

2. **(Windows) Launch with GDB**
   - Uses GDB debugger (`cppdbg`)
   - Requires MinGW-w64 or similar
   - Alternative if MSVC debugger has issues

3. **(Linux/Mac) Launch with GDB/LLDB**
   - For cross-platform development
   - Not applicable for Windows builds

4. **(Windows) Launch Release**
   - Runs optimized Release build
   - No debug symbols
   - Better performance for testing

5. **(Windows) Attach to Process**
   - Attach debugger to already-running process
   - Useful for debugging crashes or hangs

### Pre-Launch Tasks

All debug configurations use `"preLaunchTask": "CMake: Build (Debug)"` which:
1. Runs `CMake: Configure` (dependency)
   - Generates build files
   - Configures vcpkg toolchain
2. Runs `CMake: Build (Debug)`
   - Compiles source code
   - Links libraries
   - Copies DLLs

This ensures you're always debugging the latest code.

## Console Output

Debug builds are configured with `/SUBSYSTEM:CONSOLE`, so:
- `std::cout` and `std::cerr` output appears in VSCode Terminal
- SDL initialization messages visible
- Lua script errors shown
- Useful for debugging

Set in CMakeLists.txt:
```cmake
if(MSVC)
    set_target_properties(ZCoreEngine PROPERTIES
        LINK_FLAGS_DEBUG "/SUBSYSTEM:CONSOLE"
        LINK_FLAGS_RELEASE "/SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup"
    )
endif()
```

## Debugging Tips

### Setting Breakpoints

1. **Line Breakpoint**: Click left margin or press `F9`
2. **Conditional Breakpoint**: Right-click breakpoint → Edit Breakpoint
   - Example: `score > 100`
3. **Logpoint**: Like breakpoint but logs message instead of stopping
   - Right-click → Add Logpoint

### Watching Variables

1. **Variables Panel**: Shows local variables automatically
2. **Watch Panel**: Add expressions to monitor
   - Example: `m_currentPiece->GetRow()`
3. **Hover**: Hover over variable in code to see value

### Call Stack

- View in Debug sidebar
- Click stack frame to jump to that code location
- See function call hierarchy

### Debug Console

- Type expressions to evaluate
- Example: `m_board->GetRows()`
- Call functions: `m_currentPiece->MoveDown()`

## Troubleshooting

### Still Getting "preLaunchTask terminated with exit code 1"

**Check Terminal Output**:
1. When error occurs, check Terminal panel in VSCode
2. Look for specific error messages
3. Common issues:
   - Syntax errors in C++ code
   - Missing header files
   - Linker errors

**Try Manual Build**:
```bash
cd C:\Navin\Development\ZEngine2D
"C:/Program Files/CMake/bin/cmake.exe" -S . -B build -DCMAKE_BUILD_TYPE=Debug -DCMAKE_TOOLCHAIN_FILE=C:/Navin/Development/vcpkg/scripts/buildsystems/vcpkg.cmake
"C:/Program Files/CMake/bin/cmake.exe" --build build --config Debug
```

This shows full error messages.

### Debugger Won't Start

**Check C++ Extension**:
- Ensure "C/C++" extension by Microsoft is installed
- Reload VSCode: `Ctrl+Shift+P` → "Developer: Reload Window"

**Check Executable Exists**:
```bash
ls "C:\Navin\Development\ZEngine2D\bin\Debug\ZCoreEngine.exe"
```

**Try Different Configuration**:
- Use `(Windows) Launch with MSVC Debugger` (default)
- If that fails, try `(Windows) Launch with GDB`

### Breakpoints Not Working

**Verify Debug Build**:
- Make sure using Debug configuration (not Release)
- Release builds may optimize away code

**Rebuild**:
```bash
Ctrl+Shift+P → "CMake: Clean Rebuild"
```

**Check Breakpoint Icon**:
- Filled red circle = Active
- Hollow circle = Not bound (symbol not found)
- Gray circle = Disabled

### Assets Not Loading (Black Screen)

**Check Working Directory**:
- Must be `bin/Debug` for asset paths to work
- Lua script uses: `../assets/scripts/Tetris.lua`
- From `bin/Debug`, this resolves correctly

**Verify Assets Exist**:
```bash
ls C:\Navin\Development\ZEngine2D\assets\scripts\Tetris.lua
ls C:\Navin\Development\ZEngine2D\assets\sprites\
ls C:\Navin\Development\ZEngine2D\assets\fonts\
```

### Game Crashes Immediately

**Check Console Output**:
- Look for SDL initialization errors
- Check for missing DLLs
- Verify Lua script syntax

**Run from Command Line First**:
```bash
cd C:\Navin\Development\ZEngine2D\bin\Debug
./ZCoreEngine.exe
```

Better error messages than debugger sometimes.

## Additional Notes

### Why bin/Debug and bin/Release?

Visual Studio's CMake generator (multi-config) creates separate directories for each build configuration:
```
bin/
├── Debug/
│   ├── ZCoreEngine.exe (with debug symbols)
│   └── *.dll
└── Release/
    ├── ZCoreEngine.exe (optimized)
    └── *.dll
```

Single-config generators (Makefile, Ninja) would create:
```
bin/
├── ZCoreEngine.exe
└── *.dll
```

Our setup uses Visual Studio generator, hence the subdirectories.

### CMake Toolchain File

All tasks include:
```
-DCMAKE_TOOLCHAIN_FILE=C:/Navin/Development/vcpkg/scripts/buildsystems/vcpkg.cmake
```

This tells CMake where to find SDL2 and other libraries installed by vcpkg.

### Alternative: Add CMake to PATH

Instead of full path, you could add CMake to system PATH:
1. Open "Environment Variables"
2. Add to Path: `C:\Program Files\CMake\bin`
3. Restart VSCode
4. Change tasks.json back to `"command": "cmake"`

But using full path is more reliable.

## Summary of Changes

| File | Change | Reason |
|------|--------|--------|
| `.vscode/tasks.json` | Use full CMake path | CMake not in PATH |
| `.vscode/tasks.json` | Update "Run Game" paths | Point to Debug subdirectory |
| `.vscode/launch.json` | Update program paths | Point to Debug/Release subdirectories |
| `.vscode/launch.json` | Update cwd paths | Match executable location |

## Success Checklist

- [x] CMake configured with full path
- [x] Executable paths point to Debug/Release subdirectories
- [x] Working directories match executable locations
- [x] Build task completes successfully
- [x] Executable runs from command line
- [x] All DLLs present in bin/Debug/
- [x] Assets accessible from working directory

## Next Steps

1. **Test F5 Debugging**: Press F5 and verify debugger attaches
2. **Set Breakpoint**: Try breakpoint in `Tetris::Initialize()` (Tetris.cpp:11)
3. **Step Through Code**: Use F10 to step through initialization
4. **Watch Variables**: Add `m_board` to Watch panel
5. **Test Game Features**: Verify all Tetris mechanics work

The debug environment is now fully configured and ready to use!
