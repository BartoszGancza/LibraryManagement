#include <string>
#include <iostream>
#include <random>
#include <vector>
#include <sstream>
#include "Book.h"
#include "Member.h"
#include "ProgramManager.h"

using namespace std;

enum flags {
    mainMenu, newMember = 4, newBook = 3, memberList = 2, bookList = 1, quit = 5
};

int main() {

    ProgramManager manager;
    int flag = 0;
    cout << "Welcome to the library management system!" << endl;
    while (true) {
        cout << endl << "MAIN MENU" << endl;
        manager.ShowMainMenu();
        cout << "What would you like to do: ";
        cin >> flag;
        switch (flag) {
            case newMember:
                manager.AddMember();
                break;
            case newBook:
                manager.AddBook();
                break;
            case memberList:
                manager.ShowMembers();
                break;
            case bookList:
                manager.ShowBooks();
                break;
            case quit:
                exit(0);
            default:
                manager.ShowMainMenu();
                break;
        }
    }

    return 0;
}