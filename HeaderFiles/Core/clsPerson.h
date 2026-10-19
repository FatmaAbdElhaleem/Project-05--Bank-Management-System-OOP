#pragma once
#include<iostream>
using namespace std;

class clsPerson
{
private:
    string _FirstName;
    string _LastName;
    string _Email;
    string _Phone;

public:
    clsPerson(string FirstName, string LastName, string Email, string Phone) {
        _FirstName = FirstName;
        _LastName = LastName;
        _Email = Email;
        _Phone = Phone;
    }

    void SetFirstName(string FristName) {
        _FirstName = FristName;
    }
    void SetLastName(string LastName) {
        _LastName = LastName;
    }
    void SetEmail(string Email) {
        _Email = Email;
    }
    void SetPhone(string Phone) {
        _Phone = Phone;
    }

    string GetFirstName() {
        return _FirstName;
    }
    string GetLastName() {
        return _LastName;
    }
    string GetEmail() {
        return _Email;
    }
    string Phone() {
        return _Phone;
    }
    string FullName() {
        return _FirstName + " " + _LastName;
    }
    // void Print() {
    //     cout << "\nInfo:\n";
    //     cout << "_________________________";
    //     cout << "\nFirstName: " << _FirstName;
    //     cout << "\nLastName: " << _LastName;
    //     cout << "\nFull Name: " << FullName();
    //     cout << "\nEmail    : " << _Email;
    //     cout << "\nPhone    : " << _Phone;
    //     cout << "\n________________________\n";
    // }
};
