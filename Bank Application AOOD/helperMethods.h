#pragma once
class helperMethods {
public:
	static void deleteAccount(userAccount ua);
	static bool writeFile(userAccount ua);
	static bool userExists(string user, string pass, string mode);
	static userAccount* loadInformation(string username, string password);
};