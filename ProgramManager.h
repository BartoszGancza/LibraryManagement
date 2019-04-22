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

    vector<string> listOfBooks() {
        int counter = 0;
        vector<string> list;
        stringstream temp;
        string text;
        for (auto book : books) {
            temp << ++counter << ". " << book.showTitle() << endl;
            text = temp.str();
            list.emplace_back(text);
        }
        return list;
    }

    vector<string> listOfMembers() {
        int counter = 0;
        stringstream temp;
        string text;
        vector<string> list;
        for (auto member : members) {
            temp << ++counter << ". " << member.showName() << endl;
            text = temp.str();
            list.emplace_back(text);
        }
        return list;
    }

    void borrowBook(WindowManager &window) {
        int choiceMember, choiceBook;
        vector<string> booksList = listOfBooks(), membersList = listOfMembers();
        vector<SDL_Rect> positions;

        stream.str("");

        stream << "Push ESC at any time to go back to main menu." << endl << "Who is borrowing the book?" << endl;
        positions = window.renderMenu(membersList, stream.str());
        choiceMember = window.trackMouse(positions);
        if (-1 == choiceMember) { return; }
        stream.str("");
        stream << "Which book?" << endl;
        positions = window.renderMenu(booksList, stream.str());
        choiceBook = window.trackMouse(positions);
        if (-1 == choiceBook) { return; }
        books[choiceBook].lend(members[choiceMember]);
        window.renderTextTexture(
                books[choiceBook].showTitle() + " has been lent to " + members[choiceMember].showName() + ".");
        SDL_Delay(1500);
    }

    void addBook(WindowManager &window) {
        string isbn, title, genre;

        title = window.grabInput("Please enter the book title: ");
        isbn = window.grabInput("Enter the ISBN number: ");
        genre = window.grabInput("Enter the genre: ");
        books.emplace_back(Book(isbn, genre, title));
    }

    void addMember(WindowManager &window) {
        string name, address, age;

        name = window.grabInput("Enter new members full name: ");
        address = window.grabInput("Enter their address: ");
        age = window.grabInput("Enter their age: ");
        members.emplace_back(Member(name, address, age));
    }

    void memberDetails(WindowManager &window) {
        int choice;
        string flag;
        vector<string> list = listOfMembers();
        vector<SDL_Rect> positions;

        stream.str("");

        stream << "To check member details, click on the name or push ESC to go back to main menu.";
        positions = window.renderMenu(list, stream.str());
        choice = window.trackMouse(positions);
        if (-1 == choice) { return; }
        window.renderTextTexture(members[choice].showDetails());
        window.trackMouse();
    }

    void bookDetails(WindowManager &window) {
        int choice;
        string flag;
        vector<string> list = listOfBooks();
        vector<SDL_Rect> positions;

        stream.str("");

        stream << "To check book details, click on the name or push ESC to go back to main menu.";
        positions = window.renderMenu(list, stream.str());
        choice = window.trackMouse(positions);
        if (-1 == choice) { return; }
        window.renderTextTexture(books[choice].showDetails());
        window.trackMouse();
    }

    int showMainMenu(WindowManager &window) {
        int choice;
        vector<SDL_Rect> positions;
        vector<string> menuItems{"1. Show list of all books", "2. Show list of all members", "3. Add a new book",
                                 "4. Add a new member", "5. Borrow a book", "6. Quit"};

        positions = window.renderMenu(menuItems, "Welcome to library management interface!");
        choice = window.trackMouse(positions);

        return choice;
    }
};

#endif //LIBRARYMANAGEMENT_PROGRAMMANAGER_H
