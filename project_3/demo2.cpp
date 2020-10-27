#include <iostream>
#include "parsingEtc.h"
#include "bankAccount.h"
#include "serviceChargeChecking.h"
#include "noServiceChargeChecking.h"
#include "highInterestChecking.h"
#include "savingsAccount.h"
#include "highInterestSavings.h"
#include "certificateOfDeposit.h"

int monthOffset = 0;
bool nameChangeNotification = false;
int main() {
	char userInput;	
	char temp;
	bankAccount *rootAccount = readData();
	bankAccount *userAccount;
	bankAccount *enemyAccount;
	
	startScreen();
	std::cin >> userInput;
	switch (userInput) {
	case 'n':
		intro();
		break;
	default:
		return quit();
	}

	accountType userAccType =  accountSelectionMenu();
	switch (userAccType) {
	case sCC:
		userAccount = new serviceChargeChecking(userAccType, userName, 
					15000, sCCCheckLimit, 0, sCCServiceCharge);
		break;
	case nSCC:
		userAccount = new noServiceChargeChecking(userAccType, userName,
					15000, nSCCInterestRate, nSCCMinBalance, nSCCMinBalanceFee,
					false);
		break;
	case hIC:
		userAccount = new highInterestChecking(userAccType, userName,
					15000, hICInterestRate, hICMinBalance, 
					hICMinBalanceFee, false);
		break;
	case cOD:
		userAccount = new certificateOfDeposit(userAccType, userName, 
					15000, cODInterestRate, cODMaturityMonths, 
					0);
		break;
	case sA:
		userAccount = new savingsAccount(userAccType, userName, 
					15000, sAInterestRate);
		break;
	case hIS:
		userAccount = new highInterestSavings(userAccType, userName,
					15000, hISInterestRate, hISMinBalance, 
					hISMinBalanceFee, false);
	}
	psuedoClear();
	drawBox("Account Info", '&');
	printf("\n\n");
	userAccount->info();
	std::cout << "\n~Continue -> any character\n" << std::endl;
	USER_PROMPT;
	std::cin >> temp;

	int selection;
	int months; 
	while (!allEnemiesDefeated()) {
		months = 0;
		enemyAccount = enemySelectScreen();
		if (enemyAccount->getAccountBalance() < 0) {
			psuedoClear();
			std::cout << "Enemy is already defeated.\n" << std::endl;
			std::cout << "~Continue -> any character\n" << std::endl;
			USER_PROMPT;
			std::cin >> temp;
			std::cin.clear();
		} else {
			std::cin >> temp;
			while (enemyAccount->getAccountBalance() > 0 
					&& userAccount->getAccountBalance() > 0) {
				battleField(userAccount, enemyAccount, months);
				selection = battlePrompt(userAccount);
				months++;
			}
		}
	}
	//printAllInfo(rootAccount);
	//printAllTransactionStr(rootAccount);
	return 0;
}
