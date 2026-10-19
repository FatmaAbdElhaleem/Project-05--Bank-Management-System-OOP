#pragma once
#include<iostream>
#include "../../Lib/clsInputValidate.h"
#include "../../Core/clsBankClient.h"
#include "clsScreen.h"
using namespace std;

class clsDeleteClientScreen : protected clsScreen
{
private:
    static void _PrintClient(clsBankClient Client)
    {
        cout << "\n\nClient Card:";
        cout << "\n___________________";
        cout << "\nFirstName   : " << Client.GetFirstName();
        cout << "\nLastName    : " << Client.GetLastName();
        cout << "\nFull Name   : " << Client.FullName();
        cout << "\nEmail       : " << Client.GetEmail();
        cout << "\nPhone       : " << Client.Phone();
        cout << "\nAcc. Number : " << Client.AccountNumber();
        cout << "\nPassword    : " << Client.GetPinCode();
        cout << "\nBalance     : " << Client.GetAccountBalance();
        cout << "\n___________________\n\n";
    } 

public:
    static void ShowDeleteClientScreen() {

        if(!CheckAccessRights(clsUser::enMainMenuPermissions::pDeleteClient))
        {
            return;
        }

       _DrawScreenHeader("\tDelete Client Screen");

        cout << "\nPlease Enter Account Number: ";
        string AccountNumber = clsInputValidate::ReadString();

        while (!clsBankClient::IsClientExist(AccountNumber))
        {
            cout << "Account number is not found, Choose another one: \n";
            AccountNumber = clsInputValidate::ReadString();
        };

        clsBankClient Client = clsBankClient::Find(AccountNumber);
        _PrintClient(Client);

        cout << "\nAre you sure you want to delete this client y/n? \n";
        char DeleteOrNot = 'n';
        cin >> DeleteOrNot;

        if (DeleteOrNot == 'y' || DeleteOrNot == 'Y') {
            if (Client.Delete()) {
                cout << "\nClient Deleted successfully :-)\n";
                _PrintClient(Client);
            }
            else {
                cout << "\nError Client Was not Deleted\n";
            }
        }

    }
};