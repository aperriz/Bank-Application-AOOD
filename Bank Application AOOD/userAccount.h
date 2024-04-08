#include <string>
#pragma once
using namespace std;

class userAccount
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
	string userName;
	string password;
	int accountNumber;
	string accountType;
	float balance;
	
};

