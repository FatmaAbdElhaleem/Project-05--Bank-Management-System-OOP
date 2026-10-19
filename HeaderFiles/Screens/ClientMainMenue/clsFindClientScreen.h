#pragma once
#include <iostream>
#include "../../Lib/clsInputValidate.h"
#include "../../Core/clsBankClient.h"
#include "clsScreen.h"

using namespace std;

class clsFindClientScreen : protected clsScreen
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
    static void ShowFindClientScreen()
    {

        if(!CheckAccessRights(clsUser::enMainMenuPermissions::pFindClient))
        {
            return;
        }

        _DrawScreenHeader("\tFind Client Screen");
        cout << "\nPlease Enter Account Number: ";
        string AccountNumber = clsInputValidate::ReadString();

        while (!clsBankClient::IsClientExist(AccountNumber))
        {
            cout << "Account number is not found, Choose another one: \n";
            AccountNumber = clsInputValidate::ReadString();
        };

        clsBankClient Client = clsBankClient::Find(AccountNumber);
        if (!Client.IsEmpty())
        {
            cout << "\nClient Found :-)\n";
        }
        else
        {
            cout << "\nClient Was not Found :-(\n";
        }

        _PrintClient(Client);
    }
};