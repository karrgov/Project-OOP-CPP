#pragma once 
#include <iostream>
#include <cstring>
#include <fstream>
#include <string>
#include <vector>
#include <stdexcept>


class ISBN
{
    private:
    std::string isbn;

    public:
    ISBN(std::string isbn_num);
    
    std::string getIsbn() const;

    static bool isValid(std::string &isbn);
    bool operator == (ISBN &isbn);
    
};