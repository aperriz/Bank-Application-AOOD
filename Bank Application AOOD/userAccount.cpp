#include "userAccount.h"
#include <string>
#include <iostream>
#include <fstream>
using namespace std;

userAccount::userAccount() {

}

userAccount::userAccount(string user, string pass, string accountType, int accountNumber) {
	userName = user;
	password = pass;
	this->accountNumber = accountNumber;
	this->accountType = accountType;
}

userAccount::~userAccount() {
	cout << "User object deleted!" << endl;
}

string userAccount::getUsername() {
	return userName;
}

string userAccount::getPassword() {
	return password;
}

string userAccount::getAccountType() {
	return accountType;
}

int userAccount::getAccountNumber() {
	return accountNumber;
}

float userAccount::getBalance() {
	return balance;
}