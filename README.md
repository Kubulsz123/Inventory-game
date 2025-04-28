
# HomeShot Roulette

# Full code is on branch named Inventory-game-GooglewSdl

## Documentation
If someone need a documentation:
https://docs.google.com/document/d/19e8-MKdVwAPUYWl2Sc1m3m2bLbVxKlGYDipm1FLwUrY/edit?usp=sharing

🎯 **HomeShot Roulette** is a multiplayer, turn-based survival game where players manage inventories, interact with a randomized shotgun mechanic, and attempt to outlast others.  
Built in **C++** using **SDL3**, **SDL_image**, and **SDL_ttf** libraries.

---

## 📜 Features
- 🎮 1–4 players multiplayer support.
- 🛒 Merchant system: buy and sell items.
- 🔫 Randomized live/blank shotgun bullets.
- 🎒 Inventory management: expand, sort, filter.
- 🧠 Strategic turn-based shooting.
- 🖼️ Dynamic UI with real-time SDL3 rendering.

---

## ⚙️ Requirements

- **C++20** compatible compiler (GCC 10+, MSVC 2019+, Clang 11+)
- **SDL3** (Simple DirectMedia Layer 3.0)
- **SDL_image** (for PNG textures)
- **SDL_ttf** (for TrueType font rendering)

| Component | Minimum Requirement |
|-----------|----------------------|
| CPU       | Dual-core 2.0 GHz     |
| RAM       | 2 GB minimum          |
| GPU       | OpenGL 2.1 compatible |
| Storage   | 100 MB free space     |
| OS        | Windows 10 / Linux (Ubuntu 20+) |

---

## 🚀 How to Install

### 1. Install Dependencies

**Ubuntu/Linux:**
```bash
sudo apt update
sudo apt install libsdl3-dev libsdl3-image-dev libsdl3-ttf-dev
```

**Windows:**
- Download SDL3 Development Libraries: [https://github.com/libsdl-org/SDL](https://github.com/libsdl-org/SDL)
- Download SDL_image and SDL_ttf libraries similarly.
- Extract and configure them for your compiler (MSVC or MinGW).

### 2. Clone the Project
```bash
git clone https://github.com/Kubulsz123/Inventory-game.git
cd Inventory-game-GooglewSdl
```

### 3. Build the Game
**Linux:**
```bash
g++ -std=c++20 src/*.cpp -o Inventory-game-GooglewSdl `sdl3-config --cflags --libs` -lSDL3_image -lSDL3_ttf
```

**Windows (example MSVC command):**
```bash
cl /std:c++20 /I"path\to\SDL3\include" /I"path\to\SDL3_image\include" /I"path\to\SDL3_ttf\include" src\*.cpp /link /LIBPATH:"path\to\libs" SDL3.lib SDL3_image.lib SDL3_ttf.lib
```

---

## 🏃 How to Run and Use

1. Ensure you have the required **assets** folder next to your executable (contains images and fonts).
2. Build program and exe file to run it:
```bash
cmake --build .
```
3. Launch the game:
```bash
./bin/build/Inventory-Game.exe
```
3. In-game actions:
    - **Start**: Click 'Start' and select number of players (1–4).
    - **Input Names**: Type player names (min 4 characters).
    - **Main Game**:
        - View inventories.
        - Click the **Shotgun** button to prepare a shot.
        - Click **Shoot** to select a player to target.
    - **Victory**: Last surviving player wins!

---

## 🎮 Controls

| Action         | Control            |
|----------------|--------------------|
| Navigate Menus | Mouse Click         |
| Text Input     | Keyboard Typing     |
| Confirm Action | Mouse Click Buttons |

---

## 📂 Project Structure

```plaintext
assets/               # Game images, fonts
src/                  # C++ source code files
HomeShotRoulette      # Compiled executable
HomeShot_Roulette_SRS.docx # Full project SRS documentation
README.md             # This file
```

---

## 👥 Authors / Credits
- **Jakub Szubert** — Main Developer
- **Adam Wojcieszek** — Main renderer

---

## 📜 License

Licensed under the **MIT License** — free to use, modify, and distribute.

---
