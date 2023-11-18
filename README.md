# Hangman Game

This is a simple Hangman game implemented in C++. The game randomly selects a word from a file, and the player has to guess the letters in the word. The player has a limited number of incorrect guesses before the game ends.

## Compilation and Execution

To compile the program, use a C++ compiler, for example:

```bash
g++ hangman.cpp -o hangman
```

To run the compiled program:

```bash
./hangman
```

## Dependencies

- C++ Standard Library
- For Windows users, the code uses the `windows.h` library to clear the console. For UNIX-like systems, it uses the `unistd.h` library.
