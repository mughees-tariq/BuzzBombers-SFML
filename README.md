# BuzzBombers-SFML 🎮

Soar through retro mazes and blast bee swarms to defend your honey!

A modern adaptation of the iconic Buzz Bomber arcade classic, crafted in C++ with SFML. Delivering polished visuals, custom soundtracks, and immersive gameplay, this project revives the retro charm with contemporary enhancements.

## 📺 Demo Video

**Watch the gameplay video:**
▶️ [YouTube](https://youtu.be/J9RbIT6yj9U)

## 📸 Screenshots
<img width="822" height="462" alt="mainMenu" src="https://github.com/user-attachments/assets/0c6a8e8a-359c-419c-bdb2-e7e8e44892c6" />
<img width="823" height="464" alt="gameplay1" src="https://github.com/user-attachments/assets/b69d5727-620b-4d8e-a006-f5884165bb2d" />
<img width="823" height="464" alt="gameplay1" src="https://github.com/user-attachments/assets/b3217143-d7d4-41ca-bd26-60f3b4cb0a0c" />
<img width="822" height="461" alt="gameplay3" src="https://github.com/user-attachments/assets/bfab5135-4b8c-4198-9822-4e9026da70cb" />
<img width="823" height="463" alt="levelEnd" src="https://github.com/user-attachments/assets/61b3ebca-8f4d-4eca-b55c-125ee0a09270" />
<img width="824" height="466" alt="scoreRegistration" src="https://github.com/user-attachments/assets/3992af07-1930-40e8-b306-fb65af80ea98" />
<img width="824" height="467" alt="leaderboard" src="https://github.com/user-attachments/assets/4eaee26f-6e32-419b-a1bd-8b19655bddab" />

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
