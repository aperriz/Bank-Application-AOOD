#include <string>
#include "account.h"
#pragma once
using namespace std;

class userAccount : public account
{
public:
	userAccount(string user, string pass, string accountType, int accountNumber);
	userAccount();
	~userAccount();
	float getBalance();
	void PrintAccountSummary();
	void Deposit(int amount);
	void Withdraw(int amount);
	userAccount& operator=(account* other);
	
private:
	float balance;
	
};

