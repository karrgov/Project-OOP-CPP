#include <iostream>
#include <cstring>
#include <fstream>
#include <string>
#include <vector>
#include <stdexcept>
#include "Book.hpp"
#include "ISBN.hpp"
#include "Person.hpp"

    Book::Book(ISBN* isbn_num, std::string title_string, std::string author_string)
    {
        isbn = isbn_num;
        title = title_string;
        author = author_string;
        reader = nullptr;
    }

    Book::~Book()
    {
        delete isbn;
        delete reader;
        for(Book* book : booksRegistry)
        {
            delete book;
        }
    }

    ISBN* Book::getIsbn() const
    {
        return isbn;
    }

    std::string Book::getTitle() const
    {
        return title;
    }

    std::string Book::getAuthor() const
    {
        return author;
    }

    Person* Book::getReader() const
    {
        return reader;
    }

    Book* Book::getBooksRegistry()
    {
        for(Book* book : booksRegistry)
        {
            return book;
        }
    }

    void Book::setReader(Person* person)
    {
        reader = person;
    }

    void Book::removeReader()
    {
        reader = nullptr;
    }

    Book* Book::createBook(ISBN* isbn, std::string title, std::string author)
    {
        std::string str = (*isbn).getIsbn();
        if(ISBN::isValid(str))
        {
            for(Book* book : booksRegistry)
            {
                if (book->getIsbn() == isbn)
                {
                    std::cout << "A book with this ISBN already exists" << std::endl;
                }
                
            }
            Book* newBook = new Book(isbn, title, author);
            booksRegistry.push_back(newBook);
            return newBook;
        }
        else
        {
            std::cout << "The ISBN is not valid! A book can not be created!" << std::endl;
        }
    }

    void Book::removeBook(Book* book)
    {
        if (!book)
        {
            std::cout << "Invalid book!" << std::endl;
            return;
        }

        for(Book* bookToBeFound : booksRegistry)
        {
            if ((*bookToBeFound).getIsbn() == (*book).getIsbn() && (*bookToBeFound).getTitle() == (*book).getTitle() && (*bookToBeFound).getAuthor() == (*book).getAuthor())
            {
                if ((*bookToBeFound).isBorrowed())
                {
                    (*bookToBeFound).setReader(nullptr);
                    booksRegistry.erase(std::remove(booksRegistry.begin(), booksRegistry.end(), book), booksRegistry.end());
                    delete book;
                    book = nullptr;
                    break;
                }
                else
                {
                    booksRegistry.erase(std::remove(booksRegistry.begin(), booksRegistry.end(), book), booksRegistry.end());
                    delete book;
                    book = nullptr;
                    break;
                }
            }
        }
    }

    void Book::showAllBooks()
    {
        for(Book* book : booksRegistry)
        {
            std::cout << book << std::endl;
        }
    }

    Book* Book::findBook(ISBN* isbn)
    {
        std::string str = (*isbn).getIsbn();
        if (ISBN::isValid(str))
        {
            for(Book* bookToBeFound : booksRegistry)
            {
                if (bookToBeFound->getIsbn() == isbn)
                {
                    return bookToBeFound;
                }
                else 
                {
                    return nullptr;
                }
            }
        }
        else 
        {
            std::cout << "The certain ISBN is not valid!" << std::endl;
        }
    }

    bool Book::isBorrowed() const
    {
        if (reader != nullptr)
        {
            return true;
        }
        else
        {
            return false;
        }
    }