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

    void ListOfBooks() {
        int counter = 0;
        for (auto book : books) {
            cout << ++counter << ". " << book.showTitle() << endl;
        }
    }

    void ListOfMembers() {
        int counter = 0;
        for (auto member : members) {
            cout << ++counter << ". " << member.showName() << endl;
        }
    }

    void BorrowBook(WindowManager &window) {
        string choiceMember, choiceBook;

        cout << "Input \"q\" at any time to go back to Main Menu." << endl << "Who is borrowing the book?" << endl;
        ListOfMembers();
        window.grabText("Who is borrowing the book?");
        cout << "Member ID: ";
        cin >> choiceMember;
        if ("q" == choiceMember) { return; }
        cout << "Select the book:" << endl;
        ListOfBooks();
        cout << "Book ID: ";
        cin >> choiceBook;
        if ("q" == choiceBook) { return; }
        /*TODO: Finish the function, and rework it for the GUI version*/

    }

    void AddBook(WindowManager &window) {
        string isbn, title, genre;

        title = window.grabText("Please enter the book title: ");
        isbn = window.grabText("Enter the ISBN number: ");
        genre = window.grabText("Enter the genre: ");
        books.emplace_back(Book(isbn, genre, title));
    }

    void AddMember(WindowManager &window) {
        string name, address, age;

        name = window.grabText("Enter new members full name: ");
        address = window.grabText("Enter their address: ");
        age = window.grabText("Enter their age: ");
        members.emplace_back(Member(name, address, age));
    }

    void MemberDetails() {
        string choice;

        ListOfMembers();
        cout << "To check member details, input the member ID number. To go back to main menu input \"q\": ";
        cin >> choice;
        if ("q" == choice) { return; }
        while (stoi(choice) - 1 >= members.size() || stoi(choice) < 1) {
            cout << "There is no member with this ID, please try again or \"q\" to quit: ";
            cin >> choice;
            if ("q" == choice) { return; }
        }
        members[stoi(choice) - 1].showDetails();
        /*TODO: Rework for the GUI version*/
    }

    void BookDetails() {
        string choice;

        ListOfBooks();
        cout << "To check book details, input the book number. To go back to main menu input \"q\": ";
        cin >> choice;
        if ("q" == choice) { return; }
        while (stoi(choice) - 1 >= books.size() || stoi(choice) < 1) {
            cout << "There is no book with this ID, please try again or \"q\" to quit: ";
            cin >> choice;
            if ("q" == choice) { return; }
        }
        books[stoi(choice) - 1].showDetails();
        /*TODO: Reework for the GUI version*/
    }

    int ShowMainMenu(WindowManager &window) {
        string choice;
        stream << "1. Show list of all books" << endl << "2. Show list of all members" << endl << "3. Add a new book"
               << endl << "4. Add a new member" << endl << "5. Borrow a book" << endl << "6. Quit" << endl << endl
               << "What would you like to do: ";
        choice = window.grabText(stream.str());
        return stoi(choice);
    }
};

#endif //LIBRARYMANAGEMENT_PROGRAMMANAGER_H
