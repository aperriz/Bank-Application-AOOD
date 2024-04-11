#pragma once
#include "userAccount.h"
class managerAccount :
    public userAccount
{
public:
    managerAccount();
    ~managerAccount();
    void getUserInformation(string username);
    void getUserInformation(int number);
};

