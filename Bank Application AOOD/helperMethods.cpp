#include <string>
#include <iostream>
#include <fstream>
#include "userAccount.h"
#include "helperMethods.h"
#include "managerAccount.h"
#include "MainClass.h"
using namespace std;

static void back();

bool helperMethods::userExists(string user, string pass, string mode) {
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
				//If on the username line
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

bool helperMethods::userExists(int accountNum) {
	//Checks and returns if user exists
	ifstream inputFile("users.txt");
	string curLine;
	if (inputFile.is_open()) {
		int i = 0;
		while (getline(inputFile, curLine)) {
			if (i == 3) {
				int an = 0;
				try {
					an = stoi(curLine);
				}
				catch (exception e) {

				}

				if (an == accountNum) {
					return true;
				}

				i = 0;
			}
			else {
				i++;
			}
		}
	}
	inputFile.close();

	return false;
}


bool helperMethods::managerExists(string user, string pass, string mode) {
	//Checks and returns if user exists
	ifstream inputFile("managers.txt");
	string curLine;
	if (inputFile.is_open()) {
		int i = 0;
		while (getline(inputFile, curLine)) {
			if (i == 1) {
				i = 0;
			}
			else if (i == 0) {

				//If on the username line
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
		cout << "Manager " << user << " does not exist!" << endl;
	}
	return false;
}
void helperMethods::deleteAccount(userAccount*
	ua) {
	//array to hold lines to ignore
	string* userLines;
	userLines = new string[4];
	userLines[0] = ua->getUsername();
	userLines[1] = ua->getPassword();
	userLines[2] = ua->getAccountType();
	userLines[3] = to_string(ua->getAccountNumber());

	string curLine;
	//creates temporary file, ignoring any lines found in userLines array
	ifstream inputFile("users.txt");
	ofstream outputFile("temp.txt");
	curLine = "";
	if (inputFile.is_open() && outputFile.is_open()) {
		while (getline(inputFile, curLine)) {
			bool found = false;
			if (curLine == userLines[0]) {
				found == true;
				getline(inputFile, curLine);
				getline(inputFile, curLine);
				getline(inputFile, curLine);
				getline(inputFile, curLine);
			}

			if (!found && curLine != "") {
				outputFile << curLine << endl;
			}
		}
	}
	inputFile.close();
	outputFile.close();
	//Frees userLines and closes files
	//Copies temporary file to users file, deleting the account in the process
	inputFile.open("temp.txt");
	outputFile.open("users.txt");
	curLine = "";
	while (getline(inputFile, curLine)) {
		outputFile << curLine << endl;
	}

	outputFile.close();
	inputFile.close();
	//Deletes temp file
	//remove("temp.txt");
}

bool helperMethods::writeFile(userAccount ua) {
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

userAccount* helperMethods::loadInformation(string username, string password)
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

userAccount* helperMethods::loadInformation(int accNum)
{
	ifstream inputFile("users.txt");
	string curLine;
	//Attempts to read file line-by-line, seeing if the username from the object is in the file
	if (inputFile.is_open()) {
		while (getline(inputFile, curLine)) {
			string username = curLine;
			string pass;
			getline(inputFile, pass);
			string accType;
			getline(inputFile, accType);
			string nLine;
			getline(inputFile, nLine);
			int accNumber = stoi(nLine);

			if (accNumber == accNum) {
				return new userAccount(username, pass, accType, accNum);
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

void helperMethods::printManagerChoices(managerAccount* mgr) {
	cout << "Please choose one of the following: " << endl;
	cout << "1. Access User by Account Number" << endl;
	cout << "2. Access User by Account Name" << endl;
	cout << "3. Log out" << endl;
	int selection;
	try {
		cin >> selection;

		string accName;
		userAccount* ua;

		switch (selection) {
		case 1:
			cout << "Enter the account number:";
			int accNum;
			try {

				cin >> accNum;
				ua = mgr->getUserInformation(accNum);

				if (ua != nullptr) {
					mgr->managerPrintUserChoices(ua);
				}
				else {
					cout << "User not found!" << endl;
					printManagerChoices(mgr);
				}
			}
			catch(exception e) {
				printManagerChoices(mgr);
			}
			break;
		case 2:
			cout << "Enter the account username:";
			cin >> accName;
			ua = mgr->getUserInformation(accName);
			if (ua != nullptr) {
				mgr->managerPrintUserChoices(ua);
			}
			else {
				cout << "User not found!" << endl;
				printManagerChoices(mgr);
			}
			break;
		case 3:
			back();
			break;
		default:
			system("cls");
			cout << "Invalid selection!" << endl;
			printManagerChoices(mgr);
			break;
		}
	}
	catch (exception e) {
		cout << "Invalid input" << endl;
		printManagerChoices(mgr);
	}

}

static void back() {
	MainClass::logOut();
}