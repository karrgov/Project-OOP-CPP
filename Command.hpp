#pragma once
#include <iostream>
#include <cstring>
#include <fstream>
#include <string>
#include <vector>
#include <stdexcept>
#include "Book.hpp"
#include "Person.hpp"
#include "ISBN.hpp"


class Command
{
    private:
    std::string command;

    public:
    static void readCommand(std::string command);
    static std::vector<std::string> removeSpaces(std::string str);
    static unsigned int stringToInt(std::string str);
    static bool containsChar(std::string str, char c);
};