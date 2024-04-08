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
	
private:
	string userName;
	string password;
	int accountNumber;
	string accountType;
	float balance;
	
};

