#include <iostream>
#include <string>
#include <fstream>
#include "managerAccount.h"
#include "userAccount.h"
using namespace std;

void static createAccount(string username, string password, string accountType, int accountNumber);
userAccount* loadInformation(string username, string password);
userAccount* userLogin(string username, string password);
void deleteAccount(userAccount ua);
bool writeFile(userAccount ua);
void printUserChoices(userAccount* ua);
void getLogin();
int printLoginOptions();
void createAccountDialog();
bool userExists(string user, string pass, string mode);
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
	case 2:
		system("cls");
		createAccountDialog();
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
	if (!exists &&  user != "" && pass != "") {
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
		if (userLogin(user, pass) != nullptr) {
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
}

void printUserChoices(userAccount* ua) {
	cout << "Welcome " << ua->getUsername() << "!" << endl;
	cout << "Please choose one of the following: " << endl;
	cout << "1. Print Account Summary" << endl;
	cout << "2. Withdraw" << endl;
	cout << "3. Deposit" << endl;
	cout << "4. Balance" << endl;
	int selected;
	cin >> selected;
	

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
				return loadInformation(username,password);
			}
		}

		cout << "User not found!" << endl;
	}
	else {
		cout << "Could not read users.txt" << endl;
	}
	return NULL;
	
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

bool writeFile(userAccount ua) {
	ofstream outputFile("users.txt", ios::app);
	//Checks if file is open
	if (outputFile.is_open()) {
		outputFile << ua.getUsername() << endl
			<< ua.getPassword() << endl
			<< ua.getAccountType() << endl
			<< ua.getAccountNumber() << endl;
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

userAccount* loadInformation(string username, string password)
{
	ifstream inputFile("users.txt");
	string curLine;
	//Attempts to read file line-by-line, seeing if the username from the object is in the file
	if (inputFile.is_open()) {
		while (getline(inputFile, curLine)) {
			if (curLine == username) {
				//skips password line
				getline(inputFile, curLine);
				//Reads the rest of the attributes
				getline(inputFile, curLine);
				string type = curLine;
				//cout << "Account Type: " << curLine;
				getline(inputFile, curLine);
				int number = stoi(curLine);
				//cout << "Account Number: " << curLine;
				getline(inputFile, curLine);
				//returns new userAccount with properties found in file
				return new userAccount(username, password, type, number);
			}
		}
		//if user is not found in file
		cout << "User not found!" << endl;
		inputFile.close();
	}
	else {
		cout << "Could not read users.txt!" << endl;
	}
	return nullptr;	

}

void deleteAccount(userAccount ua) {
	//array to hold lines to ignore
	string userLines[4] = {ua.getUsername(), 
		ua.getPassword(), ua.getAccountType(), to_string(ua.getAccountNumber())};
	string curLine;
	//creates temporary file, ignoring any lines found in userLines array
	ifstream inputFile("users.txt");
	ofstream tempFile("temp.txt");
	curLine = "";
	if (inputFile.is_open() && tempFile.is_open()) {
		while (getline(inputFile, curLine)) {
			bool found = false;
			for (string s : userLines) {
				found = true;
			}

			if (!found) {
				tempFile << curLine << endl;
			}
		}
	}
	//Frees userLines and closes files
	delete userLines;
	tempFile.close();
	inputFile.close();
	//Copies temporary file to users file, deleting the account in the process
	ofstream outputFile("users.txt");
	ifstream temp("temp.txt");
	curLine = "";
	if (outputFile.is_open() && tempFile.is_open()) {
		while (getline(temp, curLine)) {
			outputFile << curLine << endl;
		}
	}
	outputFile.close();
	temp.close();
	//Deletes temp file
	remove("temp.txt");
}

bool userExists(string user, string pass, string mode) {
	//Checks and returns if user exists
	ifstream inputFile("users.txt");
	string curLine;
	if (inputFile.is_open()) {
		int i = 0;
		while (getline(inputFile, curLine)) {
			if (i == 3) {
				i = 0;
			}
			else if (i == 0) {
				//cout << curLine << endl;
				if (curLine == user) {
					//If in login mode, checks password
					if (mode == "login") {
						getline(inputFile, curLine);
						if (curLine == pass) {
							return true;
						}
						else {
							cout << "Incorrect password!" << endl;
							return false;
						}
					}
					else {
						return true;
					}
				}
				i++;
			}
			else {
				i++;
			}
		}
	}
	inputFile.close();
	if (mode == "login") {
		cout << "User " << user << " does not exist!" << endl;
	}
	return false;
}