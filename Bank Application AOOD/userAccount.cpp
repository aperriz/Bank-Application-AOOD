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
	balance = 0;
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

void userAccount::PrintAccountSummary() {
	//creates or reads text file
	string fileName = userName + ".txt";
	ifstream inputFile(fileName);
	string curLine;
	int index = 0;
	getline(inputFile, curLine);
	do {
		if (curLine != "") {
			cout << curLine << endl;
			index++;
		}
		else {
			if (index == 0) {
				//if first line still
				cout << "No account summary available!" << endl;
			}
		}
	} while (getline(inputFile, curLine));
	cout << "Balance: $" << getBalance() << endl;
}

void userAccount::Deposit(int amount) {
	string fileName = userName + ".txt";
	ifstream inputFile(fileName);
	string curLine;
	int index = 0;
	int balance = 0;

	getline(inputFile, curLine);
	do {
		if (curLine != "") {
			cout << curLine << endl;
			index++;
		}
		int balance = stoi(curLine);
	} while (getline(inputFile, curLine));
	ofstream outputFile(fileName, ofstream::app);
	if (outputFile.is_open()) {
		outputFile << amount << endl;
		outputFile << balance + amount << endl;
	}
}
void userAccount::Withdraw(int amount) {
	string fileName = userName + ".txt";
	ifstream inputFile(fileName);
	string curLine;
	int index = 0;
	int balance = 0;

	getline(inputFile, curLine);
	do {
		if (curLine != "") {
			cout << curLine << endl;
			index++;
		}
		int balance = stoi(curLine);
	} while (getline(inputFile, curLine));
	if (balance >= amount) {
		ofstream outputFile(fileName, ofstream::app);
		if (outputFile.is_open()) {
			outputFile << "-" + amount << endl;
			outputFile << balance - amount << endl;
		}
	}
	else {
		cout << "Error: insufficient funds" << endl;
	}
}