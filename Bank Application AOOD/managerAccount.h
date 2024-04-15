#pragma once
#include "userAccount.h"
class managerAccount :
    public account
{
public:
    managerAccount();
    ~managerAccount();
    userAccount* getUserInformation(string username);
    userAccount* getUserInformation(int number);
    void managerPrintUserChoices(userAccount* ua);
private:
    void back();
};

