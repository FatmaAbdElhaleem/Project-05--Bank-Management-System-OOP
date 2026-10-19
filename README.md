# OOP Bank Management System (C++)

## 📌 Overview

This project is part of Programming Advices **Course 11**, rebuilding the procedural Bank Management System originally developed in Courses 7 & 8 using Object-Oriented Programming (**OOP**).

The project is developed in phases to practice and apply core **OOP principles while improving code organization, reusability, and maintainability**.      

  

  
---
## 🚀 Features

### 🔐 Authentication & Authorization

- User Login and Logout
- Login History Logging
- Permission-Based Access Control

### 👥 User Management

- List All Users
- Add New User
- Delete User
- Update User Information
- Find User

### 👤 Client Management

- List All Clients
- Add New Client
- Delete Client
- Update Client Information
- Find Client by Account Number

### 💰 Banking Transactions

- Deposit Money
- Withdraw Money with Balance Validation
- Display Total Balances
- Transfer Money Between Clients
- Transfer History Log

### 💾 Data Persistence

- File-Based Data Storage
- Client and User Records
- Login and **Transfer History Logs**

---
## 📂 Project Structure

```text
OOP-BankSystem/
├── Data/
│   ├── Clients.txt
│   ├── Users.txt
│   ├── LoginHistory.txt
│   └── TransferHistory.txt
├── HeaderFiles/
│   ├── Core/
│   │   ├── clsBankClient.h
│   │   ├── clsPerson.h
│   │   └── clsUser.h
│   ├── Lib/
│   │   ├── clsDate.h
│   │   ├── clsInputValidate.h
│   │   ├── clsString.h
│   │   ├── clsUtil.h
│   │   └── Global.h
│   └── Screens/
│       ├── ClientMainMenu/
│       │   ├── clsScreen.h
│       │   ├── clsClientListScreen.h
│       │   ├── clsAddNewClientScreen.h
│       │   ├── clsDeleteClientScreen.h
│       │   ├── clsUpdateClientScreen.h
│       │   ├── clsFindClientScreen.h
│       │   └── clsMainScreen.h
│       ├── ClientTransactionsMenue/
│       │   ├── clsDepositScreen.h
│       │   ├── clsWithdrawScreen.h
│       │   ├── clsTotalBalancesScreen.h
│       │   ├── clsTransferScreen.h
│       │   ├── clsTransferLogScreen.h
│       │   └── clsTransactionsScreen.h
│       ├── Login/
│       │   ├── clsLoginRegisterScreen.h
│       │   └── clsLoginScreen.h
│       └── UsersMenue/
│           ├── clsListUsersScreen.h
│           ├── clsAddNewUserScreen.h
│           ├── clsDeleteUserScreen.h
│           ├── clsUpdateUserScreen.h
│           ├── clsFindUserScreen.h
│           └── clsManageUsersScreen.h
└── main.cpp
```


  
---
## 🏗️ Design & Architecture

The project is organized into directories based on responsibility:

- **`Core`**: Contains the main domain classes, including **bank clients, persons, and users**.  
- **`Lib`**: Contains **shared utilities** for date handling, input validation, string operations, and general functionality.  
- **`Screens`**: Organizes the console **interface** into client management, banking transactions, authentication, and user management.  
- **`Data`**: **Stores** client records, user records, login history, and transfer history.  
- **`main.cpp`**: Serves as the application's **entry point**.  

This structure promotes **modularity**, **separation** of responsibilities, and code **maintainability**.  


---
## 💡 Key Learning Outcomes

- Applying the **four** main OOP principles.
- Designing and organizing **reusable** C++ classes.
- Separating **business** entities, **interface** screens, and **shared utilities**.
- Implementing file-based data persistence and transaction logging.
- Building a modular console application with client and user management features.





