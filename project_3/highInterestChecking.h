#include <iostream>
#include "noServiceChargeChecking.h"


class highInterestChecking : public noServiceChargeChecking {
public:
	//Parameters: accountName, accountBalance, interestRate, minimumBalance,
	//balanceFee
	highInterestChecking(accountType = hIC, std::string = "anonymous", double = 0.0, 
			double = 0.0, double = 0.0, double = 0.0);
};

highInterestChecking::highInterestChecking(accountType t, std::string name, 
	double balance, double rate, double minBal, double fee) :
	noServiceChargeChecking(t, name, balance, rate, minBal, fee) {};
