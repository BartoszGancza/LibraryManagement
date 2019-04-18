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
    ProgramManager manager;
    WindowManager window = WindowManager("Test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600,
                                         SDL_WINDOW_SHOWN);
    window.init();

    int flag;
    cout << "Welcome to the library management system!" << endl;
    while (true) {
        flag = manager.ShowMainMenu(window);
        switch (flag) {
            case newMember:
                manager.AddMember(window);
                break;
            case newBook:
                manager.AddBook(window);
                break;
            case memberList:
                manager.MemberDetails();
                break;
            case bookList:
                manager.BookDetails();
                break;
            /*case borrowBook:
                manager.BorrowBook();
                break;*/
            case quit:
                window.freeResources();
                exit(0);
            default:
                manager.ShowMainMenu(window);
                break;
        }
    }

    return 0;
}