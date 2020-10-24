#include <iostream>
#include "bankAccount.h"
#ifndef C_TEST
#define C_TEST
class checkingAccount : public bankAccount {
public:
	checkingAccount(accountType, std::string = "anonymous", double = 0.0);
	virtual	double writeCheck(double, bankAccount*) = 0;
};

checkingAccount::checkingAccount(accountType t, std::string name, double balance)
	: bankAccount(t, name, balance){};
#endif
