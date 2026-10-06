#include <iostream>
#include <string>
#include <vector>
#include <bits/stdc++.h>
#include <random>

using namespace std;

std::vector<string> wordBank {"Fisherman", "Gingerbread", "Cloud", "What's up", "Computer", "Software", "Hardware", "Device", "Two words", "Solution", "Backspace"};

void printWord(string w, int livesLeft)
{
    std::cout << "The word progress is: ";

    for (auto& c : w)
    {
        std::cout << c << " ";
    }

    std::cout << std::endl;

    std::cout << "You have " << livesLeft << " lives left" << std::endl;
}

int main()
{
    std::random_device device;
    std::mt19937 gen(device());
    std::uniform_int_distribution<> dist(0, wordBank.size() - 1);

    string solution = wordBank[dist(gen)];
    transform(solution.begin(), solution.end(), solution.begin(), ::tolower);
    string progress = "";
    for (auto& l : solution)
    {
        if (l == ' ')
        {
            progress += " ";
        }
        else
        {
            progress += "_";
        }
    }
    
    std::string input;
    std::vector<string> guessedLetters;
    int livesLeft = 8;

    while (true) {
        printWord(progress, livesLeft);
        std::cout << "Guess a letter > ";
        std::getline(std::cin, input);

        if (input == "exit") break;

        if (input.size() != 1)
        {
            std::cout << "GUESS ONE LETTER ONLY" << std::endl;
            continue;
        }

        transform(input.begin(), input.end(), input.begin(), ::tolower);

        if (std::find(guessedLetters.begin(), guessedLetters.end(), input) != guessedLetters.end())
        {
            std::cout << "You've already tried the letter " << input << std::endl;
            continue;
        }

        if(input[0] == ' ') continue;

        guessedLetters.push_back(input);

        bool letterCorrect = false;
        for (size_t i = 0; i <= solution.size(); ++i)
        {
            if(solution[i] == input[0])
            {
                progress[i] = input[0];
                letterCorrect = true;
            }
        }

        if (!letterCorrect)
        {
            livesLeft -= 1;

            if (livesLeft == 0)
            {
                std::cout << "YOU LOST" << std::endl;
                std::cout << "The word is: " << solution << std::endl;
                break;
            }
        }

        if (progress == solution)
        {
            std::cout << "YOU WIN" << std::endl;
            std::cout << "The word is: " << solution << std::endl;
            break;
        }
        
    }

    return 0;
}