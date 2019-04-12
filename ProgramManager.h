//
// Created by Zellos on 12.04.2019.
//

#ifndef LIBRARYMANAGEMENT_PROGRAMMANAGER_H
#define LIBRARYMANAGEMENT_PROGRAMMANAGER_H

#include <vector>
#include <iostream>
#include "Book.h"
#include "Member.h"

using namespace std;

class ProgramManager {
private:
    vector<Member> members;
    vector<Book> books;
public:
    ProgramManager() = default;

    void AddBook() {
        string isbn, title, genre;

        cout << "Please enter the book title: ";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        getline(cin, title, '\n');
        cout << "Enter the ISBN number: ";
        getline(cin, isbn, '\n');
        cout << "Enter the genre: ";
        getline(cin, genre, '\n');
        books.emplace_back(Book(isbn, genre, title));
    }

    void AddMember() {
        string name, address;
        int age;

        cout << "Enter new members full name: ";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        getline(cin, name, '\n');
        cout << "Enter their address: ";
        getline(cin, address, '\n');
        cout << "Enter their age: ";
        cin >> age;
        members.emplace_back(Member(name, address, age));
    }

    void ShowMembers() {
        for (auto member : members) {
            member.showDetails();
        }
    }

    void ShowBooks() {
        for (auto book : books) {
            book.showDetails();
        }
    }

    void ShowMainMenu() {
        cout << "1. Show list of all books" << endl << "2. Show list of all members" << endl << "3. Add a new book"
             << endl << "4. Add a new member" << endl << "5. Quit" << endl;
    }
};

#endif //LIBRARYMANAGEMENT_PROGRAMMANAGER_H
