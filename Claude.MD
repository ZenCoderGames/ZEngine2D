# ZEngine2D - 2D Game Engine with Tetris Implementation

## Project Overview

ZEngine2D is a custom 2D game engine built from scratch using SDL2, following the Entity Component System (ECS) paradigm. The project includes a complete Tetris game implementation as a demonstration of the engine's capabilities. The engine uses Lua scripting for declarative game configuration and asset management.

## Purpose

This engine was built to document the game development process for developers who want to understand how game engines work under the hood, serving as an educational resource for those familiar with high-level engines like Unity, Unreal, or GameMaker.

## Architecture

### Core Engine Structure

```
Engine (Core Loop)
  ├── Game (Base Class)
  │   └── Tetris (Implementation)
  ├── EntityManager (Entity Container)
  ├── AssetManager (Texture/Font Loading)
  ├── CameraManager (View Control)
  ├── CollisionManager (Physics)
  └── SequenceManager (Timed Action System)
```

### Entity Component System

The engine follows a pure ECS architecture:

- **Entity** (src/Engine/Core/Entity.h:20): Container with ID and layer, holds components
- **Component** (src/Engine/Core/Component.h): Pure data/behavior attached to entities
- **System**: Implicit in managers that process entities with specific components

### Game Loop

Located in Engine class (src/Engine/Core/Engine.h:24):

1. **ProcessInput()** - SDL event handling
2. **Update()** - Game logic with deltaTime
3. **Render()** - Drawing to screen

## Key Engine Components

### Available Component Types

1. **TransformComponent** - Position, scale, rotation
2. **SpriteComponent** - Texture rendering with tinting
3. **SpriteAnimationComponent** - Frame-based animation (supports Aseprite JSON format)
4. **BoxColliderComponent** - Rectangle collision detection
5. **ProjectileComponent** - Simple projectile behavior
6. **TextComponent** - Font rendering using SDL_ttf
7. **TileComponent** - Tilemap rendering

### Sequence System

A timing system for choreographed actions (src/Engine/Core/Sequence/Sequence.h:11):

- Create sequences with multiple timed callbacks
- Used in Tetris for line-clearing animations
- Example: Stagger multiple line clears with 0.25s delays

```cpp
Sequence* sequence = Engine::sequenceManager->CreateSequence(
    onComplete, totalTime
);
sequence->AddSequenceItem(callback, executeTime);
sequence->Start();
```

## Tetris Implementation

### File Structure

```
src/Tetris/
  ├── Tetris.h/cpp          - Main game class
  ├── Board.h               - Game board (20x10 grid)
  ├── Cell.h                - Individual board cell
  ├── TetrisConfig.h        - Game constants
  └── Pieces/
      ├── Piece.h           - Base piece class
      ├── IPiece.h          - Line piece
      ├── OPiece.h          - Square piece
      ├── TPiece.h          - T-shaped piece
      ├── LPiece.h          - L-shaped piece
      ├── JPiece.h          - Reverse L piece
      ├── SPiece.h          - S-shaped piece
      └── ZPiece.h          - Z-shaped piece
```

### Game Configuration

**Board Settings** (src/Tetris/TetrisConfig.h:8):
- 20 rows x 10 columns
- 32x32 pixel cells
- Starting position: row 0, col 3
- Gravity speed: 0.5 seconds per drop

### Core Mechanics

**Piece Movement** (src/Tetris/Pieces/Piece.h:106):
- Left/Right movement with collision detection
- Rotation (CW/CCW) with wall kick system
- Automatic gravity-based descent
- Instant drop functionality
- Ghost piece preview (semi-transparent shadow)

**Line Clearing** (src/Tetris/Board.h:104):
1. Detect full rows
2. Pause game
3. Play destruction animation using Sequences
4. Recursively move pieces down
5. Resume game

**Collision System** (src/Tetris/Board.h:49):
- CheckOverflow validates piece placement
- Tests against board boundaries and existing blocks

### Controls

- **Left Arrow** - Move piece left
- **Right Arrow** - Move piece right
- **Up Arrow** - Rotate counter-clockwise
- **Down Arrow** - Rotate clockwise
- **Space** - Instant drop
- **P** - Pause/unpause
- **ESC** - Quit game

## Dependencies Required to Run Main.cpp

### System Libraries

1. **SDL2** - Core graphics, window, input handling
2. **SDL2_image** - Image loading (PNG support)
3. **SDL2_ttf** - TrueType font rendering
4. **SDL2_mixer** - Audio (linked but not actively used in Tetris)
5. **Lua 5.1** - Scripting engine

### C++ Requirements

- C++14 or higher
- Standard library support

### Third-Party Libraries (Included)

Located in `lib/` directory:
- **GLM** - OpenGL Mathematics library (header-only)
- **Sol2** - C++ Lua binding library (lib/lua/sol.hpp)
- **JSON for Modern C++** - JSON parsing (lib/json/)
- **Lua** - Source files included (lib/lua/)

## Building the Project

### Option 1: Using Makefile (Linux/Mac)

```bash
# From project root
make build

# Run the game
make run

# Clean build
make clean
```

The Makefile (line 1) compiles:
- All .cpp files in src/
- All .cpp files in src/Engine/Core/
- Links against SDL2, SDL2_image, SDL2_ttf, SDL2_mixer, Lua
- Outputs executable as `./game`

### Option 2: Using CMake (Cross-platform)

```bash
# Create build directory
mkdir build
cd build

# Generate build files
cmake ..

# Compile
cmake --build .

# Run (executable in bin/ directory)
../bin/ZCoreEngine
```

CMakeLists.txt configuration (line 1):
- Requires CMake 3.14+
- Uses custom Find modules in cmake/ folder
- Recursively includes all src/ files
- Outputs to bin/ directory
- Executable name: ZCoreEngine

### Platform-Specific Notes

**Linux/Mac:**
- Install dependencies via package manager
  ```bash
  # Ubuntu/Debian
  sudo apt-get install libsdl2-dev libsdl2-image-dev libsdl2-ttf-dev libsdl2-mixer-dev liblua5.1-dev

  # macOS (Homebrew)
  brew install sdl2 sdl2_image sdl2_ttf sdl2_mixer lua@5.1
  ```

**Windows:**
- Download SDL2 development libraries from libsdl.org
- Download Lua 5.1 binaries
- Set up include paths and library paths in your IDE or CMake
- May need to copy .dll files to executable directory

### Option 3: Using Visual Studio Code

The project includes complete VSCode configuration files in `.vscode/`:

**Configuration Files:**
- `launch.json` - Debug configurations for running and debugging
- `tasks.json` - Build tasks using CMake
- `settings.json` - C++ and CMake settings

**Available Launch Configurations:**
1. **(Windows) Launch with MSVC Debugger** - Uses Visual Studio debugger (recommended for Windows)
2. **(Windows) Launch with GDB** - Uses GDB debugger (MinGW)
3. **(Linux/Mac) Launch with GDB/LLDB** - Cross-platform debugging
4. **(Windows) Launch Release** - Run optimized release build
5. **(Windows) Attach to Process** - Attach debugger to running process

**Available Build Tasks:**
- **CMake: Configure** - Generate build files (Debug)
- **CMake: Configure (Release)** - Generate build files (Release)
- **CMake: Build (Debug)** - Build debug version (Ctrl+Shift+B default)
- **CMake: Build (Release)** - Build release version
- **CMake: Clean** - Remove build artifacts
- **CMake: Rebuild** - Clean and rebuild
- **Run Game** - Execute the game directly
- **Build and Run** - Build then run in one step

**Quick Start in VSCode:**
1. Open the project folder in VSCode
2. Press `Ctrl+Shift+B` to build (runs CMake: Build (Debug))
3. Press `F5` to debug (uses "(Windows) Launch with MSVC Debugger")
4. Breakpoints work in all source files

**Important Notes:**
- Working directory is set to `bin/` so asset paths work correctly
- Pre-launch tasks automatically build before debugging
- CMake Tools extension recommended but not required
- For MSVC debugger, ensure Visual Studio Build Tools are installed
- For GDB debugger, ensure MinGW-w64 or similar is installed

## Asset Requirements

The game requires specific assets loaded via Lua script (assets/scripts/Tetris.lua:1):

### Textures
- Block.png - Wall pieces
- EmptyBlock.png - Grid background
- WhiteBlock.png - Base block texture (tinted for colors)
- TetrisBlock.png - Break animation sprite sheet

### Sprite Sheets
- TetrisBlock.json - Aseprite format animation data

### Fonts
- charriot.ttf - Score display font

All assets are referenced with relative paths from the executable location:
```
../assets/sprites/
../assets/spriteSheets/
../assets/fonts/
```

### Lua Configuration

The Tetris.lua file (assets/scripts/Tetris.lua:1) defines:
1. **Asset Loading** - Textures and fonts with IDs
2. **Entity Prefabs** - Template entities with components
3. **Component Parameters** - Position, scale, colors, etc.

## Running Main.cpp

### Execution Flow

Main.cpp (src/Main.cpp:6) is minimal:

```cpp
int main(int argc, char *args[]) {
    auto *game = new Tetris();
    game->Start();
    return 0;
}
```

### Startup Sequence

1. **Tetris constructor** - Inherits from Game
2. **game->Start()** - Creates Engine instance (src/Engine/Core/Game.cpp:9)
3. **Engine::Initialize()** - Sets up SDL, window (832x704), renderer
4. **Tetris::Initialize()** - Loads Lua config, creates board (src/Tetris/Tetris.cpp:11)
   - Loads assets/scripts/Tetris.lua
   - Creates wall entities around playfield
   - Initializes 20x10 board grid
   - Spawns first random piece
   - Creates score display
5. **Game Loop** - Runs until quit (src/Engine/Core/Game.cpp:13)
   - ProcessInput from user
   - Update game state with deltaTime
   - Render all entities by layer
6. **Engine::Destroy()** - Cleanup SDL resources

### Expected Window

- **Resolution**: 832x704 pixels
- **Title**: "ZCoreEngine" (default)
- **Visible Elements**:
  - Gray background
  - Tetris playfield (10x20 grid) centered
  - Wall blocks surrounding playfield
  - Active piece with ghost preview
  - Score counter (top-left)

## Code Organization Best Practices

### Static Manager Pattern

All managers are static members of Engine class (src/Engine/Core/Engine.h:33):

```cpp
Engine::entityManager
Engine::renderer
Engine::assetManager
Engine::cameraManager
Engine::collisionManager
Engine::sequenceManager
```

This allows global access but maintains single ownership.

### Lua-Driven Configuration

Game data is separated from code:
- No hardcoded asset paths in C++
- Entity composition defined in Lua
- Easy to modify game content without recompiling

### Component-Based Behavior

Entities are built by composition:
```lua
entity = {
    components = {
        transform = { position, scale },
        sprite = { texture, dimensions },
        spriteAnimation = { spriteSheet, speed }
    }
}
```

## Extending the Engine

### Creating a New Game

1. Inherit from Game class (src/Engine/Core/Game.h:14)
2. Override Initialize() to set up your game
3. Override ProcessInput() for custom controls
4. Override Update() for game logic
5. Create Lua config file for assets/entities
6. Modify Main.cpp to instantiate your game

### Adding New Components

1. Create header in src/Engine/Components/
2. Inherit from Component base class
3. Implement Initialize(), Update(), Render()
4. Register in ComponentManager for Lua loading

## Documentation

Full Doxygen documentation available at:
https://zencodergames.github.io/ZEngine2D/docs/html/index.html

## Project Statistics

- **Engine Files**: 15+ core systems
- **Tetris Implementation**: 8 piece types, full game logic
- **Components**: 7 built-in component types
- **Architecture**: Pure ECS with manager pattern
- **Scripting**: Lua 5.1 with Sol2 bindings
- **Rendering**: SDL2 with layer-based rendering

## Known Limitations

1. No built-in audio playback in Tetris (SDL_mixer linked but unused)
2. Fixed window size (no dynamic resizing)
3. Single-threaded architecture
4. No built-in physics engine (basic box collisions only)
5. Asset paths are relative (must run from correct directory)

## License & Credits

Educational project by ZencoderGames for learning game engine development.
