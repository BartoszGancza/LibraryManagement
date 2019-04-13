#ifndef LIBRARYMANAGEMENT_BOOK_H
#define LIBRARYMANAGEMENT_BOOK_H

#include <string>
#include <iostream>

using namespace std;

class Book {
private:
    string bookNumber, genre, title;
    bool isLent = false;
public:
    Book(string isbn, string genre, string title) : bookNumber(move(isbn)), genre(move(genre)), title(move(title)) {};

    void showDetails() {
        cout << "ISBN: " << bookNumber << endl << "Title: " << title << endl << "Genre: " << genre << endl;
    }

    void lend() { isLent = true; }

    void returnBook() { isLent = false; }

    void status() { cout << "The book is currently " << (isLent ? "lent." : "not lent.") << endl; }

    void changeGenre(string newGenre) { genre = move(newGenre); }

    void changeISBN(string newISBN) { bookNumber = move(newISBN); }

    void changeTitle(string newTitle) { title = move(newTitle); }

    string showTitle() { return title; }
};

#endif //LIBRARYMANAGEMENT_BOOK_H
