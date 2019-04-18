#ifndef LIBRARYMANAGEMENT_MEMBER_H
#define LIBRARYMANAGEMENT_MEMBER_H

#include <string>
#include <iostream>

using namespace std;

class Member {
private:
    string name, address, age;
    int memberID, borrowedBooks = 0;
    static int currID;

    static int getCurrID() {
        ++currID;
        return currID;
    }

public:
    Member(string fullName, string address, string age) : name(move(fullName)), address(move(address)), age(age),
                                                       memberID(getCurrID()) {};

    void changeName(string newName) { name = move(newName); }

    void changeAddress(string newAddress) { address = move(newAddress); }

    void changeAge(string newAge) { age = newAge; }

    void showDetails() {
        cout << "ID: " << memberID << endl << "Name: " << name << endl << "Address: " <<
             address << endl << "Age: " << age << endl << "Number of borrowed books: " << borrowedBooks << endl;
    }

    string showName() { return name; }

    int showID() { return memberID; }

    int showBorrowedBooks() { return borrowedBooks; }

};

int Member::currID = 0;
#endif //LIBRARYMANAGEMENT_MEMBER_H
