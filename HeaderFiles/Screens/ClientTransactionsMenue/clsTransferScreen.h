#pragma once
#include <iostream>
#include <iomanip>
#include "../ClientMainMenue/clsScreen.h"
#include "../../Lib/clsInputValidate.h"
#include "../../Core/clsBankClient.h"

class clsTransferScreen :protected clsScreen
{
private:
    static void _PrintClientBreifInfoCard(clsBankClient Client)
    {
        cout << "\nClient Card\n";
        cout << "\n___________________\n\n";
        cout << left << setw(13) << "Full Name" << ": " << Client.FullName() << endl;
        cout << setw(13) << "Acc. Number" << ": " << Client.AccountNumber() << endl;
        cout << setw(13) << "Balance" << ": " << Client.GetAccountBalance() << endl;
        cout << "___________________\n";
    }

    static string _ReadAccountNumber(string Message)
    {
        cout << Message;
        string AccountNumber = clsInputValidate::ReadString();

        while (!clsBankClient::IsClientExist(AccountNumber))
        {
            cout << "\nAccount number is not found, choose another one: ";
            AccountNumber = clsInputValidate::ReadString();
        }
        return AccountNumber;
    }

    static double _ReadAmount(clsBankClient SourceClient)
    {
        cout << "Enter Transfer Amount? ";
        double TransferAmount = clsInputValidate::ReadDblNumber();
        while (TransferAmount > SourceClient.GetAccountBalance())
        {
            cout << "Amount Exceeds the Available Balance, Enter another Amount ? ";
            TransferAmount = clsInputValidate::ReadDblNumber();
        }
        return TransferAmount;
    }

public:
    static void ShowTransferScreen()
    {
        _DrawScreenHeader("\t Transfer Screen");

        clsBankClient SourceClient = clsBankClient::Find(_ReadAccountNumber("\nPlease Enter Account Number to Transfer From: "));
        _PrintClientBreifInfoCard(SourceClient);

        clsBankClient DestinationClient = clsBankClient::Find(_ReadAccountNumber("\nPlease Enter Account Number to Transfer To: "));
        _PrintClientBreifInfoCard(DestinationClient);

        double TransferAmount = _ReadAmount(SourceClient);

        if (clsInputValidate::confirmMessage("Are you sure you want to perform this operation? y/n? "))
        {
            if (SourceClient.Transfer(TransferAmount, DestinationClient))
            {
                cout << "\nTransfer done successfully\n";
            }
            else
            {
                 cout << "\nTransfer Failed\n";
            }

            _PrintClientBreifInfoCard(SourceClient);
            _PrintClientBreifInfoCard(DestinationClient);
        }

    }
};