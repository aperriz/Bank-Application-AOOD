#include <string>
#include <iostream>
#include <fstream>
#include "userAccount.h"
#include "helperMethods.h"
using namespace std;

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
bool helperMethods::managerExists(string user, string pass, string mode) {
	//Checks and returns if user exists
	ifstream inputFile("manager.txt");
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
		cout << "Manager " << user << " does not exist!" << endl;
	}
	return false;
}
void helperMethods::deleteAccount(userAccount ua) {
	//array to hold lines to ignore
	string userLines[4] = { ua.getUsername(),
		ua.getPassword(), ua.getAccountType(), to_string(ua.getAccountNumber()) };
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