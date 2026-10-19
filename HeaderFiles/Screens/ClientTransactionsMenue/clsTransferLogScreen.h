#pragma once
#include <iostream>
#include "../ClientMainMenue/clsScreen.h"
#include "../../Lib/clsInputValidate.h"
#include "../../Core/clsBankClient.h"

class clsTransferLogScreen :protected clsScreen
{
private:
    static void PrintTransferLogRecordLine(clsBankClient::stTransferLogRecord TransferLogRecord)
    {

        cout << setw(8) << left << "" << "| " << setw(23) << left << TransferLogRecord.DateTime;
        cout << "| " << setw(8) << left << TransferLogRecord.SourceAccountNumber;
        cout << "| " << setw(8) << left << TransferLogRecord.DestinationAccountNumber;
        cout << "| " << setw(8) << left << TransferLogRecord.Amount;
        cout << "| " << setw(10) << left << TransferLogRecord.SrcBalanceAfter;
        cout << "| " << setw(10) << left << TransferLogRecord.DestBalanceAfter;
        cout << "| " << setw(8) << left << TransferLogRecord.UserName;
    }

public:
    static void ShowTransferLogScreen()
    {
        vector<clsBankClient::stTransferLogRecord> vTransferRecords = clsBankClient::LoadTransferLogRecords();
        _DrawScreenHeader("Transfer Log Screen");

        string Title = "\tTransfer Log List Screen";
        string SubTitle = "\t    (" + to_string(vTransferRecords.size()) + ") Record(s).";

        _DrawScreenHeader(Title, SubTitle);

        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;

        cout << setw(8) << left << "" << "| " << left << setw(23) << "Date/Time";
        cout << "| " << left << setw(8) << "s.Acct";
        cout << "| " << left << setw(8) << "d.Acct";
        cout << "| " << left << setw(8) << "Amount";
        cout << "| " << left << setw(10) << "s.Balance";
        cout << "| " << left << setw(10) << "d.Balance";
        cout << "| " << left << setw(8) << "User";

        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;

        if (vTransferRecords.size() == 0)
            cout << "\t\t\t\tNo Transfers Available In the System!";
        else

            for (clsBankClient::stTransferLogRecord Record : vTransferRecords)
            {

                PrintTransferLogRecordLine(Record);
                cout << endl;
            }

        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;


    }
};
