#pragma once
#include "managerAccount.h"
#include "userAccount.h"
static class helperMethods {
public:
	static void deleteAccount(userAccount ua);
	static bool writeFile(userAccount ua);
	static bool userExists(string user, string pass, string mode);
	static bool managerExists(string user, string pass, string mode);
	static userAccount* loadInformation(string username, string password);
	static void printManagerChoices(managerAccount* mgr);

};