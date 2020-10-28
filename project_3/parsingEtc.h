#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <vector>
#include "bankAccount.h"
#include "serviceChargeChecking.h"
#include "noServiceChargeChecking.h"
#include "highInterestChecking.h"
#include "savingsAccount.h"
#include "highInterestSavings.h"
#include "certificateOfDeposit.h"

extern std::string userName;
std::string userName = "newUser";
int months;
std::vector<std::string> records;

//turned off when debugging
bool clearScreens = true;

const int numberOfEnemies = 6;

//constants for account types
const double sCCServiceCharge = 300;
const double sCCDmgModifier = 1.5;
const int sCCCheckLimit = 3;

const double nSCCMinBalance = 5000;
const double nSCCMinBalanceFee = 400;
const double nSCCInterestRate = 0.06;

const double hICMinBalance = 5000;
const double hICMinBalanceFee = 400;
const double hICInterestRate = 0.10;
const double hICDmgModifier = 0.8;

const int cODMaturityMonths = 4;
const double cODDmgModifier = 3.00;
const double cODInterestRate = .10;

const double sAInterestRate = .15;

const double hISInterestRate = .25;
const double hISMinBalance = 6000;
const double hISMinBalanceFee = 600;

#define USER_PROMPT\
	std::cout << userName << " >> ";

void startScreen();
void intro();
void accountInfoMenu();
void sCCInfo();
void nSCCInfo();
void hICInfo();
void cODInfo();
void sAInfo();
void hISInfo();
accountType accountSelectionMenu();
bankAccount *enemySelectScreen();
bool allEnemiesDefeated();
void battleField(bankAccount*, bankAccount*, int);
int battlePrompt(bankAccount*);
int enemySelect(bankAccount*, bankAccount*);
double attackPrompt(bankAccount*);
double checkPrompt(bankAccount*, bankAccount*);
void accountInteractions(bankAccount*, bankAccount*, int, int, double, double,
	std::vector<std::string>&);
void monthlyUpdates(bankAccount*, bankAccount*, std::vector<std::string>&);
void recentActions(int, std::vector<std::string>&);
void healthBar(double, double);
int quit();
void psuedoClear();
void horizontalLine(int, char);
void drawBox(std::string, char);
bankAccount *readData(); 
void saveData(bankAccount*);

void startScreen() {
	psuedoClear();
	horizontalLine(13, '#');
	std::cout << "\n# BANK WARS #" << std::endl;
	horizontalLine(13, '#');
	std::cout << "\n\n~New game -> n" << std::endl;
	std::cout << "~Quit -> q\n" << std::endl;
	USER_PROMPT;
}

void intro() {
	psuedoClear();
	std::cout << "Welcome to Bank Wars!\n" << std::endl;
	std::cout << "This is a game where bank accounts wage war" 
		<< " on the financial battlefield.\n" << std::endl;
	std::cout << "~What is your name? (one word)\n" << std::endl;
	USER_PROMPT;
	std::cin >> userName;
	psuedoClear();
	accountInfoMenu();
}

void accountInfoMenu() {
	char selection = 42;
	while (selection != 'n') {
		std::cout << "\nThere are 6 types of bank accounts." << std::endl;
		std::cout << "Each has special strengths and weaknesses." << std::endl;
		std::cout << "\nDo your research and choose wisely.\n" << std::endl;
		std::cout << "~serviceChargeChecking   -> 0 for more info" << std::endl;
		std::cout << "~noServiceChargeChecking -> 1 for more info" << std::endl;
		std::cout << "~highInterestChecking    -> 2 for more info" << std::endl;
		std::cout << "~certificateOfDeposit    -> 3 for more info" << std::endl;
		std::cout << "~savingsAccount          -> 4 for more info" << std::endl;
		std::cout << "~highInterestSavings     -> 5 for more info" << std::endl;
		std::cout << "~I'm ready to choose     -> n\n" << std::endl;
		USER_PROMPT;
		std::cin >> selection;
		switch (selection) {
		case '0':
			sCCInfo();
			break;
		case '1':
			nSCCInfo();
			break;
		case '2':
			hICInfo();
			break;
		case '3':
			cODInfo();
			break;
		case '4':
			sAInfo();
			break;
		case '5':
			hISInfo();
			break;
		case 'n':
			break;
		default:
			std::cout << "Invalid selection." << std::endl;
		}
	}
}

void sCCInfo() {
	char c;
	psuedoClear();
	drawBox("serviceChargeChecking", '#');
	std::cout << "\n\nThis is a checking account. Checking accounts"
		<< " can write checks to\nenemies to postpone their attacks "
		<< "for a certain amount of time.\n" << std::endl;
	std::cout << "These accounts deal extra damage but "
		<< "are charged a service charge every month." << std::endl;
	std::cout << "There is also a limit to the number of checks"
		<< " they can write.\n" << std::endl;
	std::cout << "Service Charge: $" << sCCServiceCharge << std::endl;
	std::cout << "Damage Modifier: " << sCCDmgModifier*100 << "%" << std::endl;
	std::cout << "Check Limit: " << sCCCheckLimit << std::endl;
	std::cout << "Check Postponements:" << std::endl;
	std::cout << "\t10% of enemy's starting health: 1 month" << std::endl;
	std::cout << "\t20% of enemy's starting health: 2 months" << std::endl;
	std::cout << "\n~Got it -> any character\n" << std::endl;
	USER_PROMPT;
	std::cin >> c;
	psuedoClear();
}

void nSCCInfo() {
	char c;
	psuedoClear();
	drawBox("noServiceChargeChecking", '#');
	std::cout << "\n\nThis is a checking account. Checking accounts"
		<< " can write checks to\nenemies to postpone their attacks "
		<< "for a certain amount of time.\n" << std::endl;
	std::cout << "These accounts gain interest each month." << std::endl;
	std::cout << "In addition, they are charged a fee each month\n"
		<< "if they fall below a minimum balance.\n" << std::endl;
	std::cout << "Minimum Balance: $" << nSCCMinBalance << std::endl;
	std::cout << "Minimum Balance Fee: $" << nSCCMinBalanceFee << std::endl;
	std::cout << "Interest Rate: " << nSCCInterestRate*100 << "%" << std::endl;
	std::cout << "Check Postponements:" << std::endl;
	std::cout << "\t10% of enemy's starting health: 1 month" << std::endl;
	std::cout << "\t20% of enemy's starting health: 2 months" << std::endl;
	std::cout << "\n~Got it -> any character\n" << std::endl;
	USER_PROMPT;
	std::cin >> c;
	psuedoClear();
}

void hICInfo() {
	char c;
	psuedoClear();
	drawBox("highInterestChecking", '#');
	std::cout << "\n\nThis is a checking account. Checking accounts"
		<< " can write checks\nto enemies to postpone their attacks "
		<< "for a certain amount of time.\n" << std::endl;
	std::cout << "These accounts behave the same as "
		<< "noServiceChargeChecking accounts." << std::endl;
	std::cout << "However, the interest rate is higher and they deal"
		<< " less damage.\n" << std::endl;
	std::cout << "Minimum Balance: $" << hICMinBalance << std::endl;
	std::cout << "Minimum Balance Fee: $" << hICMinBalanceFee << std::endl;
	std::cout << "Interest Rate: " << hICInterestRate*100 << "%" << std::endl;
	std::cout << "Damage Modifier: " << hICDmgModifier*100 << "%" << std::endl;
	std::cout << "Check Postponements:" << std::endl;
	std::cout << "\t10% of enemy's starting health: 1 month" << std::endl;
	std::cout << "\t20% of enemy's starting health: 2 months" << std::endl;
	std::cout << "\n~Got it -> any character\n" << std::endl;
	USER_PROMPT;
	std::cin >> c;
	psuedoClear();
}

void cODInfo() {
	char c;
	psuedoClear();
	drawBox("certificateOfDeposit", '#');
	std::cout << "\n\nThese accounts cannot attack until they\n"
		<< "are MATURE.\n\nHowever, once they are MATURE they gain"
		<< "\na powerful attack bonus." << std::endl;
	std::cout << "These accounts also gain interest each month." << std::endl;
	std::cout << "Also, enemies cannot write checks to accounts\n"
		<< "of this type.\n" << std::endl;
	std::cout << "Months Until Maturity: " << cODMaturityMonths << std::endl;
	std::cout << "MATURE Attack Bonus: " << cODDmgModifier*100 << "%"
		<< std::endl;
	std::cout << "Interest Rate: " << cODInterestRate*100 << "%" << std::endl;
	std::cout << "\n~Got it -> any character\n" << std::endl;
	USER_PROMPT;
	std::cin >> c;
	psuedoClear();
}

void sAInfo() {
	char c;
	psuedoClear();
	drawBox("savngsAccount", '#');
	std::cout << "\n\nThese accounts have a high interest rate\n"
		<< "but sacrifice utility." << std::endl;
	std::cout << "\nInterest Rate: " << sAInterestRate*100 << "%" << std::endl;
	std::cout << "\n~Got it -> any character\n" << std::endl;
	USER_PROMPT;
	std::cin >> c;
	psuedoClear();
}

void hISInfo() {
	char c;
	psuedoClear();
	drawBox("highInterestSavings", '#');
	std::cout << "\n\nThese accounts have a higher interest rate\n"
		<< "than regular savings accounts but will invoke\n"
		<< "a fee at the end of the month if they go under\n"
		<< "their minimum balance.\n" << std::endl;
	std::cout << "Minimum Balance: $" << hISMinBalance << std::endl;
	std::cout << "Minimum Balance Fee: $" << hISMinBalanceFee << std::endl;
	std::cout << "Interest Rate: " << hISInterestRate*100 << "%" << std::endl;
	std::cout << "\n~Got it -> any character\n" << std::endl;
	USER_PROMPT;
	std::cin >> c;
	psuedoClear();
}

accountType accountSelectionMenu() {
	psuedoClear();
	int selection = 42;
	char temp;
	std::cout << "Please choose the account type you will be using:\n" 
		<< std::endl;
	std::cout << "~serviceChargeChecking   -> 0" << std::endl;
	std::cout << "~noServiceChargeChecking -> 1" << std::endl;
	std::cout << "~highInterestChecking    -> 2" << std::endl;
	std::cout << "~certificateOfDeposit    -> 3" << std::endl;
	std::cout << "~savingsAccount          -> 4" << std::endl;
	std::cout << "~highInterestSavings     -> 5\n" << std::endl;
	USER_PROMPT;
	std::cin >> selection;
	switch (selection) {
	case 0:
		psuedoClear();
		drawBox("You chose serviceChargeChecking!", '$'); 
		std::cout << "\n\n~Continue -> any character\n" << std::endl;
		USER_PROMPT;
		std::cin >> temp;
		return static_cast<accountType>(selection);
		break;
	case 1:
		psuedoClear();
		drawBox("You chose noServiceChargeChecking!", '$'); 
		std::cout << "\n\n~Continue -> any character\n" << std::endl;
		USER_PROMPT;
		std::cin >> temp;
		return static_cast<accountType>(selection);
		break;
	case 2:
		psuedoClear();
		drawBox("You chose highInterestChecking!", '$'); 
		std::cout << "\n\n~Continue -> any character\n" << std::endl;
		USER_PROMPT;
		std::cin >> temp;
		return static_cast<accountType>(selection);
		break;
	case 3:
		psuedoClear();
		drawBox("You chose certificateOfDeposit!", '$'); 
		std::cout << "\n\n~Continue -> any character\n" << std::endl;
		USER_PROMPT;
		std::cin >> temp;
		return static_cast<accountType>(selection);
		break;
	case 4:
		psuedoClear();
		drawBox("You chose savingsAccount!", '$'); 
		std::cout << "\n\n~Continue -> any character\n" << std::endl;
		USER_PROMPT;
		std::cin >> temp;
		return static_cast<accountType>(selection);
		break;
	case 5:
		psuedoClear();
		drawBox("You chose highInterestSavings!", '$'); 
		std::cout << "\n\n~Continue -> any character\n" << std::endl;
		USER_PROMPT;
		std::cin >> temp;
		return static_cast<accountType>(selection);
		break;
	default:
		psuedoClear();
		std::cout << "Invalid selection." << std::endl;
		std::cout << "You will be using a highInterestSavings account." 
			<< std::endl;
		std::cout << "\n~Continue -> any character\n" << std::endl;
		USER_PROMPT;
		std::cin >> temp;
		return hIS;
	}
}

bankAccount *enemySelectScreen() {
	bankAccount *current = bankAccount::root;
	bankAccount *selectedEnemy;
	std::string status;
	int nameLength;
	int selection;

	psuedoClear();
	drawBox("Choose your opponent!", 'x');
	printf("\n\n");
	for (int i = 0; i < numberOfEnemies; i++) {
		nameLength = (current->getAccountName()).length();
		if (current->getAccountBalance() > 0)
			status = "ALIVE";
		else 
			status = "DEFEATED";

		std::cout << "~" << current->getAccountName(); 
		for (int j = 0; j < 10 - nameLength; j++)
			std::cout << " ";
		std::cout << " (" << i << ")";
		std::cout << " [" << status << "]" << std::endl;
		current = current->next;
	}
	printf("\n");
	USER_PROMPT;
	std::cin >> selection;
	if (selection > 5)
		selection = 0;
	psuedoClear();
	
	selectedEnemy = bankAccount::root;
	for (int i = 0; i < selection; i++) {
		selectedEnemy = selectedEnemy->next;
	}
	std::cout << "Here is some information about your opponent.\n" << std::endl;
	selectedEnemy->info();
	std::cout << "\n~I\'m ready to battle! -> any character\n" << std::endl;
	USER_PROMPT;
	std::cin >> selection;
	std::cin.clear();
	return selectedEnemy;
}

bool allEnemiesDefeated() {
	bankAccount *current = bankAccount::root;
	for (int i = 0; i < numberOfEnemies; i++) {
		if (current->getAccountBalance() > 0)
			return false;
		current = current->next;
	}
	return true;
}

void battleField(bankAccount *userAccount, bankAccount *enemyAccount,
		int months) {
	accountType userType = userAccount->getAccountType();
	accountType enemyType = enemyAccount->getAccountType();
	double maxUserBalance = userAccount->startingBalance;
	double maxEnemyBalance = enemyAccount->startingBalance;
	double userBalance = userAccount->getAccountBalance();
	double enemyBalance = enemyAccount->getAccountBalance();
	std::string enemyName = enemyAccount->getAccountName();
	char temp;

	if (userBalance > maxUserBalance) 
		maxUserBalance = userBalance;
	if (enemyBalance > maxEnemyBalance)
		maxEnemyBalance = enemyBalance;
	
	psuedoClear();
	std::cout << "MONTHS: " << months << std::endl << std::endl;
	std::cout << "x " << enemyName << " x";
	if (enemyAccount->isDelayed())
		std::cout << " D E L A Y E D";
	printf("\n");
	healthBar(maxEnemyBalance, enemyBalance);
	printf("\n");
	if (enemyType == nSCC || enemyType == hIC || enemyType == hIS) {
		noServiceChargeChecking *tempA;
		highInterestChecking *tempB;
		highInterestSavings *tempC;
		double rate; 
		double min; 
		double fee; 
		switch (enemyType) {
		case nSCC:
			tempA = static_cast<noServiceChargeChecking*>(enemyAccount);
			rate = tempA->getInterestRate();
			min = tempA->getMinimumBalance();
			fee = tempA->getBalanceFee();
		case hIC:
			tempB = static_cast<highInterestChecking*>(enemyAccount);
			rate = tempB->getInterestRate();
			min = tempB->getMinimumBalance();
			fee = tempB->getBalanceFee();
		case hIS:
			tempC = static_cast<highInterestSavings*>(enemyAccount);
			rate = tempC->getInterestRate();
			min = tempC->getMinimumBalance();
			fee = tempC->getBalanceFee();
		}
		std::cout << "Interest Rate: " << rate*100 << "%" << std::endl;
		std::cout << "Minimum Balance: $" << min << std::endl;
		std::cout << "Minimum Balance Fee: $" << fee << std::endl;
	} else if (enemyType == sCC) {
		serviceChargeChecking *tempA = static_cast<serviceChargeChecking*>(enemyAccount);
		int limit = tempA->getCheckLimit();
		int written = tempA->getChecksWritten();
		double charge = tempA->getServiceCharge();
		std::cout << "Check Limit: " << limit << std::endl;
		std::cout << "Checks Written: " << written << std::endl;
		std::cout << "Service Charge: $" << charge << std::endl;
	} else if (enemyType == sA) {
		savingsAccount *tempA = static_cast<savingsAccount*>(enemyAccount);
		double rate = tempA->getInterestRate()*100;
		std::cout << "Interest Rate: " << rate << "%" << std::endl;
	} else {
		certificateOfDeposit *tempA = static_cast<certificateOfDeposit*>(enemyAccount);
		double rate = tempA->getInterestRate()*100;
		int mMonths = tempA->getMaturityMonths();
		std::cout << "Interest Rate: " << rate << "%" << std::endl;
		if (mMonths - months <= 0)
			std::cout << "xX MATURE Xx" << std::endl;
		else
			std::cout << "Months Until MATURE: " << mMonths-months << std::endl;
	}
	std::cout << "\n\n$ " << userName << " $";
	if (userAccount->isDelayed())
		std::cout << " D E L A Y E D";
	printf("\n");
	healthBar(maxUserBalance, userBalance);
	printf("\n");
	if (userType == nSCC || userType == hIC || userType == hIS) {
		noServiceChargeChecking *tempA;
		highInterestChecking *tempB;
		highInterestSavings *tempC;
		double rate; 
		double min; 
		double fee; 
		switch (userType) {
		case nSCC:
			tempA = static_cast<noServiceChargeChecking*>(userAccount);
			rate = tempA->getInterestRate();
			min = tempA->getMinimumBalance();
			fee = tempA->getBalanceFee();
		case hIC:
			tempB = static_cast<highInterestChecking*>(userAccount);
			rate = tempB->getInterestRate();
			min = tempB->getMinimumBalance();
			fee = tempB->getBalanceFee();
		case hIS:
			tempC = static_cast<highInterestSavings*>(userAccount);
			rate = tempC->getInterestRate();
			min = tempC->getMinimumBalance();
			fee = tempC->getBalanceFee();
		}
		std::cout << "Interest Rate: " << rate*100 << "%" << std::endl;
		std::cout << "Minimum Balance: $" << min << std::endl;
		std::cout << "Minimum Balance Fee: $" << fee << std::endl;
	} else if (userType == sCC) {
		serviceChargeChecking *tempA = static_cast<serviceChargeChecking*>(userAccount);
		int limit = tempA->getCheckLimit();
		int written = tempA->getChecksWritten();
		double charge = tempA->getServiceCharge();
		std::cout << "Check Limit: " << limit << std::endl;
		std::cout << "Checks Written: " << written << std::endl;
		std::cout << "Service Charge: $" << charge << std::endl;
	} else if (userType == sA) {
		savingsAccount *tempA = static_cast<savingsAccount*>(userAccount);
		double rate = tempA->getInterestRate() * 100;
		std::cout << "Interest Rate: " << rate << "%" << std::endl;
	} else {
		certificateOfDeposit *tempA = static_cast<certificateOfDeposit*>(userAccount);
		double rate = tempA->getInterestRate() * 100;
		int mMonths = tempA->getMaturityMonths();
		std::cout << "Interest Rate: " << rate << "%" << std::endl;
		if (mMonths - months <= 0)
			std::cout << "xX MATURE Xx" << std::endl;
		else
			std::cout << "Months Until MATURE: " << mMonths-months << std::endl;
	}
	recentActions(months, records);
}

int battlePrompt(bankAccount *userAccount) {
	int selection;
	int i = 2;
	accountType type = userAccount->getAccountType();
	serviceChargeChecking *tempA = static_cast<serviceChargeChecking*>(userAccount);

	printf("\n");
	drawBox("What will you do?", '.');
	printf("\n\n");
	std::cout << "~Attack                  -> 0" << std::endl;
	std::cout << "~Do nothing              -> 1" << std::endl;
	if (type < cOD) {
		if (type != sCC)
			std::cout << "~Write check             -> " << i++ << std::endl;
		else if (tempA->canWriteCheck()) {
			std::cout << "~Write check             -> " << i++ << std::endl;
		}

	}
	std::cout << "~View monthly statements -> " << i++ << std::endl;
	printf("\n");
	USER_PROMPT;
	std::cin >> selection;
	return selection;
}

int enemySelect(bankAccount *enemyAccount, bankAccount *userAccount) {
	srand(time(NULL));
	accountType type = enemyAccount->getAccountType();
	certificateOfDeposit *tempA = static_cast<certificateOfDeposit*>(enemyAccount);
	serviceChargeChecking *tempB;
	int selection = rand() % 100;
	switch (type) {
	case sCC:
		tempB = static_cast<serviceChargeChecking*>(enemyAccount);
		if (!tempB->canWriteCheck()) {
			return 0;
		}
	case nSCC:
	case hIC:
		if (selection < 30)
			return 0;
		if (selection < 29 && selection < 80)
			return 1;
		userAccount->setMonthsDelayed(1);
		return 2;
	case cOD:
		if (tempA->isMature())
			return 0;
		return 1;
	default:
		if (selection > 60)
			return 1;
		return 2;
	}
	return 1;	
}

double enemyValue(bankAccount *enemyAccount, int enemySelection) {
	double enemyBalance = enemyAccount->getAccountBalance();
	srand(time(NULL));
	double randVal = (rand() % 100) * .001 + .01;

	switch (enemySelection) {
	case 0:
		return (randVal * enemyBalance);
	case 1:
		return 0;
	case 2:
		return (randVal * enemyBalance);
	}
	return 0;
}

double attackPrompt(bankAccount *userAccount) {
	double value;
	printf("\n\n");
	drawBox("How much are you going to spend?", '.');
	printf("\n\n");
	USER_PROMPT;
	std::cout << "$";
	std::cin >> value;
	fixSign(value);
	if (value > userAccount->getAccountBalance())
		value = userAccount->getAccountBalance();
	return value;
}

double checkPrompt(bankAccount *userAccount, bankAccount *enemyAccount) {
	double enemyBalance = enemyAccount->getAccountBalance();
	double oneTurn = enemyBalance/10;
	double twoTurns = enemyBalance/5;
	double selection;

	printf("\n\n");
	drawBox("How much are you going to spend?", '.');
	printf("\n\n");
	std::cout << "~Delay for one turn  (1): $" << oneTurn << std::endl;
	std::cout << "~Delay for two turns (2): $" << twoTurns << std::endl;
	printf("\n\n");
	USER_PROMPT;
	std::cin >> selection;
	if (selection < 2) {
		enemyAccount->setMonthsDelayed(1);
		return oneTurn;
	}
	enemyAccount->setMonthsDelayed(2);
	return twoTurns;
}

void accountInteractions(bankAccount *userAccount, bankAccount *enemyAccount,
		int userSelection, int enemySelection,
		double userActionValue, double enemyActionValue,
		std::vector<std::string> &records) { 
	accountType userType = userAccount->getAccountType();
	accountType enemyType = enemyAccount->getAccountType();
	checkingAccount *tempU = static_cast<checkingAccount*>(userAccount);
	checkingAccount *tempE = static_cast<checkingAccount*>(enemyAccount);
	serviceChargeChecking *userSCC;
	serviceChargeChecking *enemySCC;
	double userDmgModifier;
	double enemyDmgModifier;
	double userChargeOrFee;
	double enemyChargeOrFee;
	std::string enemyName = enemyAccount->getAccountName();
	std::string enemyRecord;
	std::string userRecord;

	switch (userType) {
	case sCC:
		userDmgModifier = sCCDmgModifier;
		userSCC = static_cast<serviceChargeChecking*>(userAccount);
		userChargeOrFee = userSCC->getServiceCharge();
		userAccount->withdraw(userChargeOrFee);
		userRecord = userName+" was charged $"+std::to_string(userChargeOrFee)+".";
		records.push_back(userRecord);
		break;
	case hIC:
		userDmgModifier = hICDmgModifier;
		break;
	case cOD:
		userDmgModifier = cODDmgModifier;
		break;
	default:
		userDmgModifier = 1;
	}

	switch (enemyType) {
	case sCC:
		enemyDmgModifier = sCCDmgModifier;
		enemySCC = static_cast<serviceChargeChecking*>(enemyAccount);
		enemyChargeOrFee = enemySCC->getServiceCharge();
		enemyAccount->withdraw(enemyChargeOrFee);
		enemyRecord = enemyName+" was charged $"+std::to_string(enemyChargeOrFee)+".";
		records.push_back(enemyRecord);
		break;
	case hIC:
		enemyDmgModifier = hICDmgModifier;
		break;
	case cOD:
		enemyDmgModifier = cODDmgModifier;
		break;
	default:
		enemyDmgModifier = 1;
	}
	
	switch (enemySelection) {
	case 0:
		if (enemyAccount->isDelayed()) 
			enemyRecord = enemyName+"'s attack failed!";
		else {
			enemyAccount->withdraw(enemyActionValue);
			userAccount->withdraw(enemyDmgModifier*enemyActionValue);
			enemyRecord = enemyName+" attacked for $"+
				std::to_string(enemyDmgModifier*enemyActionValue)+" damage.";
		}
		break;
	case 1:
		enemyRecord = enemyName+" just stood there and did nothing.";
		break;
	case 2:
		if (userType != cOD) {
			tempE->writeCheck(enemyActionValue, userAccount);
			enemyRecord = enemyName+" wrote a check for $"+
				std::to_string(enemyActionValue)+".";
		} else {
			enemyRecord = enemyName+"'s check bounced!";
		}
	}

	switch (userSelection) {
	case 0:
		if (userAccount->isDelayed()) 
			userRecord = userName+"'s attack failed!";
		else {
			userAccount->withdraw(userActionValue);
			enemyAccount->withdraw(userDmgModifier*userActionValue);
			userRecord = userName+" attacked for $"+
				std::to_string(userDmgModifier*userActionValue)+" damage.";
		}
		break;
	case 1:
		userRecord = userName+" just stood there and did nothing.";
		break;
	case 2:
		tempU->writeCheck(userActionValue, userAccount);
		userRecord = userName+" wrote a check for $"+
			std::to_string(userActionValue)+".";
	}
	records.push_back(enemyRecord);
	records.push_back(userRecord);
	enemyRecord = "";
	userRecord = "";

	if (userType == nSCC || userType == hIC || userType == hIS) {
		noServiceChargeChecking *sTemp1;
		highInterestChecking *sTemp2;
		highInterestSavings *sTemp3;
		switch (userType) {
		case nSCC:
			sTemp1 = static_cast<noServiceChargeChecking*>(userAccount);
			if (sTemp1->getFeeInvoked()) {
				userChargeOrFee = sTemp1->getBalanceFee();
				userAccount->withdraw(userChargeOrFee);
				userRecord = userName+" was fined $"+std::to_string(userChargeOrFee)+
					" for going below their minimum balance.";
				sTemp1->resetFee();
			}
			break;
		case hIC:
			sTemp2 = static_cast<highInterestChecking*>(userAccount);
			if (sTemp2->getFeeInvoked()) {
				userChargeOrFee = sTemp2->getBalanceFee();
				userAccount->withdraw(userChargeOrFee);
				userRecord = userName+" was fined $"+std::to_string(userChargeOrFee)+
					" for going below their minimum balance.";
				sTemp2->resetFee();
			}
			break;
		case hIS:
			sTemp3 = static_cast<highInterestSavings*>(userAccount);
			if (sTemp3->getFeeInvoked()) {
				userChargeOrFee = sTemp3->getBalanceFee();
				userAccount->withdraw(userChargeOrFee);
				userRecord = userName+" was fined $"+std::to_string(userChargeOrFee)+
					" for going below their minimum balance.";
				sTemp3->resetFee();
			}
			break;
		}
	}

	if (enemyType == nSCC || enemyType == hIC || enemyType == hIS) {
		noServiceChargeChecking *sTemp1;
		highInterestChecking *sTemp2;
		highInterestSavings *sTemp3;
		switch (enemyType) {
		case nSCC:
			sTemp1 = static_cast<noServiceChargeChecking*>(enemyAccount);
			if (sTemp1->getFeeInvoked()) {
				enemyChargeOrFee = sTemp1->getBalanceFee();
				enemyAccount->withdraw(enemyChargeOrFee);
				enemyRecord = enemyName+" was fined $"+std::to_string(enemyChargeOrFee)+
					" for going below their minimum balance.";
				sTemp1->resetFee();
			}
			break;
		case hIC:
			sTemp2 = static_cast<highInterestChecking*>(enemyAccount);
			if (sTemp2->getFeeInvoked()) {
				enemyChargeOrFee = sTemp2->getBalanceFee();
				enemyAccount->withdraw(enemyChargeOrFee);
				enemyRecord = userName+" was fined $"+std::to_string(enemyChargeOrFee)+
					" for going below their minimum balance.";
				sTemp2->resetFee();
			}
			break;
		case hIS:
			sTemp3 = static_cast<highInterestSavings*>(enemyAccount);
			if (sTemp3->getFeeInvoked()) {
				enemyChargeOrFee = sTemp3->getBalanceFee();
				enemyAccount->withdraw(userChargeOrFee);
				enemyRecord = enemyName+" was fined $"+std::to_string(enemyChargeOrFee)+
					" for going below their minimum balance.";
				sTemp3->resetFee();
			}
			break;
		}
	}
	if (enemyRecord.length() > 1)	
		records.push_back(enemyRecord);
	if (userRecord.length() > 1)
		records.push_back(userRecord);
}

void monthlyUpdate(bankAccount* userAccount, bankAccount *enemyAccount,
		std::vector<std::string> &records) {
	double userBalance = userAccount->getAccountBalance();
	double enemyBalance = enemyAccount->getAccountBalance();
	double uInterestRate;
	double eInterestRate;
	int userType = userAccount->getAccountType();
	int enemyType = userAccount->getAccountType();
	std::string enemyName = enemyAccount->getAccountName();
	std::string userRecord;
	std::string enemyRecord;
	noServiceChargeChecking *tempA;
	highInterestChecking *tempB;
	certificateOfDeposit *tempC;
	savingsAccount *tempD;
	highInterestSavings *tempE;

	if (userAccount->isDelayed()) 
		userAccount->decrementMonthsDelayed();
	if (enemyAccount->isDelayed()) 
		enemyAccount->decrementMonthsDelayed();

	switch (enemyType) {
	case sCC:
		return;
	case nSCC:
		tempA = static_cast<noServiceChargeChecking*>(enemyAccount);
		eInterestRate = tempA->getInterestRate();
		tempA->deposit(eInterestRate*enemyBalance);
		break;
	case hIC:
		tempB = static_cast<highInterestChecking*>(enemyAccount);
		eInterestRate = tempB->getInterestRate();
		tempB->deposit(eInterestRate*enemyBalance);
		break;
	case cOD:
		tempC->incrementMonths();
		tempC = static_cast<certificateOfDeposit*>(enemyAccount);
		eInterestRate = tempC->getInterestRate();
		tempC->deposit(eInterestRate*enemyBalance);
		break;
	case sA:
		tempD = static_cast<savingsAccount*>(enemyAccount);
		eInterestRate = tempD->getInterestRate();
		tempD->deposit(eInterestRate*enemyBalance);
	case hIS:
		tempE = static_cast<highInterestSavings*>(enemyAccount);
		eInterestRate = tempE->getInterestRate();
		tempE->deposit(eInterestRate*enemyBalance);
	}

	switch (userType) {
	case sCC:
		return;
	case nSCC:
		tempA = static_cast<noServiceChargeChecking*>(userAccount);
		uInterestRate = tempA->getInterestRate();
		tempA->deposit(uInterestRate*userBalance);
		break;
	case hIC:
		tempB = static_cast<highInterestChecking*>(userAccount);
		uInterestRate = tempB->getInterestRate();
		tempB->deposit(uInterestRate*userBalance);
		break;
	case cOD:
		tempC = static_cast<certificateOfDeposit*>(userAccount);
		uInterestRate = tempC->getInterestRate();
		tempC->deposit(uInterestRate*userBalance);
		break;
	case sA:
		tempD = static_cast<savingsAccount*>(userAccount);
		uInterestRate = tempD->getInterestRate();
		tempD->deposit(uInterestRate*userBalance);
	case hIS:
		tempE = static_cast<highInterestSavings*>(userAccount);
		uInterestRate = tempE->getInterestRate();
		tempE->deposit(uInterestRate*userBalance);
	}

	double tempVal = uInterestRate * userBalance;
	userRecord = userName+" gained $"+std::to_string(tempVal)+" in interest.";
	tempVal = eInterestRate * enemyBalance;
	enemyRecord = enemyName+" gained $"+std::to_string(tempVal)+" in interest.";
	records.push_back(enemyRecord);
	records.push_back(userRecord);
}

void recentActions(int months, std::vector<std::string> &records) {
	if (months == 0)
		return;
	int length = records.size();
	bool found = false;
	int indexBegin;
	int indexEnd;
	int i = 0;
	int monthCounter = 0;
	//get to most recent month
	while (monthCounter < months - 1) {
		std::string current = records[i];
		if (current == "break") 
			monthCounter++;
		i++;
	}
	indexBegin = i;
	while (records[i++] != "break");
	indexEnd = --i;

	printf("\n");
	for (int j = indexBegin; j < indexEnd; j++) {
		std::cout << records[j] << std::endl;
	}
}

void healthBar(double max, double current) {
	double maxDots = 20;
	double ratio = (current/max)/maxDots;
	int newMax = static_cast<int>(maxDots);
	int newRatio = static_cast<int>(ratio);
	int i;
	std::cout << "newRatio: " << newRatio << std::endl;

	std::cout << "Balance: [";
	for (i = 0; i < (newMax-ratio); i++) 
		std::cout << "*";
	for ( ; i < newMax; i++) 
		std::cout << " ";
	std::cout << "] " << "$" << current << "/$" << max;	

}

int quit() {
	psuedoClear();
	std::cout << "Thanks for playing!\n" << std::endl;
	saveData(bankAccount::root);
	return 0;
}

void psuedoClear() {
	if (clearScreens)
		for (int i = 0; i < 100; i++)
			std::cout << "\n";
}

void horizontalLine(int num, char c) {
	for (int i = 0; i < num; i++)
		std::cout << c; 
}

void drawBox(std::string entry, char c) {
	int length = entry.length() + 4;
	horizontalLine(length, c); 
	std::cout << "\n" << c << " " << entry << " " << c << std::endl;
	horizontalLine(length, c); 
}


bankAccount *readData() {
	bankAccount *current;
	serviceChargeChecking *sCCTemp;
	noServiceChargeChecking *nSCCTemp;
	highInterestChecking *hICTemp;
	certificateOfDeposit *cODTemp;
	savingsAccount *sATemp;
	highInterestSavings *hISTemp;

	std::ifstream infile;
	infile.open("dataStore.txt");
	int counter = 0;
	int totalAccounts;
	infile >> totalAccounts;
	while (counter++ < totalAccounts){
		//std::cout << "Top of while. counter = " << counter << std::endl;
		accountType currentType;
		int tempType = -1;
		int accountNumber = -1;
		std::string accountName = "error";
		double accountBalance = -1;
		double interestRate;
		double minimumBalance;
		double balanceFee;
		bool feeInvoked;
		std::string temp;
		
		infile >> tempType >> accountNumber >> accountName >> accountBalance;
		currentType = static_cast<accountType>(tempType);
		/*
		std::cout << "Before entering switch: " <<
			"\ncurrentType: " << tempType <<
			"\naccountNumber: " << accountNumber <<
			"\naccountName: " << accountName <<
			"\naccountBalance: " << accountBalance << std::endl;
		*/
		switch (currentType) {
		case sCC:
			//std::cout << "sCC" << std::endl;
			int checkLimit;
			int checksWritten;
			double serviceCharge;
			infile >> checkLimit >> checksWritten >> serviceCharge;
			infile.get();
			sCCTemp = new serviceChargeChecking(currentType, accountName, 
					accountBalance, checkLimit, checksWritten, serviceCharge);
			current = sCCTemp;
			break;
		case nSCC:
			//std::cout << "nSCC" << std::endl;
			infile >> interestRate >> minimumBalance >> balanceFee
				>> feeInvoked;
			infile.get();
			nSCCTemp = new noServiceChargeChecking(currentType, accountName,
					accountBalance, interestRate, minimumBalance, balanceFee,
					feeInvoked);
			current = nSCCTemp;
			break;
		case hIC:
			//std::cout << "hIC" << std::endl;
			infile >> interestRate >> minimumBalance >> balanceFee
				>> feeInvoked;
			infile.get();
			hICTemp = new highInterestChecking(currentType, accountName,
					accountBalance, interestRate, minimumBalance, balanceFee,
					feeInvoked);
			current = hICTemp;
			break;
		case cOD:
			//std::cout << "cOD" << std::endl;
			int maturityMonths;
			int currentMonths;
			infile >> interestRate >> maturityMonths >> currentMonths;
			infile.get();
			cODTemp = new certificateOfDeposit(currentType, accountName, 
					accountBalance, interestRate, maturityMonths, 
					currentMonths);
			current = cODTemp;
			break;
		case sA:
			//std::cout << "sA" << std::endl;
			infile >> interestRate;
			infile.get();
			sATemp = new savingsAccount(currentType, accountName, 
					accountBalance, interestRate);
			current = sATemp;
			break;
		case hIS:
			//std::cout << "hIS" << std::endl;
			infile >> interestRate >> minimumBalance >> balanceFee
				>> feeInvoked; 
			infile.get();
			hISTemp = new highInterestSavings(currentType, accountName,
					accountBalance, interestRate, minimumBalance, 
					balanceFee, feeInvoked);
			current = hISTemp;
			break;
		default:
			std::cout << "Something went wrong while reading file."
				<< std::endl;
		}
		std::getline(infile, temp);
		current->setTransactionStr(temp);
	} 
	return bankAccount::root;
}

void saveData(bankAccount *root) {
	bankAccount *current = root;
	serviceChargeChecking *sCCTemp;
	noServiceChargeChecking *nSCCTemp;
	highInterestChecking *hICTemp;
	certificateOfDeposit *cODTemp;
	savingsAccount *sATemp;
	highInterestSavings *hISTemp;

	std::ofstream outfile;
	outfile.open("dataStore.txt");
	outfile << bankAccount::totalAccounts << "\n";
	while (current != nullptr) {
		//accountType accountNumber accountName accountBalance
		accountType currentType = current->getAccountType();
		outfile << std::fixed << std::setprecision(2) << currentType;
		outfile << " " << current->getAccountNumber() << " ";
		outfile << current->getAccountName() << " ";
		outfile << current->getAccountBalance() << " ";
		switch (currentType) {
		case sCC:
			sCCTemp = static_cast<serviceChargeChecking*>(current);
			//checkLimit checksWritten serviceCharge
			outfile << sCCTemp->getCheckLimit() << " ";
			outfile << sCCTemp->getChecksWritten() << " ";
			outfile << sCCTemp->getServiceCharge();
			break;
		case nSCC:
			nSCCTemp = static_cast<noServiceChargeChecking*>(current);
			//interestRate minimumBalance balanceFee feeInvoked
			outfile << nSCCTemp->getInterestRate() << " ";
			outfile << nSCCTemp->getMinimumBalance() << " ";
			outfile << nSCCTemp->getBalanceFee() << " ";
			outfile << nSCCTemp->getFeeInvoked();
			break;
		case hIC:
			hICTemp = static_cast<highInterestChecking*>(current);
			//interestRate minimumBalance balanceFee feeInvoked
			outfile << hICTemp->getInterestRate() << " ";
			outfile << hICTemp->getMinimumBalance() << " ";
			outfile << hICTemp->getBalanceFee() << " ";
			outfile << hICTemp->getFeeInvoked();
			break;
		case cOD:
			cODTemp = static_cast<certificateOfDeposit*>(current);
			//interestRate maturityMonths currentMonths
			outfile << cODTemp->getInterestRate() << " ";
			outfile << cODTemp->getMaturityMonths() << " ";
			outfile << cODTemp->getCurrentMonths();
			break;
		case sA:
			sATemp = static_cast<savingsAccount*>(current);
			//interestRate
			outfile << sATemp->getInterestRate();
			break;
		case hIS:
			hISTemp = static_cast<highInterestSavings*>(current);
			//interestRate minimumBalance balanceFee feeInvoked
			outfile << hISTemp->getInterestRate() << " ";
			outfile << hISTemp->getMinimumBalance() << " ";
			outfile << hISTemp->getBalanceFee() << " ";
			outfile << hISTemp->getFeeInvoked();
		}
		//transactions
		outfile << "\n" << current->getTransactionStr() << "\n";
		current = current->next;
	}
}
