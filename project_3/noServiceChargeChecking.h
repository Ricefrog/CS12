#include <iostream>
#include "checkingAccount.h"

#ifndef NS_TEST
#define NS_TEST
class noServiceChargeChecking : public checkingAccount {
public:
	//Parameters: accountType, accountName, accountBalance, interestRate, minimumBalance,
	//balanceFee
	noServiceChargeChecking(accountType = nSCC, std::string = "anonymous", double = 0.0, 
			double = 0.0, double = 0.0, double = 0.0, bool = false);
	
	double getInterestRate() const;
	double getMinimumBalance() const;
	double getBalanceFee() const;
	bool getFeeInvoked() const;

	double withdraw(double) override;
	double writeCheck(double amount, bankAccount *target) override; 
	void info() const override;
private:
	double interestRate;
	double minimumBalance;
	double balanceFee;
	bool feeInvoked;
};

noServiceChargeChecking::noServiceChargeChecking(accountType t, std::string name, 
	double balance, double rate, double minBal, double fee, bool feeInv) :
	checkingAccount(t, name, balance) {
	fixSign(rate);
	fixSign(minBal);
	interestRate = rate;
	minimumBalance = minBal;
	balanceFee = fee;
	feeInvoked = feeInv;
}

double noServiceChargeChecking::getInterestRate() const {
	return interestRate;
}

double noServiceChargeChecking::getMinimumBalance() const {
	return minimumBalance;
}

double noServiceChargeChecking::getBalanceFee() const {
	return balanceFee;
}

bool noServiceChargeChecking::getFeeInvoked() const {
	return feeInvoked;
}

//Returns -1 if the account does not have enough money.
//returns amount sent, add recipient's data and the amount sent to 
//the transaction string.
double noServiceChargeChecking::writeCheck(double amount, bankAccount *target) {
	double myBalance = this->getAccountBalance();
	fixSign(amount);
	if (myBalance - amount <= 0)
		return -1;

	std::string name = target->getAccountName();
	int num = target->getAccountNumber();
	std::string temp = "writeCheck("+name+","+std::to_string(num)
		+","+std::to_string(amount)+")";

	if (myBalance - amount < minimumBalance && !feeInvoked) {
		temp += "feeinvoked("+std::to_string(balanceFee)+","
			+getCurrentTime()+")";
		feeInvoked = true;
	}
	transactions += temp;

	myBalance -= amount;
	this->setAccountBalance(myBalance);
	return target->receive(amount, static_cast<bankAccount*>(this));		
}

//Returns -1 if the account does not have enough money.
//Otherwise returns the balance after withdrawal.
double noServiceChargeChecking::withdraw(double amount) {
	double myBalance = this->getAccountBalance();
	fixSign(amount);
	if (myBalance - amount >= 0) {
		std::string temp = "withdraw("+std::to_string(amount)
			+","+getCurrentTime()+")";
		if (myBalance - amount < minimumBalance && !feeInvoked) {
			temp += "feeinvoked("+std::to_string(balanceFee)+","
				+getCurrentTime()+")";
			feeInvoked = true;
		}
		transactions += temp;
		this->setAccountBalance((myBalance -= amount));
		return myBalance;
	}
	return -1;
}
		
void noServiceChargeChecking::info() const {
	bankAccount::info();
	std::cout << "\nInterest Rate: " << 100*interestRate << "%" << std::endl;
	std::cout << "Minimum Balance: $" << minimumBalance << std::endl;
	std::cout << "Minimum Balance Fee: $" << balanceFee << std::endl;
	std::string temp = (feeInvoked) ? "Yes" : "No"; 
	std::cout << "Fee Invoked: " << temp << std::endl;
}
#endif
