#include "MainClass.h"
#include <iostream>
#include <string>
#include <fstream>
#include "managerAccount.h"
#include "userAccount.h"
#include "helperMethods.h"
using namespace std;


userAccount* userLogin(string username, string password);
void static createAccount(string username, string password, string accountType, int accountNumber);
void printUserChoices(userAccount* ua);
void getLogin();
int printLoginOptions();
void createAccountDialog();
void createMangagerDialog();
userAccount* loggedInAccount;
userAccount* accountList;

int accounts;

void MainClass::run() {
	accounts = 0;
	//cout << "Main" << endl;
	//Counts number of sets of 5 lines in file; 1 for each account
	ifstream inputFile("users.txt");
	string curLine;

	if (inputFile.is_open()) {
		//cout << "file open" << endl;
		int i = 0;
		int uIndex = 0;
		while (getline(inputFile, curLine)) {
			string user = curLine;
			getline(inputFile, curLine);
			string pass = curLine;
			getline(inputFile, curLine);
			string accType = curLine;
			getline(inputFile, curLine);
			int accNum = stoi(curLine);
			accountList[accounts] = new account(user, pass, accType, accNum);
			accounts++;
		}
	}
	inputFile.close();
	cout << "Welcome!" << endl;
	cout << "Number of accounts in the system: " << accounts << endl;

	switch (printLoginOptions()) {
	case 1:
		system("cls");
		getLogin();
		break;
	case 2:
		system("cls");
		createAccountDialog();
		break;
	case 3:
		system("cls");
		createMangagerDialog();
		break;
	case 4:
		exit(0);
		break;
	default:
		system("cls");
		cout << "Invalid selection" << endl;
		run();
		break;
	}

}

void createAccountDialog() {
	cout << "Create new account" << endl;

	string user, pass;
	cout << "Username: ";
	cin >> user;
	cout << "Password: ";
	cin >> pass;

	//Reads file and compares every 5th line to the username

	bool exists = helperMethods::userExists(user, pass, "create");
	if (!exists && user != "" && pass != "") {
		//Creates new account
		createAccount(user, pass, "customer", accounts + 1);
		userAccount* ua = userLogin(user, pass);
		printUserChoices(ua);
	}
	else if (exists) {
		cout << "Account with username " << user << " already exists" << endl;
		createAccountDialog();
	}

}
void createMangagerDialog() {
	string user, pass;
	cout << "Username: ";
	cin >> user;
	cout << "Password: ";
	cin >> pass;

	if (helperMethods::managerExists(user, pass, "login")) {
		//Clears console and prints choices
		system("cls");
		//printUserChoices(userLogin(user, pass));
		cout << "Welcome manager " << user << endl;
		managerAccount* mgrAcc = new managerAccount();
		helperMethods::printManagerChoices(mgrAcc);
	}
	else {
		//Clears console and prompts new input
		//system("cls");
		cout << "Incorrect username or password!" << endl;
		createMangagerDialog();
	}
}
void static createAccount(string username, string password, string accountType, int accountNumber) {
	userAccount* ua = new userAccount(username, password, accountType, accountNumber);
	//Attempts to write user to file. If works, prints user created
	if (helperMethods::writeFile(*ua)) {
		cout << "User created!" << endl;
		accounts++;
	}
}

void getLogin() {
	string user, pass;
	cout << "Username: ";
	cin >> user;
	cout << "Password: ";
	cin >> pass;

	if (helperMethods::userExists(user, pass, "login")) {
		//Clears console and prints choices
		system("cls");
		printUserChoices(userLogin(user, pass));
	}
	else {
		//Clears console and prompts new input
		system("cls");
		cout << "Incorrect username or password!" << endl;
		getLogin();
	}

}

void printUserChoices(userAccount* ua) {
	cout << "Welcome " << ua->getUsername() << "!" << endl;
	cout << "Please choose one of the following: " << endl;
	cout << "1. Print Account Summary" << endl;
	cout << "2. Withdraw" << endl;
	cout << "3. Deposit" << endl;
	cout << "4. Log out" << endl;

	int selected;
	cin >> selected;
	switch (selected) {
	case 1:
		system("cls");
		ua->PrintAccountSummary();
		printUserChoices(ua);
		break;
	case 2:
		system("cls");
		cout << "How much would you like to withdraw?" << endl;
		int amount;
		cin >> amount;
		ua->Withdraw(amount);
		printUserChoices(ua);
		break;
	case 3:
		system("cls");
		cout << "How much would you like to deposit?" << endl;
		cin >> amount;
		ua->Deposit(amount);
		system("cls");
		printUserChoices(ua);
		break;
	case 4:
		MainClass::logOut();
		break;

	default:
		cout << "Invalid selection" << endl;
		break;
	}


}

int printLoginOptions() {
	int choice;
	cout << "Please choose one of the below:" << endl;
	cout << "1. User Login" << endl;
	cout << "2. Create Account" << endl;
	cout << "3. Manager Login" << endl;
	cout << "4. Exit" << endl;
	cin >> choice;
	return choice;
}

void MainClass::logOut() {
	delete loggedInAccount;
	system("cls");
	cout << "Welcome!" << endl;
	cout << "Number of accounts in the system: " << accounts << endl;

	switch (printLoginOptions()) {
	case 1:
		system("cls");
		getLogin();
		break;
	case 2:
		system("cls");
		createAccountDialog();
		break;
	case 3:
		system("cls");
		createMangagerDialog();
		break;
	case 4:
		exit(0);
		break;
	default:
		cout << "Invalid selection" << endl;
		break;
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
				//Loads user information
				return helperMethods::loadInformation(username, password);
			}
		}

		cout << "User not found!" << endl;
	}
	else {
		cout << "Could not read users.txt" << endl;
	}
	return NULL;

}
