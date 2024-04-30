#ifndef ACCOUNT_H
#define ACCOUNT_H
#endif // !ACCOUNT_H
#include <string>
using namespace std;
class account
{
public:
	account(string user, string pass, string accType, int accNum);
	account();
	account(account* other);
	~account();
	string getUsername();
	string getPassword();
	string getAccountType();
	int getAccountNumber();
	void setUsername(string n);
	void setPassword(string n);
	void setAccountType(string n);
	void setAccountNumber(int n);
	static account* loggedInAccount;
private:
	int accountNumber;
	string accountType;
	string userName;
	string password;	
};

