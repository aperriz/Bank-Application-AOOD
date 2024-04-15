#include "managerAccount.h"
#include <iostream>
#include <fstream>
#include "helperMethods.h"
using namespace std;

managerAccount::managerAccount() {
	cout << "Welcome " << getUsername() << endl;
}

managerAccount::~managerAccount() {

}

userAccount* managerAccount::getUserInformation(string username) {
	if (helperMethods::userExists(username, "", "admin")) {
		return helperMethods::loadInformation(username, "");
	}
	else {
		system("cls");
		cout << "Could not find user " << username << endl;
		helperMethods::printManagerChoices(this);
	}
	return nullptr;
}

userAccount* managerAccount::getUserInformation(int number) {


	return nullptr;
}

void managerAccount::managerPrintUserChoices(userAccount* ua) {
	cout << "Welcome " << ua->getUsername() << "!" << endl;
	cout << "Please choose one of the following: " << endl;
	cout << "1. Print Account Summary" << endl;
	cout << "2. Withdraw" << endl;
	cout << "3. Deposit" << endl;
	cout << "4. Back" << endl;

	int selected;
	cin >> selected;
	switch (selected) {
	case 1:
		system("cls");
		ua->PrintAccountSummary();
		managerPrintUserChoices(ua);
		break;
	case 2:
		system("cls");
		cout << "How much would you like to withdraw?" << endl;
		int amount;
		cin >> amount;
		ua->Withdraw(amount);
		managerPrintUserChoices(ua);
		break;
	case 3:
		system("cls");
		cout << "How much would you like to deposit?" << endl;
		cin >> amount;
		ua->Deposit(amount);
		system("cls");
		managerPrintUserChoices(ua);
		break;
	case 4:
		back();
		break;

	default:
		cout << "Invalid selection" << endl;
		break;
	}
}

void managerAccount::back() {
	system("cls");
	helperMethods::printManagerChoices(this);
}