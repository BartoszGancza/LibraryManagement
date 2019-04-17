#include <string>
#include <iostream>
#include <random>
#include <vector>
#include <sstream>
#include "Book.h"
#include "Member.h"
#include "ProgramManager.h"
#include "WindowManager.h"
#include "SDL.h"

using namespace std;

enum flags {
    mainMenu, newMember = 4, newBook = 3, memberList = 2, bookList = 1, borrowBook = 5, quit = 6
};

int main(int argc, char *argv[]) {

    /*ProgramManager manager;
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
                manager.MemberDetails();
                break;
            case bookList:
                manager.BookDetails();
                break;
            case borrowBook:
                manager.BorrowBook();
                break;
            case quit:
                exit(0);
            default:
                manager.ShowMainMenu();
                break;
        }
    }*/

    WindowManager window = WindowManager("Test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600,
                                         SDL_WINDOW_SHOWN);

    window.init();
    ProgramManager manager;
    manager.ShowMainMenu(window);
    window.freeResources();


    return 0;
}