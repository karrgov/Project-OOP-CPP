#include <iostream>
#include <cstring>
#include <fstream>
#include <string>
#include <vector>
#include <stdexcept>
#include "ISBN.hpp"


    ISBN::ISBN(std::string isbn_num)
    {
        isbn = isbn_num;

    }

    std::string ISBN::getIsbn() const
    {
        return isbn;
    }

    bool ISBN::operator == (ISBN &isbn)
    {
        for (int i = 0; i < isbn.getIsbn().length(); i++)
        {
            if (this->getIsbn()[i] == isbn.getIsbn()[i])
            {
                return true;
            }
            else 
            {
                return false;
            }
        }
    }
    bool ISBN::isValid(std::string& isbn)
    {
        if (isbn.length() == 8)
        {
            if (isdigit(isbn[0]) && isdigit(isbn[1]) && isdigit(isbn[2]) && isbn[3] == '-' &&
                isupper(isbn[4]) && isupper(isbn[5]) && isbn[6] == '-' &&
                (isbn[7] - '0') % 2 == 0)
            {
                return true;
            }
        }
        else if (isbn.length() == 9)
        {
            if (isdigit(isbn[0]) && isdigit(isbn[1]) && isdigit(isbn[2]) && isbn[3] == '-' &&
                isupper(isbn[4]) && isupper(isbn[5]) && isupper(isbn[6]) && isbn[7] == '-' &&
                (isbn[8] - '0') % 2 != 0)
            {
                return true;
            }
        }
        else
        {
            return false;
        }
    }
    /*
    bool ISBN::isValid(std::string &isbn)
    {
        if (isdigit(isbn[0]) && isdigit(isbn[1]) && isdigit(isbn[2]) && isbn[3] == '-' && (isbn[4] >= '65' && isbn[4] <= '90') && (isbn[5] >= '65' && isbn[5] <= '90') && isbn[6] == '-' && (isbn[7] % 2 == 0))
        {
            return true; 
        }
        else if (isdigit(isbn[0]) && isdigit(isbn[1]) && isdigit(isbn[2]) && isbn[3] == '-' && (isbn[4] >= '65' && isbn[4] <= '90') && (isbn[5] >= '65' && isbn[5] <= '90') && (isbn[6] >= '65' && isbn[6] <= '90') && isbn[7] == '-' && (isbn[8] % 2 != 0))
        {
            return true;
        }
        else 
        {
            return false;
        }
    }
    */

