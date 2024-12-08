# Sudoku in C  

An interactive **Sudoku Game** written in C from my programming basics final project that generates playable Sudoku puzzles and allows players to solve them with helpful features like input validation, hints, and a timer. This project demonstrates fundamental concepts in C programming such as recursion, 2D arrays, and logical problem-solving while delivering an engaging user experience.  

---

## 🎮 Features  
- **Puzzle Generation**: Automatically generates valid Sudoku puzzles for three difficulty levels:  
  - `1` = Easy  
  - `2` = Medium  
  - `3` = Hard  
- **Interactive Gameplay**:  
  - Input numbers for rows, columns, and values.  
  - Receive instant feedback if your move is valid.  
- **Hint System**: Get suggestions for the next move.  
- **Reset Option**: Return to the original puzzle state.  
- **Time Tracking**: Displays the time you took to solve the puzzle.  
- **Winning Detection**: Alerts you when the puzzle is successfully solved.  

---

## 🛠️ How to Set Up and Run  

### 1. Clone the Repository  
```bash
git clone https://github.com/AriRangga/sudoku-in-c.git  
cd sudoku-in-c  
```  

### 2. Compile the Program  
Use a C compiler such as GCC:  
```bash  
gcc -o sudoku sudoku.c  
```  

### 3. Run the Program  
Execute the compiled file:  
```bash  
./sudoku  
```  

---

## 📖 How to Play  
1. **Start the Game**  
   - Choose a difficulty level:  
     - `1` for Easy  
     - `2` for Medium  
     - `3` for Hard  
2. **Understand the Board**  
   - The board is displayed with numbers and empty cells represented as `.`.  
   - Original numbers are fixed, and new numbers can be added.  

3. **Input Your Move**  
   - Enter your move in this format:  
     ```
     <row> <column> <number>
     ```  
     Example:  
     ```
     3 4 7
     ```  
     - `row`: Row number (1–9).  
     - `column`: Column number (1–9).  
     - `number`: Value to place (1–9).  

4. **Use Special Commands**  
   - `hint`: Get a suggestion for an empty cell.  
   - `reset`: Reset the puzzle to its starting state.  
   - `keluar`: Exit the game.  

5. **Win the Game**  
   - Fill all cells correctly to complete the puzzle.  
   - The program validates your solution and displays your total time.  

---

## 📂 File Structure  
- **sudoku.c**: The main source code for the program.  

---

## 💡 Example Output  

```
    1 2 3 | 4 5 6 | 7 8 9  
  +-------+-------+-------  
1 | 5 3 . | . 7 . | . . .   
2 | 6 . . | 1 9 5 | . . .   
3 | . 9 8 | . . . | . 6 .   
--+-------+-------+-------  
4 | 8 . . | . 6 . | . . 3   
5 | 4 . . | 8 . 3 | . . 1   
6 | 7 . . | . 2 . | . . 6   
--+-------+-------+-------  
7 | . 6 . | . . . | 2 8 .   
8 | . . . | 4 1 9 | . . 5   
9 | . . . | . 8 . | . 7 9   
```

---

## 🌟 Key Highlights  
- **Recursive Algorithms**: Used for solving Sudoku puzzles efficiently.  
- **Input Validation**: Ensures moves adhere to Sudoku rules.  
- **Dynamic Puzzle Generation**: Guarantees unique puzzles with single solutions.  

---

## 🚀 Future Enhancements  
- Add support for saving and loading game progress.  
- Implement a graphical user interface (GUI) for a better experience.  
- Introduce advanced difficulty levels with minimal clues.  

---

## 📜 License  
This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.  

---

## 🙌 Acknowledgments  
Inspired by the love for logic-based puzzles and the challenge of implementing Sudoku in C :D 

---

## 🤝 Contributing  
Contributions are welcome! Feel free to:  
- Fork the repository.  
- Submit pull requests with improvements or new features.  
- Open issues for bugs or suggestions. 
