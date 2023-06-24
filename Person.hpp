#pragma once 
#include <iostream>
#include <cstring>
#include <fstream>
#include <string>
#include <vector>
#include <stdexcept>
#include "Book.hpp"


class Person
{
    private:
    std::string name;
    unsigned int id;
    static std::vector<Book *> borrowedBooks;
    static int sizeBorrowedBooks;
    static std::vector<Person *> peopleRegistry;

    public: 
    Person(std::string name_string, unsigned int id_num);
    ~Person();

    std::string getName() const;
    unsigned int getId() const;
    static Person* getPeopleRegistry();

    static bool hasBorrowedBooks();
    static void showBorrowedBooks();
    static bool isInBorrowedBooks(ISBN* isbnOfBook);
    static void emptyBorrowedBooks();

    static Person* createPerson(std::string name, unsigned int id);
    static void removePerson(Person* person);
    static void showAllPeople();
    static Person* findPerson(unsigned int id);
    static void borrowBook(unsigned int id, ISBN* isbn);
    static void returnBook(unsigned int id, ISBN* isbn);


};