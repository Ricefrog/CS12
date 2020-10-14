#include <iostream>
#include "bankAccount.h"
#include "checkingAccount.h"
#include "savingsAccount.h"
#include <fstream>

#define inputPrompt() std::cout << "[" << currentUser << "@nessus]$ "

#define EXEC(type, ptr, member) if (!type)\
					(static_cast<checkingAccount*>(ptr))->member;\
				else \
					(static_cast<savingsAccount*>(ptr))->member;

#define ASSIGN(lVal, type, ptr, member) if (!type)\
					lVal = (static_cast<checkingAccount*>(ptr))->member;\
				else \
					lVal = (static_cast<savingsAccount*>(ptr))->member;

checkingAccount *newCAccount(); 
savingsAccount *newSAccount();
void startupPrompt();
void mainPrompt();
int userQuit();

//will modify minimum balance, service charges, and interest rate
//based on the plan specified in the string variable
void checkingPlan(std::string, double&, double&, double&);
//modifies interestRate variable based on the plan specified
void savingsPlan(std::string, double&);

//returns account by number or by name
template <class accType>
accType *findAccount(accType *cur, std::string name, int number) {
	if (cur == nullptr)
		return nullptr;
	if (!name.compare("byNumber")) {
		if (cur->getAccountNumber() == number)
			return cur;
		return findAccount(cur->next, "byNumber", number);
	} else {
		if (cur->getAccountName() == name)
			return cur;
		return findAccount(cur->next, name, 0);
	}
}

template <class accType>
void printAll(accType *cur) {
	if (cur == nullptr)
		return;
	cur->info();
	printAll(cur->next);
}

//will change sign of a number positive if it is negative
template <class type>
void signFix(type &num) {
	if (num < 0)
		num = -1 * num;
}

//This string is used in all the prompts
std::string currentUser = "user";
int *totalAccounts = &bankAccount::totalAccounts;
//0 for checking account, 1 for savings account
bool type = 0;

int main(void) {
	char c;

	checkingAccount *firstC = nullptr;
	checkingAccount *cTemp = nullptr;
	checkingAccount *p = nullptr;
	
	savingsAccount *firstS = nullptr;
	savingsAccount *sTemp = nullptr;
	savingsAccount *q = nullptr;

	std::ifstream infile;
	std::string checkEnd;
	infile.open("input.txt");

	//load account from file.
	while (infile >> checkEnd) {

		if (!checkEnd.compare("endfile"))
			break;
		for (int i = checkEnd.length()-1; i >= 0; i--)
			infile.putback(checkEnd[i]);

		std::string name = "";
		std::string accountType;
		std::string tempStr;
		std::string plan;
		double initBalance;

		while ((c = infile.get()) == '#')
			while ((c = infile.get()) != '\n');
		infile.putback(c);

		infile >> tempStr;
		while (tempStr != "Checking" && tempStr != "Savings") {
			name += tempStr + " ";
			infile >> tempStr;
		}
		name.pop_back();

		//tempStr now holds the account typea
		accountType = tempStr;
		infile >> initBalance;
		infile >> plan;
		if (accountType == "Checking") {
			double minBal = 0.0;
			double sCharges = 0.0;
			double rate = 0.0;

			checkingPlan(plan, minBal, sCharges, rate);			
			cTemp = new checkingAccount(name, initBalance, minBal, sCharges, rate);
			
			if (firstC == nullptr) 
				firstC = cTemp;
			else {
				p = firstC;
				while (p->next != nullptr)
					p = p->next;
				p->next = cTemp;
			}

		} else {
			double rate = 0.0;

			savingsPlan(plan, rate);
			sTemp = new savingsAccount(name, initBalance, rate);

			if (firstS == nullptr)
				firstS = sTemp;
			else {
				q = firstS;
				while (q->next != nullptr)
					q = q->next;
				q->next = sTemp;
			}
			
		}
	}
	infile.close();

	p = firstC;
	while (p->next != nullptr)
		p = p->next;
	
	q = firstS;
	while (q->next != nullptr)
		q = q->next;
	//p and q now point to the last account in the lists

	//printAll(firstC);
	//printAll(firstS);
		
	//All accounts have been loaded from the file.
	checkingAccount *userCAccount;
	savingsAccount *userSAccount;
	std::string searchName, password;

	START:
	startupPrompt();
	std::cin >> c;
	switch (c) {
	case 'l':
		std::cout << "\nLOG IN:" << std::endl;
		std::cout << "Are you logging into a checking account or a savings account?"
			<< std::endl;
		std::cout << "- checking account (press 0)" << std::endl;
		std::cout << "- savings account (press 1)" << std::endl;
		inputPrompt();
		std::cin >> type;
		if (!type) {
			std::cout << "\nChecking Account Log In:" << std::endl;
			std::cout << "Enter your account name: ";
			std::cin.clear();
			std::cin.ignore(100, '\n');
			std::getline(std::cin, searchName);
			std::cout << "Enter your password: ";
			std::cin >> password;
			p->next = findAccount(firstC, searchName, 0);
			if (p->next == nullptr) {
				std::cout << "\nWe do not have records of such an account.\n"
					<< std::endl;
				goto START;
			}
			userCAccount = p->next;
		} else {
			std::cout << "\nSavings Account Log In:" << std::endl;
			std::cout << "Enter your account name: ";
			std::cin.clear();
			std::cin.ignore(100, '\n');
			std::getline(std::cin, searchName);
			std::cout << "Enter your password: ";
			std::cin >> password;
			q->next = findAccount(firstS, searchName, 0);
			if (q->next == nullptr) {
				std::cout << "\nWe do not have records of such an account.\n"
					<< std::endl;
				goto START;
			}
			userSAccount = q->next;
		}
		std::cout << "Successfully logged in!\n" << std::endl;
		break;
	case 's':
		std::cout << "\nSIGN UP:" << std::endl;
		std::cout << "Are you creating a checking account or a savings account?"
			<< std::endl;
		std::cout << "- checking account (press 0)" << std::endl;
		std::cout << "- savings account (press 1)" << std::endl;
		inputPrompt();
		std::cin >> type;
		if (!type)
			userCAccount = p->next = newCAccount();
		else 
			userSAccount = q->next = newSAccount();
		printf("\n");
		break;
	default:
		return userQuit();
	}
	//At this point one of the account ponters should hold the 
	//current user's account and type should reflect the type 
	//of account that the user created or logged in to.
	void *userAccount;
	if (!type)
		userAccount = userCAccount;
	else 
		userAccount = userSAccount;
	
	//EXEC(type, userAccount, info());
	ASSIGN(currentUser, type, userAccount, getAccountName());
	std::cin.clear();
	std::cin.ignore(255, '\n');
	while (1) {
		mainPrompt();
		std::cin >> c;
		switch (c) {
		case 'v':
			std::cout << "\n***************************************";
			EXEC(type, userAccount, info());
			std::cout << "***************************************\n" << std::endl;
			break;
		case 'q':
			return userQuit();
		default:
			std::cout << "Invalid option." << std::endl;
		}
	}
}

checkingAccount *newCAccount() {
	checkingAccount *cTemp = nullptr;
	std::string plan;
	char c;
	double initBalance;
	double minBal;
	double sCharges;
	double rate;

	std::cout << "\n...creating a new checking account\n" << std::endl;
	std::cout << "Under what name will you be creating this account?" << std::endl;
	inputPrompt();
	std::cin >> currentUser;
	std::cout << "\nThe Bank of Nessus has three checking account plans:\n" << std::endl;
	std::cout << "|Basic (press b)       |Aggressive (press a)    |Exultant (press e)       |" << std::endl;
	std::cout << "|Minimum Balance: $0.00|Minimum Balance: $500.00|Minimum Balance: $8900.00|" << std::endl; 
	std::cout << "|Service Charges: $0.00|Service Charges: $50.00 |Service Charges: $1000.00|" << std::endl; 
	std::cout << "|Interest Rate:   0.01%|Interest Rate:    5.00% |Interest Rate:     15.00%|\n" << std::endl; 
	inputPrompt();
	std::cin >> c;

	switch (c) {
	case 'b':
		plan = "Basic";
		break;
	case 'a':
		plan = "Aggressive";
		break;
	case 'e':
		plan = "Exultant";
		break;
	default:
		plan = "Basic";
	}

	std::cout << "\nYou chose the " << plan << " plan." << std::endl;
	std::cout << "Initial deposit: $";
	std::cin >> initBalance;
	signFix(initBalance);
	checkingPlan(plan, minBal, sCharges, rate);			
	cTemp = new checkingAccount(currentUser, initBalance, minBal, sCharges, rate);
	return cTemp;
}

savingsAccount *newSAccount() {
	savingsAccount *sTemp = nullptr;
	std::string plan;
	char c;
	double initBalance;
	double rate;

	std::cout << "\n...creating a new savings account\n" << std::endl;
	std::cout << "Under what name will you be creating this account?" << std::endl;
	inputPrompt();
	std::cin >> currentUser;
	std::cout << "\nThe Bank of Nessus has two checking account plans:\n" << std::endl;
	std::cout << "|Turtle (press t)     |Fox (press f)        |" << std::endl;
	std::cout << "|Interest Rate: 0.50% |Interest Rate: 5.00% |\n" << std::endl; 
	inputPrompt();
	std::cin >> c;

	switch (c) {
	case 't':
		plan = "Turtle";
		break;
	case 'f':
		plan = "Fox";
		break;
	default:
		plan = "Turtle";
	}

	std::cout << "\nYou chose the " << plan << " plan." << std::endl;
	std::cout << "Initial deposit: $";
	std::cin >> initBalance;
	signFix(initBalance);
	savingsPlan(plan, rate);			
	sTemp = new savingsAccount(currentUser, initBalance,rate);
	return sTemp;
}

void startupPrompt() {
	std::cout << "***************************************" << std::endl;
	std::cout << "* >> Welcome to the Bank of Nessus << *" << std::endl;
	std::cout << "***************************************" << std::endl;
	std::cout << "        Now serving " << *totalAccounts << " accounts!" << std::endl;
	std::cout << "- log in (press l)" << "\n- sign up (press s)" << std::endl;
	std::cout << "- quit (press q)" << std::endl;
	inputPrompt();
}

void mainPrompt() {
	std::cout << "***************************************" << std::endl;
	std::cout << "* >> Welcome to the Bank of Nessus << *" << std::endl;
	std::cout << "***************************************" << std::endl;
	std::cout << "        Now serving " << *totalAccounts << " accounts!" << std::endl;
	std::cout << "- view account (press v)" << std::endl;
	std::cout << "- deposit (press d)" << std::endl;
	std::cout << "- withdraw (press w)" << std::endl;
	if (!type)
		std::cout << "- write check (press c)" << std::endl;
	std::cout << "- quit (press q)" << std::endl;
	inputPrompt();
}

int userQuit() {
	std::cout << "\nThank you for choosing the Bank of Nessus!" << std::endl;
	return 0;
}

void checkingPlan(std::string plan, double &minBalance, double &serviceCharges, double &rate) {
	if (!plan.compare("Basic")) {
		minBalance = 0.0;
		serviceCharges = 0.0;
		rate = 0.0001;
	} else if (!plan.compare("Aggressive")) {
		minBalance = 500.00;
		serviceCharges = 50.00;
		rate = 0.05;
	} else if (!plan.compare("Exultant")) {
		minBalance = 8900.00;
		serviceCharges = 1000.00;
		rate = 0.15;
	} else std::cout << "Invalid checking plan." << std::endl;
}

void savingsPlan(std::string plan, double &rate) {
	if (!plan.compare("Turtle"))
		rate = 0.005;
	else if (!plan.compare("Fox"))
		rate = 0.05;
	else std::cout << "Invalid savings plan." << std::endl;
}

