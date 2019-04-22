#ifndef LIBRARYMANAGEMENT_BOOK_H
#define LIBRARYMANAGEMENT_BOOK_H

#include <string>
#include <sstream>
#include <iostream>
#include "Member.h"

using namespace std;

class Book {
private:
    string bookNumber, genre, title;
    bool isLent = false;
public:
    Book(string isbn, string genre, string title) : bookNumber(move(isbn)), genre(move(genre)), title(move(title)) {};

    string showDetails() {
        stringstream details;
        details << "ISBN: " << bookNumber << endl << "Title: " << title << endl << "Genre: " << genre << endl
                << "Push ESC to go back to Main Menu.";
        return details.str();
    }

    void lend(Member &member) { isLent = true; member.borrowBook(); }

    void returnBook(Member &member) { isLent = false; member.returnBook(); }

    void status() { cout << "The book is currently " << (isLent ? "lent." : "not lent.") << endl; }

    void changeGenre(string newGenre) { genre = move(newGenre); }

    void changeISBN(string newISBN) { bookNumber = move(newISBN); }

    void changeTitle(string newTitle) { title = move(newTitle); }

    string showTitle() { return title; }
};

#endif //LIBRARYMANAGEMENT_BOOK_H
