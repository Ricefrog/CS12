#include <iostream>
#include "noServiceChargeChecking.h"

#ifndef NSCC_TEST
#define NSCC_TEST
class highInterestChecking : public noServiceChargeChecking {
public:
	//Parameters: accountName, accountBalance, interestRate, minimumBalance,
	//balanceFee
	highInterestChecking(accountType = hIC, std::string = "anonymous", double = 0.0, 
			double = 0.0, double = 0.0, double = 0.0, bool = false);
};

highInterestChecking::highInterestChecking(accountType t, std::string name, 
	double balance, double rate, double minBal, double fee, bool feeInv) :
	noServiceChargeChecking(t, name, balance, rate, minBal, fee, feeInv) {};
#endif
