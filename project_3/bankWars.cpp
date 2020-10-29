#include <iostream>
#include <vector>
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
	int intTemp;
	bankAccount *rootAccount = readData();
	bankAccount *userAccount;
	bankAccount *enemyAccount;
	certificateOfDeposit *setInitDelay;

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
		setInitDelay = static_cast<certificateOfDeposit*>(userAccount);
		intTemp = setInitDelay->getMaturityMonths();
		setInitDelay->setMonthsDelayed(intTemp);
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
	int enemySelection;
	double userActionValue;
	double enemyActionValue;
	accountType enemyAccType;
	serviceChargeChecking *tempS = static_cast<serviceChargeChecking*>(userAccount);
	//reusing a single vector would cause segfaults for some reason
	std::vector<std::string> records[numberOfEnemies];
	int rIndex = 0;
	while (!allEnemiesDefeated()) {
		std::cout << "entered first while" << std::endl;
		months = 0;
		std::cin.clear();
		enemyAccount = enemySelectScreen();
		enemyAccType = enemyAccount->getAccountType();
		if (enemyAccount->getAccountBalance() <= 0) {
			psuedoClear();
			std::cout << "Enemy is already defeated.\n" << std::endl;
			std::cout << "~Continue -> any character\n" << std::endl;
			USER_PROMPT;
			std::cin >> temp;
			std::cin.clear();
			continue;
		} else {
			std::cin >> temp;
			while (enemyAccount->getAccountBalance() > 0) {
				std::cout << "entered second while" << std::endl;
				if (userAccount->getAccountBalance() <= 0)
					return gameOver(months);
				battleField(userAccount, enemyAccount, months, records[rIndex]);
				selection = battlePrompt(userAccount);

				switch (selection) {
				case 0:
					battleField(userAccount, enemyAccount, months, records[rIndex]);
					userActionValue = attackPrompt(userAccount);
					break;
				case 1:
					battleField(userAccount, enemyAccount, months, records[rIndex]);
					userActionValue = 0;
					break;
				case 2:
					if (userAccType == sCC) {
						if (!(tempS->canWriteCheck())) {
							selection = 3;
							goto mS;
						}
					}
					if (userAccType > hIC) {
						selection = 3;
						goto mS;
					}
					battleField(userAccount, enemyAccount, months, records[rIndex]);
					userActionValue = checkPrompt(userAccount, enemyAccount);
					break;
				case 3:
					mS:
					battleField(userAccount, enemyAccount, months, records[rIndex]);
					break;
				default:
					battleField(userAccount, enemyAccount, months, records[rIndex]);
					selection = 1;
					userActionValue = 0;
				}

				if (selection == 3) {
					printMonthlyStatements(months, records[rIndex]);
					continue;
				} else {
					if (enemyAccount->getAccountBalance() <= 0 ||
						userAccount->getAccountBalance() <= 0)
						continue;
					enemySelection = enemySelect(enemyAccount, userAccount);
					enemyActionValue = enemyValue(enemyAccount, enemySelection);
					accountInteractions(userAccount, enemyAccount, 
							selection, enemySelection,
							userActionValue, enemyActionValue, records[rIndex]);
					
					months++;
					monthlyUpdate(userAccount, enemyAccount, records[rIndex]); 
					records[rIndex].push_back("break");
				 }
			}
			std::cout << "Exited second while" << std::endl;
			clearUserStatus(userAccount);
			enemyDefeatedScreen(userAccount, enemyAccount, months);
			rIndex++;
			std::cout << "End of first while" << std::endl;
		}
	}

	return userWon();
}
