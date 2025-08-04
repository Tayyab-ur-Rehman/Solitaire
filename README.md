# Solitaire 🎴 (C++ with SFML)

A classic **Klondike Solitaire** game written in **Modern C++**, using **SFML** for window handling, graphics, input, and audio.  
Designed as a data structures & algorithms project at ITU, this version replaces the terminal-only implementation and brings graphical polish to your card-based logic.
<img width="1028" height="602" alt="image" src="https://github.com/user-attachments/assets/cb1cce6b-5834-4c45-bb02-4cc110e496eb" />


---

## 🧭 Overview

- Builds and runs across **Windows**, **Linux**, and **macOS** using **SFML 2.5.x or 3.x** :contentReference[oaicite:1]{index=1}.
- Fully works with decks, foundations, tableau, and Ace piles using **stack** and **queue** data structures.
- Supports mouse/touch or keyboard input (click, drag-and-drop, keyboard shortcuts).
- Includes visual assets (card sprites, background, UI buttons) and sound effects (shuffle, win) in the `assets/` directory.
- Randomized deals with optional difficulty levels — *Easy*, *Medium*, *Hard* — adapted from your game's internal rule-set (as seen in your past LinkedIn/coding post about Klondike and SFML) :contentReference[oaicite:2]{index=2}.

---

## ✅ Features

- Interactive **drag and drop** or **click-to-move** UI.
- Automatic valid move detection, move highlights & hints.
- Track game time, move count, win/lose dialog.
- Simple **undo** (Ctrl+Z) via LIFO stack of moves.
- Shuffle and restart any game at any time.

---
