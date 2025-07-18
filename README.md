# BuzzBombers-SFML 🎮

*A modern adaptation of the iconic Buzz Bomber arcade classic, crafted in C++ with SFML. Delivering polished visuals, custom soundtracks, and immersive gameplay, this project revives the retro charm with contemporary enhancements.*

## 🛠 Features

* 🔫 **Simple Shooting:** Single bullets destroy bees, hives, and honeycombs
* 🐝 **Bee Waves:** Honey bees traverse back and forth in lines
* 🐦 **Bonus Target:** Hummingbird landing on hives or honeycombs grants extra points
* 🏆 **Menus & Scores:** Main menu, level-complete screen, and high-score table
* 🎵 **Audio & Fonts:** Includes custom music, sound effects, and fonts

## 📁 Project Layout

```plaintext
BuzzBombers-SFML/
├── assets/
│   ├── textures/      # Sprite images
│   ├── music/         # Background tracks
│   ├── sfx/           # Sound effects
│   └── fonts/         # Game fonts
├── buzz.cpp           # Core game code
└── README.md          # Project documentation
```

## ⚙️ Dependencies

* **C++17** or later
* **SFML** modules: graphics, window, audio, system

## 🚀 Build & Run (Linux)

Compile and link:

```bash
g++ -c buzz.cpp && g++ buzz.o -o sfml-app -lsfml-graphics -lsfml-window -lsfml-audio -lsfml-system
```

Run the game:

```bash
./sfml-app
```

## 🎮 Controls

* **Move Left/Right:** ← / →
* **Shoot:** Spacebar
> ⚠️ Avoid areas with flowers—they block movement.

## 👑 Game Progression

* **Single Level:** One active stage (levels 2–3 and boss planned)
* **Scoring:** Destroy bees for points; let the hummingbird eat hives/honeycombs for bonus
* **Menus:** Navigate start screen, end-of-level, and view high scores

## 📜 License

This project is for educational and personal use only. All rights to third-party assets (e.g., sound effects, music, fonts) belong to their respective owners.
