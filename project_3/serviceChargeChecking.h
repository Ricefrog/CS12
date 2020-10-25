#include <iostream>
#include "checkingAccount.h"

#ifndef SCC_TEST
#define SCC_TEST
class serviceChargeChecking : public checkingAccount {
public:
	//Parameters: accoutnType, accountName, accountBalance, checkLimit, serviceCharge, checksWritten
	serviceChargeChecking(accountType = sCC, std::string = "anonymous", double = 0.0, 
			int = 3, int = 0, double = 0.0);
	
	//getters and setters
	int getCheckLimit() const;
	void setCheckLimit(int);
	int getChecksWritten() const;
	void setChecksWritten(int);
	double getServiceCharge() const;

	double writeCheck(double, bankAccount*) override;
	void info() const override;
private:
	int checkLimit;
	int checksWritten;
	double serviceCharge;
};

serviceChargeChecking::serviceChargeChecking(accountType t, std::string name, double balance,
	int limit, int written, double charge) : checkingAccount(t, name, balance) {
	fixSign(limit);
	checkLimit = limit;
	fixSign(charge);
	serviceCharge = charge;
	fixSign(written);
	checksWritten = written;
}

int serviceChargeChecking::getCheckLimit() const {
	return checkLimit;
}

void serviceChargeChecking::setCheckLimit(int amount) {
	fixSign(amount);
	checkLimit = amount;
}

int serviceChargeChecking::getChecksWritten() const {
	return checksWritten;
}

void serviceChargeChecking::setChecksWritten(int num) {
	fixSign(num);
	checksWritten = num;
}

double serviceChargeChecking::getServiceCharge() const {
	return serviceCharge;
}

//Returns -1 if the account does not have enough money or 
//the target account cannot receive checks.
//Returns -2 if checkLimit has been reached.
//returns amount sent, add recipient's data and the amount sent to 
//the transaction string.
double serviceChargeChecking::writeCheck(double amount, bankAccount *target) {
	double myBalance = this->getAccountBalance();
	fixSign(amount);

	if (checksWritten == checkLimit)
		return -2;
	if (myBalance - amount <= 0)
		return -1;

	double r = target->receive(amount, static_cast<bankAccount*>(this));	
	if (r >= 0) {
		std::string name = target->getAccountName();
		int num = target->getAccountNumber();
		std::string temp = "writeCheck("+name+","+std::to_string(num)
			+","+std::to_string(amount)+")";
		transactions += temp;
	
		myBalance -= amount;
		checksWritten++;
		this->setAccountBalance(myBalance);
	}

	return r;
}

void serviceChargeChecking::info() const {
	bankAccount::info();
	printf("\n");
	std::cout << "Service Charge: $" << serviceCharge << std::endl;
	std::cout << "Check Limit: " << checkLimit << std::endl;
	std::cout << "Checks Written: " << checksWritten << std::endl;
}
#endif
