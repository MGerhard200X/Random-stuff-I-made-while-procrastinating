#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <sstream>
#include <bitset>
#include <algorithm>
#include <iomanip>
#include <limits>

// Forward declarations
std::string toHex(int n);
std::string toBin(int n);
std::string convertToBase(int n, int base);
void toLower(std::string &s);
void displayGrade(int score, int totalRounds);
bool playConversionRound();
bool playSummationRound();
bool playMultiplicationDivisionRound();
int getIntegerInput();


int main() {
    srand(static_cast<unsigned int>(time(0)));
    char playAgain = 'y';

    do {
        std::cout << "--- Main Menu ---\n";
        std::cout << "Welcome to a short hex/binary/decimal conversion game made by Mael\n";
        std::cout << "Please choose a game mode:\n";
        std::cout << "  1) Number System Conversions\n";
        std::cout << "  2) Addition & Subtraction\n";
        std::cout << "  3) Multiplication & Division\n";
        std::cout << "  4) Mixed Mode (All of the above)\n";
        std::cout << "Your choice: ";
        int gameMode = getIntegerInput();

        if (gameMode < 1 || gameMode > 4) {
            std::cout << "Invalid mode selected. Please try again.\n\n";
            continue;
        }

        std::cout << "How many rounds would you like to play? ";
        int numRounds = getIntegerInput();
        if (numRounds <= 0) {
            std::cout << "Invalid number of rounds. Please start over.\n\n";
            continue;
        }
        std::cout << "\n";

        int score = 0;
        for (int i = 0; i < numRounds; ++i) {
            std::cout << "--- Round " << i + 1 << " / " << numRounds << " ---\n";
            bool roundResult = false;
            int randomMode = (rand() % 3) + 1; // For mixed mode

            switch (gameMode) {
                case 1:
                    roundResult = playConversionRound();
                    break;
                case 2:
                    roundResult = playSummationRound();
                    break;
                case 3:
                    roundResult = playMultiplicationDivisionRound();
                    break;
                case 4: // Mixed Mode
                    if (randomMode == 1) roundResult = playConversionRound();
                    else if (randomMode == 2) roundResult = playSummationRound();
                    else roundResult = playMultiplicationDivisionRound();
                    break;
            }

            if (roundResult) {
                score++;
            }
        }

        displayGrade(score, numRounds);

        std::cout << "Play again? (y/n): ";
        std::cin >> playAgain;
        std::cout << "\n";

    } while (playAgain == 'y' || playAgain == 'Y');

    std::cout << "Thanks for playing! Goodbye.\n";

    return 0;
}

// --- Game Round Functions ---

bool playConversionRound() {
    int number = rand() % 255 + 1;
    int fromBase = rand() % 3;
    int toBase;
    do {
        toBase = rand() % 3;
    } while (fromBase == toBase);

    std::vector<std::string> baseNames = {"decimal", "binary", "hexadecimal"};
    std::string questionValue = convertToBase(number, fromBase);
    std::string correctAnswer = convertToBase(number, toBase);

    std::cout << "Convert " << questionValue << " (" << baseNames[fromBase] << ") to " << baseNames[toBase] << ": ";
    std::string userAnswer;
    std::cin >> userAnswer;

    toLower(userAnswer);
    std::string lowerCorrectAnswer = correctAnswer;
    toLower(lowerCorrectAnswer);

    if (userAnswer == lowerCorrectAnswer) {
        std::cout << "Correct!\n\n";
        return true;
    } else {
        std::cout << "Wrong! The correct answer is: " << correctAnswer << "\n\n";
        return false;
    }
}

bool playSummationRound() {
    std::vector<std::string> baseNames = {"decimal", "binary", "hexadecimal"};
    int num1 = rand() % 100 + 1;
    int num2 = rand() % 100 + 1;

    int base1 = rand() % 3;
    int base2 = rand() % 3;
    int answerBase = rand() % 3;

    int operation = rand() % 2; // 0 for addition, 1 for subtraction
    int decimalResult;
    std::string opSymbol;

    if (operation == 0) { // Addition
        decimalResult = num1 + num2;
        opSymbol = "+";
    } else { // Subtraction
        if (num1 < num2) std::swap(num1, num2);
        decimalResult = num1 - num2;
        opSymbol = "-";
    }

    std::string str1 = convertToBase(num1, base1);
    std::string str2 = convertToBase(num2, base2);
    std::string correctAnswer = convertToBase(decimalResult, answerBase);

    std::cout << "Calculate: " << str1 << " (" << baseNames[base1] << ") " << opSymbol << " "
              << str2 << " (" << baseNames[base2] << ")\n";
    std::cout << "Enter the answer in " << baseNames[answerBase] << ": ";
    
    std::string userAnswer;
    std::cin >> userAnswer;
    toLower(userAnswer);
    toLower(correctAnswer);

    if (userAnswer == correctAnswer) {
        std::cout << "Correct!\n\n";
        return true;
    } else {
        std::cout << "Wrong! The correct answer is: " << correctAnswer << "\n\n";
        return false;
    }
}

bool playMultiplicationDivisionRound() {
    std::vector<std::string> baseNames = {"decimal", "binary", "hexadecimal"};
    int operation = rand() % 2;
    int num1, num2, decimalResult;
    std::string opSymbol;
    
    int base1 = rand() % 3;
    int base2 = rand() % 3;
    int answerBase = rand() % 3;

    if (operation == 0) { // Multiplication
        num1 = rand() % 20 + 2;
        num2 = rand() % 20 + 2;
        decimalResult = num1 * num2;
        opSymbol = "*";
    } else { // Division (engineered to have an integer result)
        num2 = rand() % 19 + 2; // Divisor
        int result = rand() % 20 + 2; 
        num1 = num2 * result; // Dividend
        decimalResult = result;
        opSymbol = "/";
    }

    std::string str1 = convertToBase(num1, base1);
    std::string str2 = convertToBase(num2, base2);
    std::string correctAnswer = convertToBase(decimalResult, answerBase);

    std::cout << "Calculate: " << str1 << " (" << baseNames[base1] << ") " << opSymbol << " "
              << str2 << " (" << baseNames[base2] << ")\n";
    std::cout << "Enter the answer in " << baseNames[answerBase] << ": ";
    
    std::string userAnswer;
    std::cin >> userAnswer;
    toLower(userAnswer);
    toLower(correctAnswer);

    if (userAnswer == correctAnswer) {
        std::cout << "Correct!\n\n";
        return true;
    } else {
        std::cout << "Wrong! The correct answer is: " << correctAnswer << "\n\n";
        return false;
    }
}


// --- Helper Functions ---

void displayGrade(int score, int totalRounds) {
    if (totalRounds == 0) return;
    double percentage = (static_cast<double>(score) / totalRounds) * 100.0;
    int grade;

    if (percentage >= 90) grade = 1;
    else if (percentage >= 80) grade = 2;
    else if (percentage >= 65) grade = 3;
    else if (percentage >= 50) grade = 4;
    else if (percentage >= 25) grade = 5;
    else grade = 6;

    std::cout << "\n----------------------------------------\n";
    std::cout << "Final Score: " << score << " / " << totalRounds << " (" << std::fixed << std::setprecision(1) << percentage << "%)\n";
    std::cout << "German Grade (Note): " << grade << "\n";
    std::cout << "----------------------------------------\n";
}

std::string toHex(int n) {
    std::stringstream ss;
    ss << std::hex << n;
    return ss.str();
}

std::string toBin(int n) {
    if (n > 255) return std::bitset<16>(n).to_string();
    return std::bitset<8>(n).to_string();
}

std::string convertToBase(int n, int base) {
    switch (base) {
        case 0: return std::to_string(n);
        case 1: return toBin(n);
        case 2: return toHex(n);
        default: return "";
    }
}

void toLower(std::string &s) {
    std::transform(s.begin(), s.end(), s.begin(),
                   [](unsigned char c){ return std::tolower(c); });
}

int getIntegerInput() {
    int value;
    std::cin >> value;
    while (std::cin.fail()) {
        std::cout << "Invalid input. Please enter a number: ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cin >> value;
    }
    return value;
}