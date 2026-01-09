# ZEngine2D - Quick Start Guide

## 🚀 Run the Game NOW

### From VSCode
```
Press F5
```
That's it! The game will build and run automatically.

### From Command Line
```bash
cd C:\Navin\Development\ZEngine2D\bin\Debug
./ZCoreEngine.exe
```

## 🎮 Game Controls

| Key | Action |
|-----|--------|
| ← → | Move piece left/right |
| ↑ | Rotate counter-clockwise |
| ↓ | Rotate clockwise |
| Space | Instant drop |
| P | Pause/unpause |
| ESC | Quit game |

## 🔧 Build Commands

### Build Only
```
Ctrl+Shift+B
```

### Clean Rebuild
```
Ctrl+Shift+P → "CMake: Clean Rebuild"
```

## 🐛 Debug Commands

| Key | Action |
|-----|--------|
| F5 | Start Debugging |
| Ctrl+F5 | Run Without Debugging |
| F9 | Toggle Breakpoint |
| F10 | Step Over |
| F11 | Step Into |
| Shift+F11 | Step Out |
| Shift+F5 | Stop Debugging |

## 📁 Important Locations

| Item | Path |
|------|------|
| Executable | `bin/Debug/ZCoreEngine.exe` |
| Assets | `assets/` |
| Lua Config | `assets/scripts/Tetris.lua` |
| Source Code | `src/` |

## ✅ Verify Installation

Check these files exist:
```bash
# Executable
ls bin/Debug/ZCoreEngine.exe

# Key DLLs
ls bin/Debug/SDL2.dll
ls bin/Debug/lua5.1.dll

# Assets
ls assets/scripts/Tetris.lua
ls assets/sprites/Block.png
ls assets/fonts/charriot.ttf
```

## 🆘 Quick Troubleshooting

### Build Fails
```bash
# Try manual build
cd C:\Navin\Development\ZEngine2D
"C:/Program Files/CMake/bin/cmake.exe" --build build --config Debug
```

### Game Doesn't Start
1. Check working directory is `bin/Debug`
2. Verify all DLLs are present
3. Check console output for errors

### Black Screen
- Assets not loading
- Check paths in `assets/scripts/Tetris.lua`
- Ensure working directory is correct

## 📚 Full Documentation

- **Complete build guide**: `BUILD_AND_RUN_GUIDE.md`
- **VSCode debug setup**: `VSCODE_DEBUG_FIXED.md`
- **SDL fixes**: `SDL_FIXES_SUMMARY.md`
- **Dependencies**: `DEPENDENCIES_INSTALLED.md`
- **Engine architecture**: `Claude.MD`

## 🎯 Common Tasks

### Add a Breakpoint
1. Open a .cpp file (e.g., `src/Tetris/Tetris.cpp`)
2. Click left margin next to line number
3. Red dot appears
4. Press F5 to debug - execution pauses at breakpoint

### Watch a Variable
1. Start debugging (F5)
2. Right-click variable → "Add to Watch"
3. Or type in Watch panel

### Test a Feature
1. Make code changes
2. Press F5 (auto-builds and runs)
3. Test in game window
4. Stop with Shift+F5 or ESC

### Create New Block Type
1. Edit `assets/scripts/Tetris.lua`
2. Add new entity with color values
3. Create piece class in `src/Tetris/Pieces/`
4. Rebuild and test

## ⚡ Pro Tips

- **Fast iteration**: Use `Ctrl+F5` to run without debugging (faster startup)
- **Console output**: Debug builds show stdout/stderr in VSCode terminal
- **Hot reload**: Stop game, make changes, F5 to restart
- **Multiple configs**: Use dropdown in Debug panel to switch between MSVC/GDB debuggers

## 🏁 Success!

If you see:
- ✓ 832x704 window opens
- ✓ Gray background with Tetris grid
- ✓ Wall blocks around playfield
- ✓ Falling Tetris piece
- ✓ Score counter top-left

**Everything is working perfectly!** 🎉

Enjoy coding with ZEngine2D!
