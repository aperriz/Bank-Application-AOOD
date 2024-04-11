#include <string>
#include "account.h"
#pragma once
using namespace std;

class userAccount : account
{
public:
	userAccount(string user, string pass, string accountType, int accountNumber);
	userAccount();
	~userAccount();
	string getUsername();
	string getPassword();
	string getAccountType();
	int getAccountNumber();
	float getBalance();
	void PrintAccountSummary();
	void Deposit(int amount);
	void Withdraw(int amount);
	
private:
	float balance;
	
};

