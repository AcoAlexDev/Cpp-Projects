#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#ifdef _WIN32
#include <windows.h>
#endif

std::vector<std::string> parseLine(const std::string& line) {
    std::vector<std::string> fields;
    std::string field;
    bool inQuotes = false;

    for (size_t i = 0; i < line.size(); ++i) {
        char c = line[i];

        if (c == ';')
        {
            fields.push_back(field);
            field.clear();
        }
        else if (c != '\r')
        {
            field += c;
        }
    }
    fields.push_back(field);
    return fields;
}

std::vector<std::vector<std::string>> readCSV(const std::string& filename) {
    std::vector<std::vector<std::string>> rows;
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Error: could not open file '" << filename << "'\n";
        return rows;
    }

    // CLAUDE FIX
    // Skip the UTF-8 BOM (bytes EF BB BF) if the file starts with one.
    // Excel and Notepad add it when saving as "UTF-8"; it shows up as "´╗┐"
    // in a Windows console.
    char bom[3] = {0, 0, 0};
    file.read(bom, 3);
    bool hasBom = file.gcount() == 3 &&
                  static_cast<unsigned char>(bom[0]) == 0xEF &&
                  static_cast<unsigned char>(bom[1]) == 0xBB &&
                  static_cast<unsigned char>(bom[2]) == 0xBF;
    if (!hasBom) {
        file.clear();
        file.seekg(0);  // no BOM: go back to the start
    }
    // CLAUDE FIX END

    std::string line;
    while (std::getline(file, line)) {
        if (line.empty()) continue;
        rows.push_back(parseLine(line));
    }
    return rows;
}

int main(int argc, char* argv[]) {

    #ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    #endif

    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <file.csv>\n";
        argv[1] = const_cast<char*>("C:/Users/alexa/Desktop/csv reader/data.csv");
    }

    auto data = readCSV(argv[1]);

    std::cout << "Read " << data.size() << " rows\n\n";
    
    std::string language = "English";
    std::cout << "Current language is: " << language << std::endl;

    std::string input = "";
    while (true)
    {
        std::getline(std::cin, input);
        if (input.empty() || input == "e" || input == "exit")
        {
            break;
        }

        if(input.find("getlang") != std::string::npos)
        {
            std::cout << "Current language is: " << language << std::endl;
            continue;
        }

        if(input.find("setlang") != std::string::npos)
        {
            input.erase(input.begin(), input.begin() + 8);
            
            const auto lBef = language;

            for (size_t c = 0; c < data[0].size(); ++c)
            {
                if (input == data[0][c])
                {
                    language = input;
                    std::cout << "Set language to " << language << std::endl;
                    break;
                }
            }

            if (language == lBef)
            {
                std::cout << "Could not change language to: " << input << std::endl;
            }

            continue;
        }

        bool res = false;
        for (size_t r = 0; r < data.size(); ++r)
        {
            if (input == data[r][0])
            {
                for (size_t c = 0; c < data[0].size(); ++c)
                {
                    if (language == data[0][c])
                    {
                        std::cout << "Translated to: " << data[r][c] << std::endl;
                        res = true;
                        break;
                    }
                }
                break;
            }
        }
        if (!res)
        {
            std::cout << "The keyword " << input << " is not in the CSV. Try 'test'. " << std::endl;
        }
    }

    return 0;
}