#include <iostream>
#include <string>
#include <fstream>
#include "managerAccount.h"
#include "userAccount.h"
using namespace std;

void createAccount(string username, string password, string accountType, int accountNumber, int balance);
void loadInformation(userAccount ua);
userAccount* userLogin(string username, string password);
void deleteAccount(string username, string password);
void deleteAccount(int accountNum);
bool writeFile(userAccount* ua);
userAccount logedInAccount;

void main() {


}

void createAccount(string username, string password, string accountType, int accountNumber, int balance) {
	userAccount* ua = new userAccount(username, password, accountType, accountNumber, balance);
	//Attempts to write user to file. If works, prints user created
	if (writeFile(ua)) {
		cout << "User created!" << endl;
	}
}

userAccount* userLogin(string username, string password) {
	ifstream inputFile("users.txt");
	string curLine;
	userAccount* tempUA;
	//reads file looking for username
	if (inputFile.is_open()) {
		while (getline(inputFile, curLine)) {
			if (curLine == username) {
				getline(inputFile, curLine);
			}
			if (curLine == password) {
				return;
			}
		}

		cout << "User not found!" << endl;
	}
	else {
		cout << "Could not read users.txt" << endl;
	}
	return tempUA;
}

bool writeFile(userAccount ua) {
	ofstream outputFile("users.txt", ios::app);
	//Checks if file is open
	if (outputFile.is_open()) {
		outputFile << ua.getUsername() << endl
			<< ua.getPassword() << endl
			<< ua.getAccountType() << endl
			<< ua.getAccountNumber() << endl
			<< ua.getBalance() << endl;
		return true;
	}
	else {
		//Returns false if unable to write to file
		cout << "Error writing to file!" << endl;
		return false;
	}
	//Default returns false
	return false;
}

void loadInformation(userAccount ua) {
	ifstream inputFile("users.txt");
	string curLine;
	//Attempts to read file line-by-line, seeing if the username from the object is in the file
	if (inputFile.is_open()) {
		while (getline(inputFile, curLine)) {
			if (curLine == ua.getUsername()) {
				//skips password line
				getline(inputFile, curLine);
				//Reads the rest of the attributes, then terminates function
				getline(inputFile, curLine);
				cout << "Account Type: " << curLine;
				getline(inputFile, curLine);
				cout << "Account Number: " << curLine;
				getline(inputFile, curLine);
				cout << "Balance: $" << curLine;

				return;
			}
		}
		//if user is not found in file
		cout << "User not found!" << endl;
		inputFile.close();
	}
	else {
		cout << "Could not read users.txt!" << endl;
	}

}