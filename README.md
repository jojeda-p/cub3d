*This project has been created as part of the 42 curriculum by [julepere, jojeda-p].*

# 🎮 cub3D

## 📖 Description

cub3D is a raycasting engine built in C, inspired by the technology behind the original *Wolfenstein 3D*. The goal of the project is to understand and implement the core principles of 3D graphics rendering using only 2D primitives: casting rays from the player's point of view, computing wall intersections, and projecting a pseudo-3D view onto the screen in real time. The project is inspired by the first-person shooter *Call of Duty: Black Ops 2 Zombies*.

The project is split into two parts:

- **Mandatory part**: a map parser and validator, a raycasting engine that renders textured walls (with different textures per orientation: north, south, east, west) using a single image buffer instead of per-pixel calls for better performance, and player movement/rotation using WASD and the arrow keys.
- **Bonus part**: everything from the mandatory part plus mouse-look with crosshair, inertia-based movement physics, wall sliding on collision, minimap, sprint, animated sprites and collectibles, a sliding door system, a pause menu, a fog effect, smooth transitions between weapon animations (reload, shoot, aim and extra animations), and an end-of-game screen with collectibles progress.

Beyond the graphics themselves, the project is an exercise in strict, constraint-driven C: no global variables, no memory leaks, functions capped at 25 lines, and full compliance with the 42 Norm.

## ✨ Features

**Mandatory**
- 🗺️ Custom `.cub` map parser with full validation (walls, spawn point, textures, colors) using flood fill to guarantee the map is properly closed.
- 👁️ Raycasting engine (DDA algorithm) with per-side wall textures.
- 🕹️ Player movement (WASD) and rotation (left/right arrow keys).
- 🧹 Clean window handling and resource cleanup (no leaks, proper MinilibX hook management).

**Bonus**
- 🖱️ Mouse-look combined with realistic movement physics: acceleration/deceleration (inertia) instead of instant velocity changes.
- 🧱 Wall sliding: colliding with a wall at an angle slides the player along it instead of blocking movement outright.
- ⚡ Sprint mechanic.
- 🚪 Sliding doors, DDA-integrated into the raycasting loop (rendered consistently regardless of the player's angle relative to the door, including when moving parallel to it).
- 👾 Animated sprites with Z-buffering and camera-space transforms (billboard sprites correctly occluded by walls).
- 💊 Collectible pickup system with an on-screen collection counter.
- 🗾 Real-time, pixel-accurate scrolling minimap with wall collision on ray and correct player centering.
- 🔫 Weapon animations: reload animation (`R`), bullet flip animation (`T`), shoot animation (`mouse left click`), aim animation (`mouse right click`).
- 🏁 End-of-game screen once all collectibles have been picked up.
- 🌫️ Fog effect using per-ray perpendicular distance, with configurable distance and tint color.
- ⏸️ Pause menu (toggled with `P`, per subject constraints) with texture scaling and cursor visibility toggling.

## ⚙️ Physics & Animation details

### 🏃 Movement physics
- Physics-based movement model derived from Newton's second law (F = m·a)
  with surface friction, giving the movement a grounded, realistic feel.
- The player accelerates gradually and decelerates with inertia instead of
  instant velocity changes.
- Directional speed asymmetry: the player moves faster forward, slower sideways,
  and slowest backwards — matching realistic locomotion.
- Sprint is only possible when moving forward.
- Diagonal movement is normalized: moving forward and sideways simultaneously
  does not stack velocities (a common implementation mistake).
- Wall sliding: colliding with a wall at an angle slides the player along it
  instead of stopping movement outright.
- FOV increases smoothly when sprinting and returns gradually when stopping,
  using linear interpolation each frame.
- Picking up ammo increases the player's mass, gradually reducing acceleration.

### 🎬 Weapon animation state machine
- Animations never overlap or interrupt each other incorrectly.
- Aiming while sprinting cancels the sprint and plays the corresponding
  transition animation before entering the aim state.
- Sprinting while aiming cancels the aim and plays the corresponding
  transition animation before entering the sprint state.
- Reload and bullet flip (T) are non-interruptible: triggering one while the
  other is playing queues it as the next animation instead of cancelling.
- Both reload and bullet flip can be queued while sprinting and transition
  cleanly once the sprint animation finishes.
- Attempting to reload or flip while aiming automatically cancels the aim first,
  playing the transition animation before the queued action.
- The crosshair disappears during aim-in and aim states.
- Aiming disables sprint and sprinting disables aim for the duration.

## 🛠️ Instructions

### Requirements

- Linux
- `make`, `gcc`/`cc`
- MinilibX (X11 libraries: `libxext-dev`, `libx11-dev`)

### Compilation

```bash
git clone <repo_url> cub3D
cd cub3D
make
```

This builds the `cub3D` executable. Other available targets:

```bash
make bonus     # build the bonus version
make clean     # remove object files
make fclean    # remove object files and the executable
make re        # fclean + make
```

### ▶️ Execution

```bash
./cub3D maps/example.cub
```

The program expects a valid `.cub` map file as its only argument. Invalid maps (unclosed maps, missing textures/colors, malformed characters, etc.) are rejected with an explicit error message.

### 🎮 Controls

| Key              | Action                              |
|------------------|--------------------------------------|
| `W` `A` `S` `D`  | Move forward / left / back / right  |
| `←` `→`          | Rotate the camera (mandatory)       |
| 🖱️ Mouse         | Look around (bonus)                 |
| `Shift`          | Sprint (bonus)                      |
| `E`              | Open/close a sliding door           |
| `R`              | Reload animation (bonus)            |
| `T`              | Bullet flip (bonus)                 |
| 🖱️ Left click    | Shoot (bonus)                       |
| 🖱️ Right click   | Aim (bonus)                         |
| `P`              | Pause menu                          |
| `ESC`            | Quit                                |

## 🔬 Technical choices

- **🚪 Doors**: initially implemented as billboard sprites, which caused lateral drift and incorrect scaling depending on the viewing angle. The system was reworked to be fully integrated into the DDA raycasting loop, treating the door as a moving wall segment so its projected height and position stay consistent from any angle.
- **🏃 Movement physics**: instead of directly setting the player's velocity from input, the bonus movement model applies acceleration and friction each frame, producing a realistic inertia effect and a distinct feel when sprinting.
- **🗾 Minimap**: uses `div_floor`-based coordinate conversion to keep centering pixel-accurate regardless of the sign of the player's position.

## 📚 Resources

- [Lode's Raycasting Tutorial](https://lodev.org/cgtutor/raycasting.html) — the classic reference for DDA-based raycasting, used as the foundation for the wall-rendering algorithm.
- [MinilibX documentation (42 Paris)](https://github.com/42Paris/minilibx-linux) — reference for window/image handling and event hooks.
- [Wolfenstein 3D — Fabien Sanglard's Game Engine Black Book](https://fabiensanglard.net/gebbwolf3d/) — background reading on the original engine that inspired the project.
- [DDA algorithm (Wikipedia)](https://en.wikipedia.org/wiki/Digital_differential_analyzer_(graphics_algorithm)) — general reference for the Digital Differential Analyzer technique used in ray-wall intersection.

### 🤖 AI usage

AI was used as a learning and debugging aid throughout the project, in a step-by-step, didactic way rather than to generate ready-made code to copy-paste. Specifically, it was used for:

- Explaining raycasting concepts (DDA stepping, perpendicular distance vs. Euclidean distance, camera-space sprite transforms) before implementing them.
- Debugging the transition of the door system from a billboard-based approach to a DDA-integrated one, including diagnosing the lateral drift/height issue when the player moves parallel to a door.
- Reviewing logic for the minimap scrolling/centering math and the flood-fill map validation.
- Discussing the design of the inertia-based movement physics (acceleration/friction model) and the sprint mechanic.

All resulting code was written, understood, and tested by the project's authors.