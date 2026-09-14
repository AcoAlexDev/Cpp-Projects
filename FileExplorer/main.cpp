#include <iostream>
#include <filesystem>
#include <print>
#include <sstream>
#include <fstream>
#include <vector>

namespace fs = std::filesystem;

std::string pathAsString(const fs::path& p) { return p.stem().string() + p.extension().string(); }

void printDir(const fs::path& p)
{
    fs::directory_entry de {p};
    fs::directory_iterator di {de};

    for (const auto& file : di)
    {
        if (file.is_directory())
        {
            std::cout << "Folder: " << pathAsString(file.path()) << std::endl;
        }
        else
        {
            std::cout << "File: " << pathAsString(file.path()) << std::endl;
        }
    }
}

fs::path fullPath(fs::path currentPath, fs::path targetPath)
{
    if (targetPath == "..") return currentPath.parent_path();
    if (!targetPath.has_root_path()) return (currentPath / targetPath).lexically_normal();
    return targetPath;
}

std::vector<std::string> splitInput(std::string input)
{
    std::vector<std::string> v;
    std::string word;
    bool inString = false;

    for (size_t i = 0; i < input.length(); ++i)
    {
        if (input[i] == '"')
        {
            inString = !inString;
        }
        else if (input[i] == ' ' && !inString)
        {
            if (!word.empty()) v.push_back(word);
            word = "";
        }
        else
        {
            word += input[i];
        }
    }
    if (!word.empty()) v.push_back(word);

    return v;
} 

int main()
{
    std::cout << "Started program" << std::endl;
    fs::path p = "C:/Users/";
    while (true)
    {
        std::cout << "You are in: " << p << std::endl;
        std::cout << "> ";

        std::string command;
        std::getline(std::cin, command);

        std::string keyword {};
        std::string param1 {};

        std::vector<std::string> inputs = splitInput(command);

        if (inputs.size() >= 1) keyword = inputs[0];
        if (inputs.size() >= 2) param1 = inputs[1];

        for (size_t i = 2; i < inputs.size(); ++i)
        {
            std::cout << "Unused parameter: " << inputs[i] << std::endl;
        }

        if (keyword == "ls")
        {
            printDir(p);
        }
        else if (keyword == "cd")
        {
            fs::path fp = fullPath(p, param1);
            if (fs::is_directory(fp))
            {
                p = fullPath(p, param1);
            }
            else
            {
                std::cout << "Not a directory: " << fp.string() << std::endl;
            }
        }
        else if (keyword == "read")
        {
            fs::path filePath = fullPath(p, param1);
            if (fs::is_regular_file(filePath))
            {
                std::ifstream file{filePath};
                if (!file)
                {
                    printf("Error: File could not be opened.");
                    continue;
                }
                std::string line;
                while (std::getline(file, line))
                {
                    std::cout << line << std::endl;
                }
            }

        }
        else if (keyword == "q")
        {
            break;
        }
        else if (keyword == "help")
        {
            // print all possible commands
            std::cout << "All possible commands:" << std::endl;

            std::cout << "q - quit application" << std::endl;
            std::cout << "ls - list all files in directory" << std::endl;
            std::cout << "cd - change directory" << std::endl;
            std::cout << "read - show file content" << std::endl;
        }
        else
        {
            std::cout << "Unknown commands. Please use 'help' to list all commands." << std::endl;
        }

        if (!fs::exists(p)) { p = "C:/Users/"; }
    }
    return 0;
}