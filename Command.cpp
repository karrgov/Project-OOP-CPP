#include <iostream>
#include <cstring>
#include <fstream>
#include <string>
#include <vector>
#include <stdexcept>
#include "Book.hpp"
#include "Person.hpp"
#include "ISBN.hpp"
#include "Command.hpp"


    void Command::readCommand(std::string command)
    {
        std::vector<std::string> arguments = Command::removeSpaces(command);
        if (!arguments.empty())
        {
            std::string commandName = arguments[0];
            toupper(commandName);
            if (commandName == "BOOK")
            {
                if (arguments.size() == 4)
                {
                    Book::createBook(&(ISBN(arguments[1])), arguments[2], arguments[3]);
                }
                else 
                {
                    std::cout << "Command BOOK requires an ISBN, title and author!" << std::endl;
                }
            }
            else if (commandName == "PERSON")
            {
                if (arguments.size() == 3)
                {
                    Person::createPerson(arguments[1], stringToInt(arguments[2]));
                }
                else
                {
                    std::cout << "Command PERSON requires a name and an ID!" << std::endl;
                }
            }
            else if (commandName == "BORROW")
            {
                if (arguments.size() == 3)
                {
                    Person::borrowBook(stringToInt(arguments[1]), &(ISBN(arguments[2])));
                }
                else
                {
                    std::cout << "Command BORROW requires an ID and an ISBN!" << std::endl;
                }
            }
            else if (commandName == "RETURN")
            {
                if (arguments.size() == 3)
                {
                    if(Person::isInBorrowedBooks(&(ISBN(arguments[2]))))
                    {
                        Person::returnBook(stringToInt(arguments[1]), &(ISBN(arguments[2])));
                    }
                    else
                    {
                        std::cout << "The person has not borrowed this exact book!" << std::endl;
                    }
                }
                else
                {
                    std::cout << "Command RETURN requires an ID and an ISBN!" << std::endl;
                }
            }
            else if (commandName == "REMOVE")
            {
                if (arguments.size() == 2)
                {
                    if (containsChar(arguments[1], '-'))
                    {
                        if (Book::findBook(&ISBN(arguments[1])))
                        {
                            if (Book::findBook(&ISBN(arguments[1]))->isBorrowed())
                            {
                                std::cout << "Are you sure? YES or NO?" << std::endl;
                                std::string yesOrNo;
                                std::cin >> yesOrNo;
                                if (yesOrNo == "YES")
                                {
                                    Book::removeBook(Book::findBook(&ISBN(arguments[1])));
                                }
                            }
                            else
                            {
                                Book::removeBook(Book::findBook(&ISBN(arguments[1])));
                            }
                        }
                        else
                        {
                            std::cout << "There is not such book!" << std::endl;
                        }
                    }
                    else
                    {
                        if (Person::findPerson(stringToInt(arguments[1])))
                        {
                            if (Person::hasBorrowedBooks())
                            {
                                std::cout << "Are you sure? YES or NO?" << std::endl;
                                std::string yesOrNo;
                                std::cin >> yesOrNo;
                                if (yesOrNo == "YES")
                                {
                                    Person::removePerson(Person::findPerson(stringToInt(arguments[1])));
                                }
                            }
                            else 
                            {
                                Person::removePerson(Person::findPerson(stringToInt(arguments[1])));
                            }
                        }
                        else
                        {
                            std::cout << "There is not such person!" << std::endl;
                        }
                    }
                }
                else
                {
                    std::cout << "Command REMOVE requires an ID or an ISBN!" << std::endl;
                }
            }
            else if (commandName == "SAVE")
            {
                if (arguments.size() == 2)
                {
                    std::fstream file;
                    file.open(arguments[1], std::ios::out);
                    file << Person::getPeopleRegistry();
                    file << Book::getBooksRegistry();
                    file.close();
                }
                
            }
            else if (commandName == "SHOW")
            {
                if (arguments.size() == 2)
                {
                    if (arguments[1] == "PEOPLE")
                    {
                        Person::showAllPeople();
                    }
                    else if (arguments[1] == "BOOKS")
                    {
                        Book::showAllBooks();
                    }
                    else if (containsChar(arguments[1], '-'))
                    {
                        std::cout << "The title of the book is: " << Book::findBook(&(ISBN(arguments[1])))->getTitle() << std::endl;
                        std::cout << "The author of the book is: " << Book::findBook(&(ISBN(arguments[1])))->getAuthor() << std::endl;
                        if (Book::findBook(&(ISBN(arguments[1])))->isBorrowed())
                        {
                            std::cout << "The reader of the book is: " << Book::findBook(&(ISBN(arguments[1])))->getReader() << std::endl;
                        }
                        else 
                        {
                            std::cout << "The book does not have a reader at the moment!" << std::endl;
                        }
                        
                    }
                    else
                    {
                        std::cout << "The name of the person is: " << Person::findPerson(stringToInt(arguments[1]))->getName() << std::endl;
                        if (Person::findPerson(stringToInt(arguments[1]))->hasBorrowedBooks())
                        {
                            Person::showBorrowedBooks();
                        }
                        else 
                        {
                            std::cout << "The person does not have any borrowed book!" << std::endl;
                        }
                    }
                }
                else
                {
                    std::cout << "Command SHOW requires PEOPLE or BOOKS or a specific ID or a specific ISBN!";
                }
            }
            else
            {
                std::cout << "Unknown command!" << std::endl;
            }
        }
    }

    std::vector<std::string> Command::removeSpaces(std::string str)
    {
        std::vector<std::string> words;
        std::string tempWord;

        for(char c : str)
        {
            if (isspace(c))
            {
                if (!tempWord.empty())
                {
                    words.push_back(tempWord);
                    tempWord.clear();
                }
            }
            else 
            {
                tempWord.push_back(c);
            }
        }

        if (!tempWord.empty())
        {
            words.push_back(tempWord);
        }
        return words;
    }

    unsigned int Command::stringToInt(std::string str)
    {
        int i = 0;
        for(char c : str)
        {
            if (c >= '0' && c <= '9')
            {
                i = i * 10 + (c - '0');
            }
        }
        return i;
    }

    bool Command::containsChar(std::string str, char c)
    {
        for (int i = 0; i < str.size(); i++)
        {
            if (str[i] == c)
            {
                break;
                return true;
            }
            else 
            {
                return false;
            }
        }
    }