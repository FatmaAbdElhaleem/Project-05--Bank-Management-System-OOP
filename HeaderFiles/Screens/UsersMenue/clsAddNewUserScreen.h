#pragma once
#include <iostream>
#include <iomanip>
#include "../ClientMainMenue/clsScreen.h"
#include "../../Core/clsUser.h"
#include "../../Lib/clsInputValidate.h"

class clsAddNewUserScreen : protected clsScreen
{
private:
    static void _ReadUserInfo(clsUser& User)
    {
        cout << "\nEnter FirstName: ";
        User.SetFirstName(clsInputValidate::ReadString());

        cout << "\nEnter LastName: ";
        User.SetLastName(clsInputValidate::ReadString());

        cout << "\nEnter Email: ";
        User.SetEmail(clsInputValidate::ReadString());

        cout << "\nEnter Phone: ";
        User.SetPhone(clsInputValidate::ReadString());

        cout << "\nEnter Password: ";
        User.SetPassword(clsInputValidate::ReadString());

        cout << "\nEnter Permission: ";
        User.SetPermissions(_ReadPermissionsToSet());
    }

    static int _ReadPermissionsToSet()
    {
        int Permissions = 0;

        if (clsInputValidate::confirmMessage("\nDo you want to give full access? y/n? "))
            return -1;

        cout << "\nDo you want to give access to:\n";

        if (clsInputValidate::confirmMessage("Show Client List? y/n? "))
            Permissions += clsUser::enMainMenuPermissions::pListClients;

        if (clsInputValidate::confirmMessage("Add New Client? y/n? "))
            Permissions += clsUser::enMainMenuPermissions::pAddNewClient;

        if (clsInputValidate::confirmMessage("Delete Client? y/n? "))
            Permissions += clsUser::enMainMenuPermissions::pDeleteClient;

        if (clsInputValidate::confirmMessage("Update Client? y/n? "))
            Permissions += clsUser::enMainMenuPermissions::pUpdateClients;

        if (clsInputValidate::confirmMessage("Find Client? y/n? "))
            Permissions += clsUser::enMainMenuPermissions::pFindClient;

        if (clsInputValidate::confirmMessage("Transactions? y/n? "))
            Permissions += clsUser::enMainMenuPermissions::pTransactions;

        if (clsInputValidate::confirmMessage("Manage Users? y/n? "))
            Permissions += clsUser::enMainMenuPermissions::pManageUsers;

        if (clsInputValidate::confirmMessage("Show Login Register? y/n? "))
            Permissions += clsUser::enMainMenuPermissions::pLoginRegister;

        return Permissions;
    }

    static void _PrintUser(clsUser User)
    {
        cout << "\nUser Card:";
        cout << "\n___________________";
        cout << "\nFirstName   : " << User.GetFirstName();
        cout << "\nLastName    : " << User.GetLastName();
        cout << "\nFull Name   : " << User.FullName();
        cout << "\nEmail       : " << User.GetEmail();
        cout << "\nPhone       : " << User.Phone();
        cout << "\nUser Name   : " << User.GetUserName();
        cout << "\nPassword    : " << User.GetPassword();
        cout << "\nPermissions : " << User.GetPermissions();
        cout << "\n___________________\n";

    }

public:
static void ShowAddNewUserScreen()
    {

        _DrawScreenHeader("\t  Add New User Screen");

        string UserName = "";

        cout << "\nPlease Enter UserName: ";
        UserName = clsInputValidate::ReadString();
        while (clsUser::IsUserExist(UserName))
        {
            cout << "\nUserName Is Already Used, Choose another one: ";
            UserName = clsInputValidate::ReadString();
        }

        clsUser NewUser = clsUser::GetAddNewUserObject(UserName);

        _ReadUserInfo(NewUser);

        clsUser::enSaveResults SaveResult;

        SaveResult = NewUser.Save();

        switch (SaveResult)
        {
        case  clsUser::enSaveResults::svSucceeded:
        {
            cout << "\nUser Addeded Successfully :-)\n";
            _PrintUser(NewUser);
            break;
        }
        case clsUser::enSaveResults::svFaildEmptyObject:
        {
            cout << "\nError User was not saved because it's Empty";
            break;

        }
        case clsUser::enSaveResults::svFaildUserExists:
        {
            cout << "\nError User was not saved because UserName is used!\n";
            break;

        }
        }
    }
};


