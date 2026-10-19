#pragma once
#include <string>

const string ClientsFileName = "Data/Clients.txt";
const string UsersFileName = "Data/Users.txt";
const string LoginRegisterFile = "Data/LoginHistory.txt";
const string TransferLogFile = "Data/TransferHistory.txt";

#include "../Core/clsUser.h"
clsUser CurrentUser = clsUser::Find("", "");