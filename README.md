# Snake Game 🐍

A classic multiplayer snake game implementation in C++ with console-based graphics and sound effects. Supports up to 4 players simultaneously!

## Table of Contents
- [Features](#features-)
- [Project Structure](#project-structure-)
- [Build & Run](#build--run-)
- [Gameplay](#gameplay-)
- [Architecture](#architecture-)
- [License](#license-)

## Features ✨
- 🕹️ 1-4 player local multiplayer
- 🎮 Customizable controls per player
- 🔊 Sound effects for food consumption
- 📈 Growing snake mechanics
- ⚡ Collision detection (walls/other snakes)
- 📊 Score tracking system

## Project Structure 📂
| File/Folder                | Description                                  |
|----------------------------|----------------------------------------------|
| `Source.cpp`               | Main game implementation                    |
| `Source1.txt`              | Configuration/score records                 |
| `Bite sound effect.wav`    | Food consumption audio                      |
| `.vscode/`                 | VS Code workspace configurations           |
| `Snake_Game.sln`           | Visual Studio solution file                 |
| `.claudiaideconfig`        | ClaudiaIDE extension settings               |
| `.gitattributes`           | Git file handling rules                     |
| `.gitignore`               | Git exclusion rules                         |

## Build & Run 🛠️

### Visual Studio
```bash
1. Open Snake_Game.sln
2. Build Solution (Ctrl + Shift + B)
3. Run (F5)
```

### VS Code
```bash
# Install required packages (Windows)
choco install mingw

# Build
g++ -o Snake_Game Source.cpp -lwinmm

# Run
./Snake_Game.exe
```

### CMake (Recommended)
```cmake
cmake_minimum_required(VERSION 3.12)
project(Snake_Game)
add_executable(Snake_Game Source.cpp)
target_link_libraries(Snake_Game winmm)
```

## Gameplay 🎮

### Controls 🕹️
| Player | Up    | Left  | Down  | Right |
|--------|-------|-------|-------|-------|
| 1      | ↑     | ←     | ↓     | →     |
| 2      | W     | A     | S     | D     |
| 3      | I     | J     | K     | L     |
| 4      | T     | F     | G     | H     |

### Rules 📜
- Eat food (`@`) to grow and gain points
- Avoid collisions with walls and other snakes
- Longer snakes get speed boosts 🚀
- Last surviving snake wins!

## Architecture 📚

### Core Components
| Category            | Functions                     | Description                          |
|---------------------|-------------------------------|--------------------------------------|
| **Initialization**  | `init()`, `draw_boarder()`    | Game setup and visual preparation    |
| **Game Logic**      | `move_snake()`, `food_eaten()`| Movement and collision detection     |
| **Rendering**       | `display_snake()`, `erase_snake()` | Console graphics management     |
| **Audio**           | `PlaySound()`                 | Sound effect playback                |
| **State Management**| `generate_food()`, `kill_snake()` | Game state control               |

## License 📄
MIT License - See [LICENSE](LICENSE) for details  
[![License](https://img.shields.io/badge/License-MIT-blue.svg)](https://opensource.org/licenses/MIT)

---
