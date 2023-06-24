#include <iostream>
#include <cstring>
#include <fstream>
#include <string>
#include <vector>
#include <stdexcept>
#include <fstream>
#include "Command.hpp"

int main()
{
    //std::cout << "hello world" << std::endl;
    std::string filename;

    std::ifstream file;

    std::cout << "Enter a filename: ";
    std::cin >> filename;
    if (filename == "NO")
    {
        while (true)
        {
            std::string command;
            std::cout << "Enter a command: ";
            getline(std::cin, command);
            Command::readCommand(command);
        }
    }
    else 
    {
        file.open(filename);

    if (file.fail())
    {
        std::cout << "The opening of the file failed!" << std::endl;
        return 1;
    }

    std::vector<std::string> contents;
    std::string line;

    while (!file.eof())
    {
        getline(file, line);
        contents.push_back(line);
    }
    file.close();
    }
}