#include <iostream>
#include "bankAccount.h"

class savingsAccount : public bankAccount {
public:
	//name, initial balance, interest rate
	savingsAccount(std::string = "Anonymous", double = 0.0, double = 0.0);

	void setInterestRate(double);
	double getInterestRate() const;
	//Returns the balance in x number of years, interest is assumed to compound annually
	double interestGains(int) const;
	
	void info() const;
	savingsAccount *next;

	//the withdraw function does not need to be overridden
private:
	double interestRate;
};

savingsAccount::savingsAccount(std::string name, double balance, double rate)
	: bankAccount(name, balance) {
		interestRate = rate;
}

void savingsAccount::setInterestRate(double rate) {
	interestRate = rate;
}

double savingsAccount::getInterestRate() const {
	return interestRate;
}

void savingsAccount::info() const {
	bankAccount::info();	
	printf("Interest Rate: %.2f\%\n", 100 * interestRate);
}
