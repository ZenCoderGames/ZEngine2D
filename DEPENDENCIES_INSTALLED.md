# Dependencies Installation Summary

All dependencies for ZEngine2D have been successfully installed and configured.

## Installation Date
January 9, 2026

## Installed Components

### 1. CMake 4.2.1
- **Location**: C:\Program Files\CMake\
- **Installation Method**: winget
- **Status**: ✓ Installed

### 2. vcpkg (Microsoft C++ Package Manager)
- **Location**: C:\Navin\Development\vcpkg\
- **Installation Method**: Git clone + bootstrap
- **Status**: ✓ Installed and configured

### 3. SDL2 Libraries (via vcpkg)

All SDL2 libraries installed for x64-windows:

- **SDL2 2.32.10** - Core graphics/window/input library
- **SDL2_image 2.8.8** - Image loading library (PNG, JPG, etc.)
- **SDL2_ttf 2.24.0** - TrueType font rendering
- **SDL2_mixer 2.8.1** - Multi-channel audio mixer

**Installation Location**: C:\Navin\Development\vcpkg\installed\x64-windows\

**DLL Files**: Automatically copied to `bin/Debug/` during build

### 4. Lua 5.1.5
- **Source**: LuaBinaries (MSVC-compatible pre-built)
- **Location**:
  - Headers: C:\Navin\Development\ZEngine2D\lib\lua\
  - Library: C:\Navin\Development\ZEngine2D\lib\lua\lua5.1.lib
  - DLL: C:\Navin\Development\ZEngine2D\bin\Debug\lua5.1.dll
- **Installation Method**: Manual download from LuaBinaries
- **Status**: ✓ Installed and configured
- **Note**: Using Lua 5.1.5 instead of vcpkg's Lua 5.5 for C linkage compatibility with Sol2

### 5. Additional Dependencies (via vcpkg)

These were installed automatically as dependencies:

- **zlib 1.3.1** - Compression library
- **libpng 1.6.53** - PNG image format support
- **freetype 2.13.3** - Font rendering engine
- **brotli 1.2.0** - Compression algorithm
- **bzip2 1.0.8** - Compression library
- **libogg 1.3.6** - Audio container format
- **libvorbis 1.3.7** - Vorbis audio codec
- **wavpack 5.8.1** - Audio compression

## VSCode Configuration

### Files Created/Modified

1. **`.vscode/launch.json`** - Debug configurations
   - Windows MSVC Debugger (default)
   - Windows GDB Debugger
   - Linux/Mac GDB/LLDB
   - Release configuration
   - Process attachment

2. **`.vscode/tasks.json`** - Build tasks
   - CMake Configure (Debug/Release)
   - CMake Build (default: Ctrl+Shift+B)
   - CMake Clean
   - CMake Rebuild
   - Run Game
   - Build and Run

3. **`.vscode/settings.json`** - Project settings
   - CMake toolchain file configuration
   - C++ IntelliSense settings
   - File associations

4. **`.vscode/README.md`** - Complete usage guide

### vcpkg Integration

CMake is configured to use vcpkg toolchain file:
```
-DCMAKE_TOOLCHAIN_FILE=C:/Navin/Development/vcpkg/scripts/buildsystems/vcpkg.cmake
```

## Build Configuration

### CMakeLists.txt Modifications

1. **SDL2 Libraries**: Changed to CONFIG mode for vcpkg integration
   ```cmake
   find_package(SDL2 CONFIG REQUIRED)
   find_package(SDL2_image CONFIG REQUIRED)
   find_package(SDL2_ttf CONFIG REQUIRED)
   find_package(SDL2_mixer CONFIG REQUIRED)
   ```

2. **Lua 5.1**: Configured to use local build
   ```cmake
   set(LUA_INCLUDE_DIR "${PROJECT_SOURCE_DIR}/lib/lua")
   set(LUA_LIBRARY "${PROJECT_SOURCE_DIR}/lib/lua/lua5.1.lib")
   ```

3. **Target Linking**: Updated to use vcpkg CMake targets
   ```cmake
   target_link_libraries(ZCoreEngine PRIVATE
       $<TARGET_NAME_IF_EXISTS:SDL2::SDL2main>
       $<IF:$<TARGET_EXISTS:SDL2::SDL2>,SDL2::SDL2,SDL2::SDL2-static>
       # ... other SDL2 targets
       ${LUA_LIBRARY})
   ```

4. **DLL Copying**: Added post-build command to copy DLLs automatically
   ```cmake
   add_custom_command(TARGET ZCoreEngine POST_BUILD
       COMMAND ${CMAKE_COMMAND} -E copy_if_different
       $<TARGET_RUNTIME_DLLS:ZCoreEngine>
       $<TARGET_FILE_DIR:ZCoreEngine>
       COMMAND_EXPAND_LISTS)
   ```

## Bug Fixes

### Board.h Line 70
Fixed missing return statement in `Board::Set()` function:
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

## Build Output

- **Executable**: C:\Navin\Development\ZEngine2D\bin\Debug\ZCoreEngine.exe
- **Size**: 963 KB
- **Build Status**: ✓ Successful (with warnings only)
- **Configuration**: Debug

## How to Build

### Option 1: Using VSCode
1. Open project in VSCode
2. Press `Ctrl+Shift+B` (Build)
3. Press `F5` (Debug)

### Option 2: Using Command Line
```bash
cd C:\Navin\Development\ZEngine2D
cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug -DCMAKE_TOOLCHAIN_FILE=C:/Navin/Development/vcpkg/scripts/buildsystems/vcpkg.cmake
cmake --build build --config Debug
```

### Option 3: Using VSCode Tasks
- Open Command Palette (`Ctrl+Shift+P`)
- Select "Tasks: Run Task"
- Choose "CMake: Build (Debug)"

## How to Run

### From VSCode
- Press `Ctrl+F5` (Run without debugging)
- Or Press `F5` (Run with debugging)

### From Command Line
```bash
cd C:\Navin\Development\ZEngine2D\bin\Debug
./ZCoreEngine.exe
```

## Troubleshooting

### CMake Not Found
- CMake was just installed and may not be in PATH
- Restart your terminal/VSCode
- Or use full path: `"C:\Program Files\CMake\bin\cmake.exe"`

### Missing DLLs
All DLLs should be in `bin/Debug/`. If missing, run:
```bash
cp C:/Navin/Development/vcpkg/installed/x64-windows/bin/*.dll C:/Navin/Development/ZEngine2D/bin/Debug/
```

### Assets Not Loading
- Ensure working directory is set to `bin/Debug` (already configured in launch.json)
- Asset paths are relative: `../assets/...`

## Next Steps

1. **Test the game**: Run the executable and verify Tetris game works
2. **Create Release build**: Use "CMake: Build (Release)" task
3. **Package distribution**: Copy bin/Release folder with all DLLs and assets

## Additional Notes

- vcpkg provides automatic DLL copying for dependencies
- Lua 5.1 DLL must be manually ensured in bin directory
- All warnings during build are non-critical (type conversion warnings)
- Visual Studio 2022 Community Edition is the detected compiler
