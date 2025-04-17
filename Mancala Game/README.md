# Mancala Game 

This project is a simplified implementation of the traditional **Mancala** game written in **C**. The game is designed to be played between a human player and a basic computer AI on a 2x7 board (6 small cups and 1 large cup per player).

## 🎮 Game Rules

- Each player has 6 small cups (indexes 0-5) and 1 large cup (index 6).
- At the start, each small cup is filled with `n` stones, as defined by the user.
- Players take turns picking a non-empty cup from their side and distribute its stones counter-clockwise.
- If the last stone lands in the player's own **large cup**, they get an **extra turn**.
- If the last stone lands in a cup with more than 1 stone, the player continues the move.
- If the last stone lands in an empty cup, the turn ends.
- The game ends when all 6 cups of either player are empty.
- The player with the most stones in their large cup wins.

## 🧠 Computer AI Strategy

- First checks for any move that ends in its own large cup (to get an extra turn).
- If none found, it chooses the cup with the highest number of stones.

## 📂 Project Files

- `MancalaGame.c` – The source code containing the full game logic.
- `README.md` – This documentation file.

## 🛠️ How to Compile

Use a C compiler like `gcc`:

```bash
gcc main.c -o mancala
```

Then run the game:

```bash
./mancala
```

## ✅ Example

```text
Enter the number of stones in each cup: 4
+---+---+---+---+---+---+---+---+
|   | 4 | 4 | 4 | 4 | 4 | 4 |   |
| 0 |---+---+---+---+---+---| 0 |
|   | 4 | 4 | 4 | 4 | 4 | 4 |   |
+---+---+---+---+---+---+---+---+
    | 0 | 1 | 2 | 3 | 4 | 5 | <- indexes
```

## 📌 Notes

- The game uses a simple rule set and does not include advanced Mancala rules like capturing.
- Designed as a console-based terminal application.

---

Enjoy playing Mancala!