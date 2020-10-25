#include <iostream>
#include "bankAccount.h"

#ifndef S_TEST
#define S_TEST
class savingsAccount : public bankAccount {
public:
	//Parameters: accountType, accountName, accountBalance, interestRate
	savingsAccount(accountType = sA, std::string = "anonymous", double = 0.0, double = 0.0);

	double getInterestRate() const;

	void info() const override;
protected:
	double interestRate;
};

savingsAccount::savingsAccount(accountType t, std::string name, double balance, double rate) 
	: bankAccount(t, name, balance) {
		fixSign(rate);
		interestRate = rate;
}

double savingsAccount::getInterestRate() const {
	return interestRate;
}

void savingsAccount::info() const {
	bankAccount::info();
	std::cout << "\nInterest Rate: " << 100*interestRate << "%" << std::endl;
}
#endif
