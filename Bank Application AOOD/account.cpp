#include "account.h"
account::account() {
	userName = "";
	password = "";
}

string account::getUsername() {
	return userName;
}

account::account(string user, string pass, string accType, int accNum) {
	userName = user;
	password = pass;
	accountType = accType;
	accountNumber = accNum;
}

account::~account() {

}

string account::getPassword() {
	return password;
}

string account::getAccountType() {
	return accountType;
}

int account::getAccountNumber() {
	return accountNumber;
}

void account::setUsername(string n) {
	userName = n;
}

void account::setPassword(string n) {
	password = n;
}
void account::setAccountType(string n) {
	accountType = n;
}

void account::setAccountNumber(int n) {
	accountNumber = n;
}