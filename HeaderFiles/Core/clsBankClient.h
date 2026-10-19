#pragma once
#include <iostream>
#include <string>
#include "clsPerson.h"
#include "../Lib/clsString.h"
#include "../Lib/Global.h"
#include <vector>
#include <fstream>

using namespace std;

class clsBankClient : public clsPerson
{
public:
    struct stTransferLogRecord {
        string DateTime;
        string SourceAccountNumber;
        string DestinationAccountNumber;
        double Amount;
        double SrcBalanceAfter;
        double DestBalanceAfter;
        string UserName;
    };
private:
    enum enMode { EmptyMode = 0, UpdateMode = 1, AddNewMode = 2 };
    enMode _Mode;

    string _AccountNumber;
    string _PinCode;
    float _AccountBalance;
    bool _MarkForDelete = false;


    static clsBankClient _ConvertLineToClientObject(string Line, string Seperator = "#//#") {
        vector <string> vClientData;
        vClientData = clsString::Split(Line, Seperator);
        return clsBankClient(enMode::UpdateMode, vClientData[0], vClientData[1], vClientData[2], vClientData[3], vClientData[4], vClientData[5], stod(vClientData[6]));
    };

    static string _ConvertClientObjectToDataLine(clsBankClient Client, string Seperator = "#//#")
    {
        string stClientRecord = "";
        stClientRecord += Client.GetFirstName() + Seperator;
        stClientRecord += Client.GetLastName() + Seperator;
        stClientRecord += Client.GetEmail() + Seperator;
        stClientRecord += Client.Phone() + Seperator;
        stClientRecord += Client.AccountNumber() + Seperator;
        stClientRecord += Client.GetPinCode() + Seperator;
        stClientRecord += to_string(Client.GetAccountBalance());

        return stClientRecord;
    }

    static clsBankClient _GetEmptyClientObject() {
        return clsBankClient(enMode::EmptyMode, "", "", "", "", "", "", 0);
    }

    static vector <clsBankClient> _LoadClientsDataFromFile() {
        vector <clsBankClient> vClients;
        fstream MyFile;
        MyFile.open(ClientsFileName, ios::in);
        if (MyFile.is_open()) {
            string Line;
            while (getline(MyFile, Line)) {
                clsBankClient Client = _ConvertLineToClientObject(Line);
                vClients.push_back(Client);
            }
            MyFile.close();
        }
        return vClients;
    }

    static void _SaveClientsDataToFile(vector <clsBankClient> vClients) {
        fstream MyFile;
        MyFile.open(ClientsFileName, ios::out);
        if (MyFile.is_open()) {
            string DataLine = "";
            for (clsBankClient C : vClients) {
                if (!C.MarkForDelete()) {
                    DataLine = _ConvertClientObjectToDataLine(C);
                    MyFile << DataLine << endl;
                }
            }
            MyFile.close();
        }
    }

    void _Update() {
        vector <clsBankClient> _vClients;
        _vClients = _LoadClientsDataFromFile();
        for (clsBankClient& C : _vClients) {
            if (C.AccountNumber() == this->_AccountNumber)
            {
                C = *this;
                break;
            }
        }
        _SaveClientsDataToFile(_vClients);
    }

    void _AddNew() {
        _AddDataLineToFile(_ConvertClientObjectToDataLine(*this));
    }

    void _AddDataLineToFile(string  stDataLine) {
        fstream MyFile;
        MyFile.open(ClientsFileName, ios::out | ios::app);
        if (MyFile.is_open()) {
            MyFile << stDataLine << endl;
            MyFile.close();
        }
    }

    string _PrepareTransferHistoryDataLine(double Amount, clsBankClient DestinationClient, string Seperator = "#//#")
    {
        string Line = "";
        Line = clsDate::GetSystemDateTimeString() + Seperator;
        Line += _AccountNumber + Seperator;
        Line += DestinationClient.AccountNumber() + Seperator;
        Line += to_string(Amount) + Seperator;
        Line += to_string(_AccountBalance) + Seperator;
        Line += to_string(DestinationClient.GetAccountBalance()) + Seperator;
        Line += CurrentUser.GetUserName();
        return Line;
    }

    void _RegisterTransferLog(double Amount, clsBankClient DestinationClient)
    {
        string DataLine = _PrepareTransferHistoryDataLine(Amount, DestinationClient);
        fstream MyFile;
        MyFile.open(TransferLogFile, ios::out | ios::app);
        if (MyFile.is_open())
        {
            MyFile << DataLine << endl;
        }
    }

    static stTransferLogRecord _ConvertTransferLogLineToStruct(string Line, string Seperator = "#//#")
    {
        vector <string> vLineData = clsString::Split(Line, Seperator);
        stTransferLogRecord TransferLogRecord;

        TransferLogRecord.DateTime = vLineData[0];
        TransferLogRecord.SourceAccountNumber = vLineData[1];
        TransferLogRecord.DestinationAccountNumber = vLineData[2];
        TransferLogRecord.Amount = stod(vLineData[3]);
        TransferLogRecord.SrcBalanceAfter = stod(vLineData[4]);
        TransferLogRecord.DestBalanceAfter = stod(vLineData[5]);
        TransferLogRecord.UserName = vLineData[6];

        return TransferLogRecord;
    }

public:
    clsBankClient(enMode Mode, string FirstName, string LastName, string Email, string Phone, string AccountNumber, string PinCode, float AccountBalance) :
        clsPerson(FirstName, LastName, Email, Phone)
    {
        _Mode = Mode;
        _AccountNumber = AccountNumber;
        _PinCode = PinCode;
        _AccountBalance = AccountBalance;
    }

    bool IsEmpty() {
        return (_Mode == enMode::EmptyMode);
    }

    string AccountNumber() {
        return _AccountNumber;
    }

    bool MarkForDelete() {
        return _MarkForDelete;
    }
    void SetPinCode(string PinCode) {
        _PinCode = PinCode;
    }

    void SetAccountBalance(float AccountBalance) {
        _AccountBalance = AccountBalance;
    }

    string GetPinCode() {
        return _PinCode;
    }

    float GetAccountBalance() {
        return _AccountBalance;
    }

    // No Ui in object it should be seperated
    // void Print() {
    //     cout << "\n\nClient Card:";
    //     cout << "\n___________________";
    //     cout << "\nFirstName   : " << GetFirstName();
    //     cout << "\nLastName    : " << GetLastName();
    //     cout << "\nFull Name   : " << FullName();
    //     cout << "\nEmail       : " << GetEmail();
    //     cout << "\nPhone       : " << Phone();
    //     cout << "\nAcc. Number : " << _AccountNumber;
    //     cout << "\nPassword    : " << _PinCode;
    //     cout << "\nBalance     : " << _AccountBalance;
    //     cout << "\n___________________\n\n";

    // }

    static clsBankClient Find(string AccountNumber) {
        fstream MyFile;
        MyFile.open(ClientsFileName, ios::in);
        if (MyFile.is_open()) {
            string Line;
            while (getline(MyFile, Line)) {
                if (Line.empty())
                    continue;
                clsBankClient Client = _ConvertLineToClientObject(Line);
                if (Client.AccountNumber() == AccountNumber)
                {
                    MyFile.close();
                    return Client;
                }
            }
            MyFile.close();
        }
        return _GetEmptyClientObject();
    }


    static clsBankClient Find(string AccountNumber, string PinCode) {
        fstream MyFile;
        MyFile.open(ClientsFileName, ios::in);
        if (MyFile.is_open()) {
            string Line;
            while (getline(MyFile, Line)) {
                clsBankClient Client = _ConvertLineToClientObject(Line);
                if (Client.AccountNumber() == AccountNumber && Client.GetPinCode() == PinCode)
                {
                    MyFile.close();
                    return Client;
                }
            }
            MyFile.close();
        }
        return _GetEmptyClientObject();
    }

    static bool IsClientExist(string AccountNumber) {
        clsBankClient Client = Find(AccountNumber);
        return (!Client.IsEmpty());
    }

    enum enSaveResults { svFaildEmptyObject = 0, svSucceeded = 1, svFaildAccountNumberExists = 2 };
    enSaveResults Save()
    {
        switch (this->_Mode)
        {
        case enMode::EmptyMode:
        {
            return enSaveResults::svFaildEmptyObject;
        }

        case enMode::UpdateMode:
        {
            _Update();
            return enSaveResults::svSucceeded;
        }

        case enMode::AddNewMode:
        {
            if (clsBankClient::IsClientExist(_AccountNumber)) {
                return enSaveResults::svFaildAccountNumberExists;

            }
            else {
                _AddNew();
                _Mode = enMode::UpdateMode;
                return enSaveResults::svSucceeded;
            }

        }
        }

    }

    static clsBankClient GetAddNewClientObject(string AccountNumber) {
        return clsBankClient(enMode::AddNewMode, "", "", "", "", AccountNumber, "", 0);
    }

    bool Delete() {
        vector <clsBankClient> _vClients = _LoadClientsDataFromFile();
        for (clsBankClient& C : _vClients) {
            if (C.AccountNumber() == _AccountNumber) {
                C._MarkForDelete = true;
                break;
            }
        }
        _SaveClientsDataToFile(_vClients);
        *this = _GetEmptyClientObject();
        return true;
    }

    static vector <clsBankClient> GetClientsList()
    {
        return _LoadClientsDataFromFile();
    };

    static double GetTotalBalances() {
        vector <clsBankClient> vClients = GetClientsList();
        double TotalBalances = 0;

        for (clsBankClient& C : vClients) {
            TotalBalances += C.GetAccountBalance();
        }
        return TotalBalances;
    };

    void Deposit(double Amount)
    {
        _AccountBalance += Amount;
        Save();
    }

    bool Withdraw(double Amount)
    {
        if (Amount <= _AccountBalance)
        {
            _AccountBalance -= Amount;
            Save();
            return true;
        }
        else
        {
            return false;
        }
    }


    bool Transfer(double Amount, clsBankClient& DestinationClient)
    {
        // bool Result = this->Withdraw(Amount);
        // if (Result)
        //     DestinationClient.Deposit(Amount);
        // return Result;

        if (!this->Withdraw(Amount))
            return false;
        DestinationClient.Deposit(Amount);
        this->_RegisterTransferLog(Amount, DestinationClient);
        return true;
    }

    static vector<stTransferLogRecord> LoadTransferLogRecords()
    {
        vector<stTransferLogRecord> vTransferLogRecords;
        fstream MyFile;
        MyFile.open(TransferLogFile,ios::in);
        if(MyFile.is_open())
        {
            string Line;
            while(getline(MyFile,Line))
            {
                vTransferLogRecords.push_back(_ConvertTransferLogLineToStruct(Line));
            }
            MyFile.close();
        }
        return vTransferLogRecords;
    }
};