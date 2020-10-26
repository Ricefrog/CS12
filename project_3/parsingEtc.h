#include <iostream>
#include <fstream>
#include "bankAccount.h"
#include "serviceChargeChecking.h"
#include "noServiceChargeChecking.h"
#include "highInterestChecking.h"
#include "savingsAccount.h"
#include "highInterestSavings.h"
#include "certificateOfDeposit.h"

extern std::string userName;
std::string userName = "newUser";
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
