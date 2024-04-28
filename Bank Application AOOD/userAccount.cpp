#include "userAccount.h"
#include <string>
#include <iostream>
#include <fstream>
using namespace std;

userAccount::userAccount() : account("", "", "", NULL) {

}

userAccount::userAccount(string user, string pass, string accountType, int accountNumber) : 
	account(user ,pass, accountType, accountNumber)
{
	balance = 0;
}

userAccount::~userAccount() {
	cout << "User object deleted!" << endl;
}

float userAccount::getBalance() {
	return balance;
}

void userAccount::PrintAccountSummary() {
	//creates or reads text file
	string fileName = getUsername() + ".txt";
	ifstream inputFile(fileName);
	string curLine;
	string temp;
	int index = 0;
	getline(inputFile, curLine);
	do {
		if (curLine != "") {
			cout << curLine << endl;
			temp = curLine;
			index++;
		}
		else {
			if (index == 0) {
				//if first line still
				cout << "No account summary available!" << endl;
			}
		}
	} while (getline(inputFile, curLine));
	if (index != 0) {
		cout << "Balance: $" << temp << endl;
	}
	cout << "Enter any key to return" << endl;
	string tString;
	cin >> tString;
	system("cls");
}

void userAccount::Deposit(int amount) {
	string fileName = getUsername() + ".txt";
	ifstream inputFile(fileName);
	string curLine;
	string temp;
	int index = 0;
	int balance = 0;
	getline(inputFile, curLine);
	do {
		if (curLine != "") {
			index++;
		}
		temp = curLine;

	} while (getline(inputFile, curLine));

	if (index > 0) {
		balance = stoi(temp) + amount;

	}
	else {
		balance = amount;
	}

	inputFile.close();
	ofstream outputFile(fileName, ofstream::app);
	if (outputFile.is_open()) {


		outputFile << "+" << amount << endl;
		outputFile << balance << endl;

	}

	outputFile.close();
}

void userAccount::Withdraw(int amount) {
	string fileName = getUsername() + ".txt";
	ifstream inputFile(fileName);
	string curLine;
	string temp;


	int index = 0;
	int balance = 0;


	getline(inputFile, curLine);
	do {
		if (curLine != "") {
			index++;
		}
		temp = curLine;

	} while (getline(inputFile, curLine));

	if (index > 0) {
		balance = stoi(temp);

	}
	if (balance >= amount) {
		balance = balance - amount;
		inputFile.close();

		ofstream outputFile(fileName, ofstream::app);
		if (outputFile.is_open()) {

			outputFile << "-" << amount << endl;
			outputFile << balance << endl;

		}

		outputFile.close();
	}
	else {
		cout << "Error insufficient funds" << endl;
	}
	string tString;
	cout << "Enter any key to continue..." << endl;
	cin >> tString;
	system("cls");
}

userAccount& userAccount::operator=(account* other)
{
	userAccount newAcc(other->getUsername(), other->getPassword(), other->getAccountType(), other->getAccountNumber());

	return newAcc;
}