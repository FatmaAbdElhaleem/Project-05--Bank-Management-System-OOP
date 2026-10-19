#pragma once
#include <iostream>
#include "../../Lib/clsInputValidate.h"
#include "../../Core/clsBankClient.h"
#include "clsScreen.h"
#include <iomanip>

class clsClientListScreen :protected clsScreen
{
private:
    static void PrintClientRecordLine(clsBankClient Client)
    {
        cout << setw(8) << left << "" << "| " << setw(15) << left << Client.AccountNumber();
        cout << "| " << left << setw(20) << Client.FullName();
        cout << "| " << left << setw(12) << Client.Phone();
        cout << "| " << left << setw(20) << Client.GetEmail();
        cout << "| " << left << setw(10) << Client.GetPinCode();
        cout << "| " << left << setw(12) << Client.GetAccountBalance();
    };

public:
    static void ShowClientsList() {

        if(!CheckAccessRights(clsUser::enMainMenuPermissions::pListClients))
        {
            return;
        }

        vector <clsBankClient> vClients = clsBankClient::GetClientsList();
        string Title = "\t  Client List Screen";
        string SubTitle = "\t    (" + to_string(vClients.size()) + ") Client(s).";

        _DrawScreenHeader(Title, SubTitle);

        // cout << "\n\t\t\t\t\tClient List (" << vClients.size() << ") Client(s).";
        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;

        cout << setw(8) << left << "" << "| " << left << setw(15) << "Accout Number";
        cout << "| " << left << setw(20) << "Client Name";
        cout << "| " << left << setw(12) << "Phone";
        cout << "| " << left << setw(20) << "Email";
        cout << "| " << left << setw(10) << "Pin Code";
        cout << "| " << left << setw(12) << "Balance";
        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;

        if (vClients.size() == 0) {
            cout << "\t\t\t\tNo Clients Available In the System!";
        }
        else
            for (const clsBankClient& Client : vClients) {
                PrintClientRecordLine(Client);
                cout << endl;
            }
        cout << setw(8) << left << "" <<"\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;

    }
};