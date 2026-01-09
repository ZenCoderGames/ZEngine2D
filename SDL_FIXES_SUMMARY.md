# SDL.h Errors - Fixes Applied

## Problem Summary

When attempting to debug/run the ZEngine2D project, you encountered errors related to `#include <SDL.h>` and other SDL headers.

## Root Causes Identified

### 1. IntelliSense Configuration Missing
VSCode's C++ IntelliSense didn't know where SDL2 headers were located, causing red squiggles and "cannot find" errors in the editor, even though the code compiled successfully.

### 2. Build Configuration Issues
- CMakeLists.txt needed proper vcpkg integration
- Console output was disabled, making debugging difficult
- DLL files were not automatically copied to executable directory

### 3. Lua Linkage Issues
The vcpkg version of Lua (5.5) had C++ name mangling that was incompatible with Sol2 library, causing linker errors.

## Solutions Implemented

### Fix 1: Created c_cpp_properties.json for IntelliSense

**File**: `.vscode/c_cpp_properties.json`

```json
{
    "configurations": [
        {
            "name": "Win32",
            "includePath": [
                "${workspaceFolder}/**",
                "C:/Navin/Development/vcpkg/installed/x64-windows/include",
                "C:/Navin/Development/vcpkg/installed/x64-windows/include/SDL2",
                "${workspaceFolder}/lib/lua",
                "${workspaceFolder}/lib/glm",
                "${workspaceFolder}/lib/json"
            ],
            "compilerPath": "C:/Program Files/Microsoft Visual Studio/2022/Community/VC/Tools/MSVC/14.38.33130/bin/Hostx64/x64/cl.exe",
            "cppStandard": "c++14",
            "intelliSenseMode": "windows-msvc-x64"
        }
    ],
    "version": 4
}
```

**What this does**:
- Points IntelliSense to vcpkg's include directory
- Adds SDL2 subdirectory explicitly
- Includes local library paths (Lua, GLM, JSON)
- Configures C++14 standard
- Sets correct compiler and IntelliSense mode

**Result**: SDL.h and related headers are now recognized by VSCode, eliminating red squiggles.

### Fix 2: Updated CMakeLists.txt for vcpkg Integration

**Changes made**:

```cmake
# Use vcpkg's CONFIG mode for SDL2 packages
find_package(SDL2 CONFIG REQUIRED)
find_package(SDL2_image CONFIG REQUIRED)
find_package(SDL2_ttf CONFIG REQUIRED)
find_package(SDL2_mixer CONFIG REQUIRED)

# Use local Lua 5.1 for C linkage compatibility
set(LUA_INCLUDE_DIR "${PROJECT_SOURCE_DIR}/lib/lua")
set(LUA_LIBRARY "${PROJECT_SOURCE_DIR}/lib/lua/lua5.1.lib")
include_directories(${LUA_INCLUDE_DIR})

# Link with vcpkg CMake targets
target_link_libraries(ZCoreEngine PRIVATE
    $<TARGET_NAME_IF_EXISTS:SDL2::SDL2main>
    $<IF:$<TARGET_EXISTS:SDL2::SDL2>,SDL2::SDL2,SDL2::SDL2-static>
    $<IF:$<TARGET_EXISTS:SDL2_image::SDL2_image>,SDL2_image::SDL2_image,SDL2_image::SDL2_image-static>
    $<IF:$<TARGET_EXISTS:SDL2_ttf::SDL2_ttf>,SDL2_ttf::SDL2_ttf,SDL2_ttf::SDL2_ttf-static>
    $<IF:$<TARGET_EXISTS:SDL2_mixer::SDL2_mixer>,SDL2_mixer::SDL2_mixer,SDL2_mixer::SDL2_mixer-static>
    ${LUA_LIBRARY}
)

# Enable console output for Debug builds
if(MSVC)
    set_target_properties(ZCoreEngine PROPERTIES
        LINK_FLAGS_DEBUG "/SUBSYSTEM:CONSOLE"
        LINK_FLAGS_RELEASE "/SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup"
    )
endif()

# Automatically copy DLLs to output directory
add_custom_command(TARGET ZCoreEngine POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    $<TARGET_RUNTIME_DLLS:ZCoreEngine>
    $<TARGET_FILE_DIR:ZCoreEngine>
    COMMAND_EXPAND_LISTS
)
```

**What this does**:
- Uses vcpkg's CMake config files instead of custom Find modules
- SDL2 targets automatically add correct include directories
- Console subsystem enabled for Debug builds (see stdout/stderr)
- DLLs automatically copied after build

**Result**: Project builds successfully with proper SDL2 integration.

### Fix 3: Installed Lua 5.1 with C Linkage

**Problem**: vcpkg's Lua 5.5 used C++ linkage, causing undefined symbol errors with Sol2.

**Solution**:
- Downloaded pre-built Lua 5.1.5 from LuaBinaries (MSVC compatible)
- Placed library at `lib/lua/lua5.1.lib`
- Placed DLL at `bin/Debug/lua5.1.dll`
- Copied headers to `lib/lua/`

**Result**: Lua functions link correctly without symbol errors.

### Fix 4: Updated VSCode Tasks

**File**: `.vscode/tasks.json`

All CMake tasks now include the vcpkg toolchain file:

```json
{
    "args": [
        "-S", "${workspaceFolder}",
        "-B", "${workspaceFolder}/build",
        "-DCMAKE_BUILD_TYPE=Debug",
        "-DCMAKE_TOOLCHAIN_FILE=C:/Navin/Development/vcpkg/scripts/buildsystems/vcpkg.cmake"
    ]
}
```

**Result**: Building from VSCode (Ctrl+Shift+B) works correctly with vcpkg.

### Fix 5: Updated VSCode Settings

**File**: `.vscode/settings.json`

```json
{
    "cmake.configureArgs": [
        "-DCMAKE_TOOLCHAIN_FILE=C:/Navin/Development/vcpkg/scripts/buildsystems/vcpkg.cmake"
    ]
}
```

**Result**: CMake Tools extension uses vcpkg automatically.

### Fix 6: Code Bug Fixed

**File**: `src/Tetris/Board.h:70`

**Problem**: Function declared to return `bool` but had no return statement.

**Fix**:
```cpp
bool Set(int startRow, int startCol, std::vector<Cell*> cells) {
    for(int i=0; i<cells.size(); ++i) {
        int row = startRow + cells[i]->r;
        int col = startCol + cells[i]->c;
        m_grid[row][col]->SetBlock(cells[i]->block);
    }
    return true;  // Added this line
}
```

**Result**: Code compiles without error.

## Verification Steps

### 1. Check IntelliSense
Open `src/Engine/Core/Engine.h` in VSCode:
- `#include <SDL.h>` should not show red squiggle
- Hover over `SDL_Window` - should show type information
- Ctrl+Click on `SDL_Init` - should navigate to header

### 2. Verify Build
```bash
cd C:\Navin\Development\ZEngine2D
cmake --build build --config Debug
```

Should complete with:
- ✓ 0 errors
- ⚠ Warnings only (type conversion, safe to ignore)
- ✓ Executable: `bin/Debug/ZCoreEngine.exe`

### 3. Verify DLLs
Check that these exist in `bin/Debug/`:
- SDL2.dll
- SDL2_image.dll
- SDL2_ttf.dll
- SDL2_mixer.dll
- lua5.1.dll
- And 21 other dependency DLLs

### 4. Run from VSCode
Press `F5` in VSCode:
- Should build automatically if needed
- Should launch with debugger attached
- Console window should appear (Debug build)
- Game window should open

## Common Issues and Solutions

### Issue: "SDL.h not found" in IntelliSense

**Check**:
1. Does `.vscode/c_cpp_properties.json` exist?
2. Does the path to vcpkg include directory match your installation?
3. Is the C++ extension installed in VSCode?

**Fix**:
- Reload VSCode: Ctrl+Shift+P → "Developer: Reload Window"
- Verify path: `C:/Navin/Development/vcpkg/installed/x64-windows/include`

### Issue: Build succeeds but linker errors

**Symptom**: `unresolved external symbol __imp_luaL_openlibs`

**Check**:
- Does `lib/lua/lua5.1.lib` exist?
- Is CMakeLists.txt using `${LUA_LIBRARY}`?

**Fix**: Already fixed - using local Lua 5.1 build.

### Issue: Missing DLL at runtime

**Symptom**: "The code execution cannot proceed because SDL2.dll was not found"

**Check**:
- Are DLLs in `bin/Debug/`?

**Fix**:
```bash
cp C:/Navin/Development/vcpkg/installed/x64-windows/bin/*.dll C:/Navin/Development/ZEngine2D/bin/Debug/
```

### Issue: Assets not loading

**Symptom**: Black screen or crash on startup

**Check**:
- Is working directory set to `bin/` or `bin/Debug/`?
- Do asset files exist in `assets/` folder?

**Fix**: The `.vscode/launch.json` sets `"cwd": "${workspaceFolder}/bin"` correctly.

## Technical Details

### How vcpkg SDL2 Works

vcpkg installs SDL2 in a structured way:
```
vcpkg/installed/x64-windows/
├── include/
│   └── SDL2/          ← SDL headers here
│       ├── SDL.h
│       ├── SDL_image.h
│       └── SDL_ttf.h
├── lib/
│   ├── SDL2.lib       ← Import libraries
│   ├── SDL2_image.lib
│   └── SDL2_ttf.lib
└── bin/
    ├── SDL2.dll       ← Runtime DLLs
    ├── SDL2_image.dll
    └── SDL2_ttf.dll
```

The CMake CONFIG packages automatically:
1. Add `include/SDL2` to include path
2. Link import libraries (`.lib`)
3. Know about runtime DLLs (`.dll`)

This is why `#include <SDL.h>` works without `#include <SDL2/SDL.h>`.

### Why Separate Lua Installation

vcpkg's Lua package:
- Provides Lua 5.5 (latest)
- Uses C++ name mangling for exports
- Incompatible with Sol2 (C++ Lua wrapper)

LuaBinaries Lua 5.1:
- Provides Lua 5.1.5 (older but stable)
- Uses C linkage (no name mangling)
- Compatible with Sol2 and most C++ Lua wrappers
- Widely used in game development

## Files Modified/Created

### Created:
- `.vscode/c_cpp_properties.json` (NEW)
- `.vscode/README.md` (NEW)
- `bin/Debug/run_debug.bat` (NEW)
- `lib/lua/lua5.1.lib` (NEW)
- `lib/lua/*.h` (NEW - Lua headers)
- `bin/Debug/lua5.1.dll` (NEW)

### Modified:
- `CMakeLists.txt` (Updated for vcpkg + Lua)
- `.vscode/launch.json` (Added toolchain file)
- `.vscode/tasks.json` (Added toolchain file)
- `.vscode/settings.json` (Added CMake args)
- `src/Tetris/Board.h` (Fixed return statement)

### No changes needed:
- Source code includes (`#include <SDL.h>` is correct)
- Lua scripts
- Assets
- Game logic

## Summary

All SDL.h related errors have been resolved through:
1. ✓ Proper IntelliSense configuration
2. ✓ Correct CMake vcpkg integration
3. ✓ Compatible Lua installation
4. ✓ Automatic DLL management
5. ✓ Console output for debugging

The project now:
- **Compiles successfully** with all dependencies
- **Links correctly** with SDL2 and Lua
- **Shows IntelliSense** for all headers in VSCode
- **Runs with debugger** attached from VSCode
- **Has all DLLs** automatically copied

You can now press `F5` in VSCode to build and run the game with debugging enabled.
