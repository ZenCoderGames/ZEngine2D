# ZEngine2D - Build and Run Guide

## Issues Fixed

### 1. SDL.h Include Path Issues

**Problem**: VSCode IntelliSense showing errors for `#include <SDL.h>` even though the code compiles.

**Solution**: Created `.vscode/c_cpp_properties.json` with proper include paths pointing to vcpkg's SDL2 installation:
- `C:/Navin/Development/vcpkg/installed/x64-windows/include`
- `C:/Navin/Development/vcpkg/installed/x64-windows/include/SDL2`

This tells VSCode IntelliSense where to find the SDL headers, eliminating red squiggles in the editor.

### 2. Build Configuration

**Fixes Applied**:
- ✓ Fixed missing return statement in `Board::Set()` function (Board.h:70)
- ✓ Configured CMake to use vcpkg toolchain for SDL2 libraries
- ✓ Set up Lua 5.1 with proper C linkage compatibility
- ✓ Added console subsystem for Debug builds to enable stdout/stderr output
- ✓ Configured automatic DLL copying to output directory

### 3. CMake Configuration Updates

The CMakeLists.txt has been updated with:

```cmake
# SDL2 via vcpkg (CONFIG mode)
find_package(SDL2 CONFIG REQUIRED)
find_package(SDL2_image CONFIG REQUIRED)
find_package(SDL2_ttf CONFIG REQUIRED)
find_package(SDL2_mixer CONFIG REQUIRED)

# Lua 5.1 (local build for C linkage)
set(LUA_INCLUDE_DIR "${PROJECT_SOURCE_DIR}/lib/lua")
set(LUA_LIBRARY "${PROJECT_SOURCE_DIR}/lib/lua/lua5.1.lib")

# Console output for Debug builds
if(MSVC)
    set_target_properties(ZCoreEngine PROPERTIES
        LINK_FLAGS_DEBUG "/SUBSYSTEM:CONSOLE"
        LINK_FLAGS_RELEASE "/SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup"
    )
endif()

# Automatic DLL copying
add_custom_command(TARGET ZCoreEngine POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    $<TARGET_RUNTIME_DLLS:ZCoreEngine>
    $<TARGET_FILE_DIR:ZCoreEngine>
    COMMAND_EXPAND_LISTS
)
```

## Building the Project

### Prerequisites

All dependencies are already installed:
- CMake 4.2.1
- vcpkg (with SDL2 libraries)
- Lua 5.1.5
- Visual Studio 2022 Build Tools (MSVC compiler)

### Build Steps

#### Option 1: VSCode (Recommended)

1. Open the project in VSCode
2. Press `Ctrl+Shift+B` to build (Debug configuration)
3. Build output appears in Terminal
4. Executable created at: `bin/Debug/ZCoreEngine.exe`

#### Option 2: Command Line

```bash
# Navigate to project directory
cd C:\Navin\Development\ZEngine2D

# Configure CMake with vcpkg toolchain
cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug -DCMAKE_TOOLCHAIN_FILE=C:/Navin/Development/vcpkg/scripts/buildsystems/vcpkg.cmake

# Build
cmake --build build --config Debug

# Executable will be at: bin/Debug/ZCoreEngine.exe
```

#### Option 3: Using Make (if available)

```bash
make build
./game
```

## Running the Game

### Important: Working Directory

The game MUST be run with the working directory set to `bin/Debug/` because:
- Asset paths in Lua scripts are relative: `../assets/...`
- From `bin/Debug/`, `../assets/` correctly resolves to the project's `assets/` folder

### Method 1: VSCode Debug (F5)

The `.vscode/launch.json` is configured with correct working directory:

```json
{
    "program": "${workspaceFolder}/bin/ZCoreEngine.exe",
    "cwd": "${workspaceFolder}/bin"
}
```

**To Debug:**
1. Press `F5` (Start Debugging)
2. Or press `Ctrl+F5` (Run Without Debugging)

The debugger will:
- Build if needed (preLaunchTask)
- Set working directory to `bin/`
- Launch with MSVC debugger attached

### Method 2: Command Line

```bash
# Navigate to bin/Debug
cd C:\Navin\Development\ZEngine2D\bin\Debug

# Run
./ZCoreEngine.exe
```

### Method 3: Double-click

1. Navigate to `C:\Navin\Development\ZEngine2D\bin\Debug\`
2. Double-click `ZCoreEngine.exe`

**Note**: Double-clicking sets the working directory to `bin\Debug\` automatically, so assets will load correctly.

### Method 4: Using Batch Script

A helper script has been created at `bin/Debug/run_debug.bat`:

```bash
cd bin/Debug
./run_debug.bat
```

This will:
- Run the game
- Show exit code
- Keep console open to see any error messages

## Verifying the Build

### Check for Required Files

All these files should exist in `bin/Debug/`:

**Executable:**
- `ZCoreEngine.exe` (~963 KB)

**Required DLLs (26 total):**
- `SDL2.dll`, `SDL2d.dll`
- `SDL2_image.dll`, `SDL2_imaged.dll`
- `SDL2_ttf.dll`, `SDL2_ttfd.dll`
- `SDL2_mixer.dll`, `SDL2_mixerd.dll`
- `lua5.1.dll`
- `zlib1.dll`, `zlibd1.dll`
- `libpng16.dll`, `libpng16d.dll`
- `freetype.dll`, `freetyped.dll`
- `brotlicommon.dll`, `brotlidec.dll`, `brotlienc.dll`
- `bz2.dll`, `bz2d.dll`
- `ogg.dll`, `vorbis.dll`, `vorbisenc.dll`, `vorbisfile.dll`
- `wavpackdll.dll`

### Check for Assets

Verify these exist relative to project root:
```
assets/
├── scripts/
│   └── Tetris.lua
├── sprites/
│   ├── Block.png
│   ├── EmptyBlock.png
│   ├── WhiteBlock.png
│   └── ... (other block sprites)
├── spriteSheets/
│   ├── TetrisBlock.png
│   └── TetrisBlock.json
└── fonts/
    └── charriot.ttf
```

## Troubleshooting

### "SDL.h not found" in VSCode

**Symptom**: Red squiggles under `#include <SDL.h>` but code compiles fine.

**Solution**: The `.vscode/c_cpp_properties.json` file has been created with correct include paths. If issues persist:
1. Reload VSCode window: `Ctrl+Shift+P` → "Developer: Reload Window"
2. Verify C++ extension is installed
3. Check that `c_cpp_properties.json` exists in `.vscode/` folder

### Build Errors

**Missing CMake**:
- CMake was just installed and may not be in PATH
- Restart terminal or use full path: `"C:\Program Files\CMake\bin\cmake.exe"`

**SDL2 not found**:
- Ensure vcpkg toolchain file is specified in CMake command
- Check vcpkg installation: `C:\Navin\Development\vcpkg\`

**Lua linking errors**:
- Verify `lib/lua/lua5.1.lib` exists
- Verify `bin/Debug/lua5.1.dll` exists
- These were installed from LuaBinaries for MSVC compatibility

### Runtime Errors

**Missing DLL error**:
```bash
# Copy all vcpkg DLLs to bin/Debug
cp C:/Navin/Development/vcpkg/installed/x64-windows/bin/*.dll C:/Navin/Development/ZEngine2D/bin/Debug/
```

**Assets not loading**:
- Verify working directory is `bin/` or `bin/Debug/`
- Check asset files exist in `assets/` folder
- Lua script expects: `../assets/scripts/Tetris.lua` from working directory

**Black screen or immediate exit**:
- Check console output (Debug builds have `/SUBSYSTEM:CONSOLE`)
- Verify all required textures exist
- Ensure SDL2 initialized successfully

### Debugger Issues in VSCode

**Debugger not starting**:
1. Install "C/C++" extension by Microsoft
2. Verify Visual Studio Build Tools are installed
3. Check `launch.json` configuration is present
4. Try running without debugging first: `Ctrl+F5`

**Breakpoints not working**:
1. Ensure Debug build is being used (not Release)
2. Check that symbols are being generated
3. Rebuild with clean: `Ctrl+Shift+P` → "CMake: Clean Rebuild"

## Game Controls

Once running, use these controls to play Tetris:

- **← / →** - Move piece left/right
- **↑** - Rotate counter-clockwise
- **↓** - Rotate clockwise
- **Space** - Instant drop
- **P** - Pause/unpause
- **ESC** - Quit game

## Expected Behavior

When running correctly, you should see:
1. An 832x704 pixel window opens
2. Gray background (RGB: 21, 21, 21)
3. Tetris playfield with gray wall blocks
4. Current falling piece
5. Ghost piece (semi-transparent preview)
6. Score counter in top-left

## Build Warnings (Safe to Ignore)

The build produces many C4244 warnings about float-to-int conversions. These are:
- Non-critical type conversion warnings
- Do not affect functionality
- Can be suppressed in future by casting explicitly or adjusting compiler flags

## Additional Files Created

- `.vscode/c_cpp_properties.json` - IntelliSense configuration
- `.vscode/launch.json` - Debug configurations (updated)
- `.vscode/tasks.json` - Build tasks (updated with vcpkg toolchain)
- `.vscode/settings.json` - CMake settings
- `bin/Debug/run_debug.bat` - Helper script for running with console output
- `lib/lua/lua5.1.lib` - Lua import library
- `lib/lua/*.h` - Lua header files
- `bin/Debug/lua5.1.dll` - Lua runtime DLL

## Next Steps

1. **Test the game**: Run from VSCode with F5
2. **Verify all features**: Test piece movement, rotation, line clearing
3. **Create Release build**: Use "CMake: Build (Release)" task
4. **Package for distribution**: Copy `bin/Release/` folder with all DLLs and assets

## Success Checklist

- [x] Dependencies installed (CMake, vcpkg, SDL2, Lua)
- [x] Project builds without errors
- [x] All DLLs copied to output directory
- [x] VSCode configuration created
- [x] Console output enabled for Debug builds
- [x] Working directory configured correctly
- [x] IntelliSense errors resolved
- [ ] Game runs and displays correctly
- [ ] All Tetris mechanics work (movement, rotation, line clearing)
- [ ] Assets load without errors

## Support

If issues persist:
1. Check that all files in this guide are present
2. Verify working directory is correct
3. Ensure all DLLs are in `bin/Debug/`
4. Check console output for error messages
5. Review the DEPENDENCIES_INSTALLED.md file for detailed installation info
