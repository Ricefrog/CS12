#include <iostream>
#include "parsingEtc.h"
#include "bankAccount.h"
#include "serviceChargeChecking.h"
#include "noServiceChargeChecking.h"
#include "highInterestChecking.h"
#include "savingsAccount.h"
#include "highInterestSavings.h"
#include "certificateOfDeposit.h"

#define enemyBal 13000
int monthOffset = 0;
bool nameChangeNotification = false;
int main() {
	serviceChargeChecking init1(sCC, "Talos", enemyBal, sCCCheckLimit,
			0, sCCServiceCharge);
	noServiceChargeChecking init2(nSCC, "Agia", enemyBal, nSCCInterestRate,
			nSCCMinBalance, nSCCMinBalanceFee, false);
	highInterestChecking init3(hIC, "Agilus", enemyBal, hICInterestRate,
			hICMinBalance, hICMinBalanceFee, false);
	certificateOfDeposit init4(cOD, "Baldanders", enemyBal, cODInterestRate,
			cODMaturityMonths, 0);
	savingsAccount init5(sA, "Alzabo", enemyBal, sAInterestRate);
	highInterestSavings init6(hIS, "Cacogen_3", enemyBal, hISInterestRate,
			hISMinBalance, hISMinBalanceFee, false);
	bankAccount *rootAccount = &init1;
	/*
		userAccount = new serviceChargeChecking(userAccType, userName, 
					15000, sCCCheckLimit, 0, sCCServiceCharge);
		userAccount = new noServiceChargeChecking(userAccType, userName,
					15000, nSCCInterestRate, nSCCMinBalance, nSCCMinBalanceFee,
					false);
		userAccount = new highInterestChecking(userAccType, userName,
					15000, hICInterestRate, hICMinBalance, 
					hICMinBalanceFee, false);
		userAccount = new certificateOfDeposit(userAccType, userName, 
					15000, cODInterestRate, cODMaturityMonths, 
					0);
		userAccount = new savingsAccount(userAccType, userName, 
					15000, sAInterestRate);
		userAccount = new highInterestSavings(userAccType, userName,
					15000, hISInterestRate, hISMinBalance, 
					hISMinBalanceFee, false);
					*/
	saveData(rootAccount);
	return 0;
}
