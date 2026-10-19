#pragma once
#include <iostream>
#include "../ClientMainMenue/clsScreen.h"
#include "../../Core/clsUser.h"
#include "../../Lib/Global.h"

class clsLoginScreen :protected clsScreen
{
private:
    

    static bool _Login() {
        string Username, Password;
        bool LoginFailed = false;
        short FaildLoginCount = 0;

        do {

            if (LoginFailed) {
                FaildLoginCount++;
                cout << "\nInvlaid Username/Password!\n\n";
                cout << "\nYou have " << (3 - FaildLoginCount)
                    << " Trial(s) to login.\n\n";
            }

            if (FaildLoginCount == 3) {
                cout << "\nYou are locked after 3 Failed Trails\n";
                return false;
            }

            cout << "Enter Username? ";
            cin >> Username;

            cout << "Enter Password? ";
            cin >> Password;

            CurrentUser = clsUser::Find(Username, Password);
            LoginFailed = CurrentUser.IsEmpty();

        } while (LoginFailed);

        CurrentUser.RegisterLogins();
        clsMainScreen::ShowMainMenue();
        return true;

    }

public:
    static bool ShowLoginScreen()
    {
        system("cls");
        _DrawScreenHeader("\t   Login Screen");
        return _Login();
    }

};