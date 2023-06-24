#include <iostream>
#include <cstring>
#include <fstream>
#include <string>
#include <vector>
#include <stdexcept>
#include "Person.hpp"
#include "Book.hpp"


    Person::Person(std::string name_string, unsigned int id_num)
    {
        name = name_string;
        id = id_num;
        sizeBorrowedBooks = 0;
    }

    Person::~Person()
    {
        for(Person* person : peopleRegistry)
        {
            delete person;
        }
        for(Book* book : borrowedBooks)
        {
            delete book;
        }
    }

    std::string Person::getName() const
    {
        return name;
    }

    unsigned int Person::getId() const
    {
        return id;
    }

    Person* Person::getPeopleRegistry()
    {
        for(Person* person : peopleRegistry)
        {
            return person;
        }
    }

    bool Person::hasBorrowedBooks()
    {
        if (borrowedBooks.empty())
        {
            return false;
        }
        else 
        {
            return true;
        }
    }

    void Person::showBorrowedBooks()
    {
        if (borrowedBooks.empty())
        {
            std::cout << "The person has not borrowed any books" << std::endl;
        }
        else
        {
            for(Book* book : borrowedBooks)
            {
                std::cout << book << std::endl;
            }
        }
    }

    bool Person::isInBorrowedBooks(ISBN* isbnOfBook)
    {
        std::string str = (*isbnOfBook).getIsbn();
        if(ISBN::isValid(str))
        {
            for(Book* book : borrowedBooks)
            {
                if (book->getIsbn() == isbnOfBook)
                {
                    return true;
                }
                else
                {
                    return false;
                }
            }
        }
    }

    void Person::emptyBorrowedBooks()
    {
        if (!borrowedBooks.empty())
        {
            borrowedBooks.clear();
        }
    }

    Person* Person::createPerson(std::string name, unsigned int id)
    {
        for(Person* person : peopleRegistry)
        {
            if (person->getId() == id)
            {
                std::cout << "A person with this ID already exists!" << std::endl;
                return nullptr;
            }
        }

        Person* newPerson = new Person(name, id);
        peopleRegistry.push_back(newPerson);
        return newPerson;
    }

    void Person::removePerson(Person* person)
    {
        if (person == nullptr)
        {
            std::cout << "Invalid person!" << std::endl;
            return;
        }

        for(Person* personToBeFound : peopleRegistry)
        {
            if ((*personToBeFound).getId() == (*person).getId() && (*personToBeFound).getName() == (*person).getName())
            {
                if ((*personToBeFound).hasBorrowedBooks())
                {
                    emptyBorrowedBooks();
                    peopleRegistry.erase(std::remove(peopleRegistry.begin(), peopleRegistry.end(), person), peopleRegistry.end());
                    delete person;
                    person = nullptr;
                    break;
                }
                else
                {
                    peopleRegistry.erase(std::remove(peopleRegistry.begin(), peopleRegistry.end(), person), peopleRegistry.end());
                    delete person;
                    person = nullptr;
                    break;
                }
            }   
        }
    }

    void Person::showAllPeople()
    {
        for(Person* person : peopleRegistry)
        {
            std::cout << person << std::endl;
        }
    }

    Person* Person::findPerson(unsigned int id)
    {
        for(Person* personToBeFound : peopleRegistry)
        {
            if ((*personToBeFound).getId() == id)
            {
                return personToBeFound;
            }
            else 
            {
                return nullptr;
            }
        }
    }

    void Person::borrowBook(unsigned int id, ISBN* isbn)
    {
        (*findPerson(id)).borrowedBooks.push_back(Book::findBook(isbn));
        Book::findBook(isbn)->setReader(Person::findPerson(id));
        (*findPerson(id)).sizeBorrowedBooks++;
    }

    void Person::returnBook(unsigned int id, ISBN* isbn)
    {
        std::string str = (*isbn).getIsbn();
        if(ISBN::isValid(str))
        {
            if (!(*findPerson(id)).borrowedBooks.empty())
            {
                (*findPerson(id)).sizeBorrowedBooks--;
                Book::findBook(isbn)->setReader(nullptr);

                for(Book* bookToBeFound : borrowedBooks)
                {
                    if ((*bookToBeFound).getIsbn() == (*Book::findBook(isbn)).getIsbn() && (*bookToBeFound).getTitle() == (*Book::findBook(isbn)).getTitle() && (*bookToBeFound).getAuthor() == (*Book::findBook(isbn)).getAuthor())
                    {
                        borrowedBooks.erase(std::remove(borrowedBooks.begin(), borrowedBooks.end(), Book::findBook(isbn)), borrowedBooks.end());
                        delete Book::findBook(isbn);
                        //Book::findBook(isbn) = nullptr;
                        break;
                    }
                }
            }
        }
        else
        {
            std::cout << "The ISBN of the certain book is not valid!";
        }
    }

    /*
    static void deletePerson(Person* person)
    {
        if (person == nullptr)
        {
            std::cout << "Invalid person" << std::endl;
            return;
        }

        auto iterator = std::find(peopleRegistry.begin(), peopleRegistry.end(), person);
        if (iterator != peopleRegistry.end())
        {
            delete *iterator;
            peopleRegistry.erase(iterator);
        }
    }
    */