#ifndef LIBRARYMANAGEMENT_PROGRAMMANAGER_H
#define LIBRARYMANAGEMENT_PROGRAMMANAGER_H

#include <vector>
#include <iostream>
#include <sstream>
#include <cctype>
#include "Book.h"
#include "Member.h"
#include "WindowManager.h"

using namespace std;

class ProgramManager {
private:
    vector<Member> members;
    vector<Book> books;
    stringstream stream;
public:
    ProgramManager() = default;

    string ListOfBooks() {
        int counter = 0;
        stringstream temp;
        for (auto book : books) {
            temp << ++counter << ". " << book.showTitle() << endl;
        }
        return temp.str();
    }

    string ListOfMembers() {
        int counter = 0;
        stringstream temp;
        for (auto member : members) {
            temp << ++counter << ". " << member.showName() << endl;
        }
        return temp.str();
    }

    void BorrowBook(WindowManager &window) {
        string choiceMember, choiceBook, booksList, membersList;

        stream.str("");

        stream << "Input \"q\" at any time to go back to Main Menu." << endl << "Who is borrowing the book?" << endl;
        membersList = ListOfMembers();
        choiceMember = window.grabInput(stream.str() + membersList + "Member ID: ");
        if ("q" == choiceMember) { return; }
        while (stoi(choiceMember) - 1 >= members.size() || stoi(choiceMember) < 1) {
            stream.str("");
            stream << "There is no member with this ID, please try again or \"q\" to quit: ";
            choiceMember = window.grabInput(membersList + stream.str());
            if ("q" == choiceMember) { return; }
        }
        stream.str("");
        stream << "Which book?" << endl;
        booksList = ListOfBooks();
        choiceBook = window.grabInput(stream.str() + booksList + "Book ID: ");
        if ("q" == choiceBook) { return; }
        while (stoi(choiceBook) - 1 >= books.size() || stoi(choiceBook) < 1) {
            stream.str("");
            stream << "There is no book with this ID, please try again or \"q\" to quit: ";
            choiceBook = window.grabInput(booksList + stream.str());
            if ("q" == choiceBook) { return; }
        }
        books[stoi(choiceBook) - 1].lend(members[stoi(choiceMember) - 1]);
    }

    void AddBook(WindowManager &window) {
        string isbn, title, genre;

        title = window.grabInput("Please enter the book title: ");
        isbn = window.grabInput("Enter the ISBN number: ");
        genre = window.grabInput("Enter the genre: ");
        books.emplace_back(Book(isbn, genre, title));
    }

    void AddMember(WindowManager &window) {
        string name, address, age;

        name = window.grabInput("Enter new members full name: ");
        address = window.grabInput("Enter their address: ");
        age = window.grabInput("Enter their age: ");
        members.emplace_back(Member(name, address, age));
    }

    void MemberDetails(WindowManager &window) {
        string choice, flag, list;

        stream.str("");

        list = ListOfMembers();
        stream << "To check member details, input the member ID number. To go back to main menu input \"q\": ";
        choice = window.grabInput(list + stream.str());
        if ("q" == choice) { return; }
        while (stoi(choice) - 1 >= members.size() || stoi(choice) < 1) {
            stream.str("");
            stream << "There is no member with this ID, please try again or \"q\" to quit: ";
            choice = window.grabInput(list + stream.str());
            if ("q" == choice) { return; }
        }
        do {
           flag = window.grabInput(members[stoi(choice) - 1].showDetails());
        } while (flag != "q");
    }

    void BookDetails(WindowManager &window) {
        string choice, flag, list;

        stream.str("");

        list = ListOfBooks();
        stream << "To check book details, input the book number. To go back to main menu input \"q\": ";
        choice = window.grabInput(list + stream.str());
        if ("q" == choice) { return; }
        while (stoi(choice) - 1 >= books.size() || stoi(choice) < 1) {
            stream.str("");
            stream << "There is no book with this ID, please try again or \"q\" to quit: ";
            choice = window.grabInput(list + stream.str());
            if ("q" == choice) { return; }
        }
        do {
            flag = window.grabInput(books[stoi(choice) - 1].showDetails());
        } while (flag != "q");
    }

    int ShowMainMenu(WindowManager &window) {
        string choice;
        // Clear stream before proceeding
        stream.str("");

        stream << "1. Show list of all books" << endl << "2. Show list of all members" << endl << "3. Add a new book"
               << endl << "4. Add a new member" << endl << "5. Borrow a book" << endl << "6. Quit" << endl << endl
               << "What would you like to do: ";
        choice = window.grabInput(stream.str());

        return stoi(choice);
    }
};

#endif //LIBRARYMANAGEMENT_PROGRAMMANAGER_H
