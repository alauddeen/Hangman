#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <ctime>
#include <cstdlib>
#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

using namespace std;

class Hangman {
private:
    int guessCount;
    bool gameOver;
    string guessedWord;
    string wordToGuess;

public:
    Hangman() : guessCount(0), gameOver(true), guessedWord(""), wordToGuess("") {}

    void displayMessage(string message, bool printTop = true, bool printBottom = true, bool clearScreen = false) {
        if (clearScreen) {
            clearConsole();
        }

        if (printTop) {
            cout << "+------------------------------------+" << endl;
            cout << "|";
        } else {
            cout << "|";
        }

        bool flag = true;
        for (int i = message.length(); i < 36; i++) {
            if (flag) {
                message = message + " ";
            } else {
                message = " " + message;
            }
            flag = !flag;
        }

        cout << message;

        if (printBottom) {
            cout << "|" << endl;
            cout << "+------------------------------------+" << endl;
        } else {
            cout << "|" << endl;
        }
    }

    void drawHangman() {
        displayMessage("HANGMAN GAME", false, true, true);
        displayMessage("Guess Count: " + to_string(guessCount), false, true);
        displayMessage("", false, false);

        // ASCII Art for Hangman
        if (guessCount >= 1) {
            displayMessage("  O", false, false);
        }

        if (guessCount == 2) {
            displayMessage(" /", false, false);
        }

        if (guessCount == 3) {
            displayMessage(" /|", false, false);
        }

        if (guessCount >= 4) {
            displayMessage(" /|\\", false, false);
        }

        if (guessCount == 5) {
            displayMessage(" /", false, false);
        }

        if (guessCount >= 6) {
            displayMessage(" / \\", false, false);
        }
    }

    void randomWord(string path = "words.txt") {
        srand(static_cast<unsigned>(time(0)));
        vector<string> words;
        ifstream file(path);

        if (file.is_open()) {
            string line;
            while (getline(file, line)) {
                words.push_back(line);
            }
            file.close();
        }

        wordToGuess = words[rand() % words.size()];
    }

    void printRemainingLetters() {
        displayMessage("REMAINING LETTERS");
        printLetters('a', 'm');
        printLetters('n', 'z');
    }

    void printLetters(char from, char to) {
        string remainingLetters;
        for (char i = from; i <= to; i++) {
            if (guessedWord.find(i) == string::npos) {
                remainingLetters += i;
                remainingLetters += " ";
            } else {
                remainingLetters += "  ";
            }
        }
        displayMessage(remainingLetters, false, false);
    }

    void printWord() {
        string displayWord;
        for (char letter : wordToGuess) {
            if (guessedWord.find(letter) == string::npos) {
                gameOver = false;
                displayWord += "_ ";
            } else {
                displayWord += letter;
                displayWord += " ";
            }
        }
        displayMessage(displayWord, false);
    }

    void countGuess(string newGuess) {
        for (char letter : newGuess) {
            if (wordToGuess.find(letter) == string::npos) {
                guessCount++;
            }
        }
    }

    void setup() {
        randomWord();
        do {
            drawHangman();
            printRemainingLetters();
            printWord();

            string userGuess;
            cout << "Enter a letter: ";
            cin >> userGuess;

            if (guessedWord.find(userGuess) == string::npos) {
                guessedWord += userGuess;
                countGuess(userGuess);
            }

            if (gameOver) {
                break;
            }

            // Add a delay or prompt to continue for better user experience.
            // sleep(1); // Sleep for 1 second (UNIX-like systems)
            // Alternatively, use this for Windows:
            // Sleep(1000);

        } while (guessCount < 6);

        drawHangman(); // Display the final state of the hangman
        if (gameOver) {
            cout << "Congratulations! You guessed the word: " << wordToGuess << endl;
        } else {
            cout << "Sorry, you ran out of turns. The correct word was: " << wordToGuess << endl;
        }
    }

private:
    void clearConsole() {
#ifdef _WIN32
        system("cls");
#else
        system("clear");
#endif
    }
};

int main() {
    Hangman hangmanGame;
    hangmanGame.setup();

    // Pause the console before closing
    cout << "Press Enter to exit...";
    cin.ignore();
    cin.get();     // Wait for the user to press Enter

    return 0;
}
