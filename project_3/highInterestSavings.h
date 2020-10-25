#include <iostream>
#include "savingsAccount.h"

#ifndef SA_TEST
#define SA_TEST
class highInterestSavings : public savingsAccount {
public:
	//Parameters: accountType, accountName, accountBalance, interestRate, minimumBalance,
	//balanceFee
	highInterestSavings(accountType = hIC, std::string = "anonymous", double = 0.0, double = 0.0,
		double = 0.0, double = 0.0, bool = false);
	
	double getMinimumBalance() const;
	double getBalanceFee() const;
	bool getFeeInvoked() const;

	double withdraw(double) override;
	void info() const override;
private:
	double minimumBalance;
	double balanceFee;
	bool feeInvoked;
};

highInterestSavings::highInterestSavings(accountType t, std::string name, double balance, 
		double rate, double minBal, double fee, bool feeInv)
		: savingsAccount(t, name, balance, rate) {
	fixSign(minBal);
	fixSign(fee);
	minimumBalance = minBal;
	balanceFee = fee;
	feeInvoked = feeInv;
}

double highInterestSavings::getMinimumBalance() const {
	return minimumBalance;
}

double highInterestSavings::getBalanceFee() const {
	return balanceFee;
}

bool highInterestSavings::getFeeInvoked() const {
	return feeInvoked;
}

//Returns -1 if the account does not have enough money.
//Otherwise returns the balance after withdrawal.
double highInterestSavings::withdraw(double amount) {
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
void highInterestSavings::info() const {
	savingsAccount::info();
	std::cout << "Minimum Balance: $" << minimumBalance << std::endl;
	std::cout << "Minimum Balance Fee: $" << balanceFee << std::endl;
	std::string temp = (feeInvoked) ? "Yes" : "No"; 
	std::cout << "Fee Invoked: " << temp << std::endl;
}
#endif
