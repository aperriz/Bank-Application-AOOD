#include <iostream>
#include <string>
#include <fstream>
#include "managerAccount.h"
#include "userAccount.h"
#include "helperMethods.cpp"
using namespace std;

void static createAccount(string username, string password, string accountType, int accountNumber);
userAccount* userLogin(string username, string password);
void printUserChoices(userAccount* ua);
void getLogin();
int printLoginOptions();
void createAccountDialog();
userAccount loggedInAccount;

static int accounts = 0;

void main() {
	//cout << "Main" << endl;
	//Counts number of sets of 5 lines in file; 1 for each account
	ifstream inputFile("users.txt");
	string curLine;

	if (inputFile.is_open()) {
		//cout << "file open" << endl;
		int i = 0;
		int uIndex = 0;
		while (getline(inputFile, curLine)) {
			if (i < 4) {
				i++;
			}
			else {
				i = 0;
				accounts++;
			}
		}
	}
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
	default:
		cout << "Invalid selection" << endl;
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

	bool exists = userExists(user, pass, "create");
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

void static createAccount(string username, string password, string accountType, int accountNumber) {
	userAccount* ua = new userAccount(username, password, accountType, accountNumber);
	//Attempts to write user to file. If works, prints user created
	if (writeFile(*ua)) {
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

	if (userExists(user, pass, "login")) {
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
		cout << "How much would you like to withdraw";
		int amount;
		cin >> amount;
		ua->Withdraw(amount);
		printUserChoices(ua);
		break;
	case 3:
		system("cls");
		cout << "How much would you like to deposit" << endl;
		cin >> amount;
		ua->Deposit(amount);
		printUserChoices(ua);
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
	cin >> choice;
	return choice;
}