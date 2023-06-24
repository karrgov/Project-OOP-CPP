#pragma once 
#include <iostream>
#include <cstring>
#include <fstream>
#include <string>
#include <vector>
#include <stdexcept>
#include "ISBN.hpp"
#include "Person.hpp"


class Book
{
    private:
    ISBN* isbn;
    std::string title;
    std::string author;
    Person* reader;
    static std::vector<Book *> booksRegistry;

    public:
    Book(ISBN* isbn_num, std::string title_string, std::string author_string);
    ~Book();

    ISBN* getIsbn() const;
    std::string getTitle() const;
    std::string getAuthor() const;
    Person* getReader() const;
    static Book* getBooksRegistry();

    void setReader(Person* person);
    void removeReader();

    static Book* createBook(ISBN* isbn, std::string title, std::string author);
    static void removeBook(Book* book);
    static void showAllBooks();
    static Book* findBook(ISBN* isbn);
    bool isBorrowed() const;

    
};