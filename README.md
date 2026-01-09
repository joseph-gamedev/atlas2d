# GameEngine2D

2D engine + sample game (MonsterChaseGame) targeting Windows.

## Build

Prereqs:
- Windows 10/11
- Visual Studio 2022 Build Tools (MSVC)
- CMake 3.20+

Build (Debug by default):
```
build.bat
```

Build Release:
```
build.bat Release
```

The executable is generated at `build/bin/<Config>/MonsterChaseGame.exe`.
Game data is copied to `build/bin/<Config>/data`.

## Repo Layout

- `engine/` engine source and headers
  - `engine/include/Core` public engine headers
  - `engine/src/Core` engine implementation
  - `engine/src/Render/D3D11` D3D11 renderer (GLib compatibility layer)
- `games/` sample game(s)
- `assets/` game data (copied to output on build)
- `extern/` third-party dependencies (RapidJSON)
- `legacy/` legacy VS artifacts (kept for reference)
- `docs/` documentation
- `build/` CMake build output

## MonsterChaseGame

### Game Objects
* Green Cube - Player
* Grey Borders - Walls
* Red Cubes - Obstacles
* Orange Cube - Collectible
* SkyBlue Cube - Goal / Flag

### Controls
* W - Move Up
* A - Move Left
* S - Move Down
* D - Move Right
* Enter Key - Start/Restart the Game

### Gameplay
The objective is to move the Player to the Flag/Goal by avoiding the Obstacles and optionally collecting the collectibles.

### Win / Lose
* Win: Player reaches the Flag/Goal.
* Lose: Player collides with Obstacles or Level Boundaries.
