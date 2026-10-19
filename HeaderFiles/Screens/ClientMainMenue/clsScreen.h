#pragma once
#include <iostream> 
#include "../../Core/clsUser.h"
#include "../../Lib/Global.h"
#include "../../Lib/clsDate.h"
using namespace std;


class clsScreen {
private:
    static void _PrintCommonInfo()
    {
        if (CurrentUser.IsEmpty())
            cout << "\t\t\t\t\tUser: No User Logged in yet" << endl;
        else
            cout << "\t\t\t\t\tUser: " << CurrentUser.GetUserName() << endl;

        cout << "\t\t\t\t\tDate: " << clsDate::DateToString(clsDate::GetSystemDate()) << "\n\n";
    }

protected:
    static void _DrawScreenHeader(string Title, string SubTitle = "") {
        cout << "\t\t\t\t\t______________________________________";
        cout << "\n\n\t\t\t\t\t  " << Title;

        if (SubTitle != "") {
            cout << "\n\t\t\t\t\t  " << SubTitle;
        }
        cout << "\n\t\t\t\t\t______________________________________\n\n";
        _PrintCommonInfo();
    }

    static bool CheckAccessRights(clsUser::enMainMenuPermissions Permission) {
        if (!CurrentUser.CheckAccessPermission(Permission))
        {
            cout << "\t\t\t\t\t______________________________________";
            cout << "\n\n\t\t\t\t\t  Access Denied! Contact your Admin.";
            cout << "\n\t\t\t\t\t______________________________________\n\n";
            return false;

        }
        else
        {
            return true;
        }
    }
};