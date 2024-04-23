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

	if (helperMethods::userExists(number)) {
		return helperMethods::loadInformation(number);
	}
	else {
		system("cls");
		cout << "Could not find user with account number " << number << endl;
		helperMethods::printManagerChoices(this);
	}
	return nullptr;
}

void managerAccount::managerPrintUserChoices(userAccount* ua) {
	cout << "Welcome " << ua->getUsername() << "!" << endl;
	cout << "Please choose one of the following: " << endl;
	cout << "1. Print Account Summary" << endl;
	cout << "2. Withdraw" << endl;
	cout << "3. Deposit" << endl;
	cout << "4. Back" << endl;
	cout << "5. Delete Account" << endl;

	int selected;
	try {
		cin >> selected;
	}
	catch (exception e) {
		cout << "Invalid input!" << endl;
		managerPrintUserChoices(ua);
	}
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
		try {

			cin >> amount;
			ua->Withdraw(amount);
		}
		catch(exception e){
			cout << "Invalid input!" << endl;
		}
		managerPrintUserChoices(ua);
		break;
	case 3:
		system("cls");
		cout << "How much would you like to deposit?" << endl;
		try {
			cin >> amount;
			ua->Deposit(amount);

			system("cls");
		}
		catch (exception e) {
			cout << "Invalid input!" << endl;
		}
		managerPrintUserChoices(ua);
		break;
	case 4:
		back();
		break;
	case 5:
		char choice;
		cout << "Are you sure you want to delete this account? Y/N" << endl;
		cin >> choice;
		if (toupper(choice) == 'Y') {
			helperMethods::deleteAccount(ua);
			helperMethods::printManagerChoices(this);
		}
		break;
	default:
		cout << "Invalid selection" << endl;
		managerPrintUserChoices(ua);
		break;
	}
}

void managerAccount::back() {
	system("cls");
	helperMethods::printManagerChoices(this);
}