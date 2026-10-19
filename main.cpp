#include <iostream>
#include <iomanip>
#include "HeaderFiles\Lib\clsInputValidate.h"
#include "HeaderFiles\Lib\clsUtil.h"
#include "HeaderFiles\Core\clsBankClient.h"
#include "HeaderFiles\Screens\ClientMainMenue\clsMainScreen.h"
#include "HeaderFiles/Screens/Login/clsLoginScreen.h"
using namespace std;


int main()
{
    // solution 1:
    // bool LoginResult=true;
    // while(LoginResult){
    //    LoginResult =clsLoginScreen::ShowLoginScreen();
    // }

    // solution 2:
    // while(clsLoginScreen::ShowLoginScreen());

    // solution 3:
    while (true) {
        if (!clsLoginScreen::ShowLoginScreen())
            break;
    }
}