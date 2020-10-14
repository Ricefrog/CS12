#include <iostream>
#include "bankAccount.h"
#include "checkingAccount.h"
#include <fstream>

#define inputPrompt() std::cout << "[" << currentUser << "@nessus]$ "
checkingAccount *newCAccount(); 
void startupPrompt();
int userQuit();

//will modify minimum balance, service charges, and interest rate
//based on the plan specified in the string variable
void checkingPlan(std::string, double&, double&, double&);

//returns account by number or by name
checkingAccount *findCAccount(checkingAccount*, std::string, int = 0);

void printAllChecking(checkingAccount*);

//This string is used in all the prompts
std::string currentUser = "user";

int main(void) {
	char c;
	int *totalAccounts = &bankAccount::totalAccounts;
	checkingAccount *firstC = nullptr;
	checkingAccount *cTemp = nullptr;
	checkingAccount *p = nullptr;
	//savingsAccount *sTemp;
	std::ifstream infile;
	infile.open("input.txt");
	std::string checkEnd;

	while (infile >> checkEnd) {
		if (!checkEnd.compare("endfile"))
			break;
		for (int i = checkEnd.length()-1; i >= 0; i--)
			infile.putback(checkEnd[i]);

		std::string name = "";
		std::string accountType;
		std::string tempStr;
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
		if (accountType == "Checking") {
			std::string plan;
			infile >> plan;
			double minBal = 0.0;
			double sCharges = 0.0;
			double rate = 0.0;
			checkingAccount *p;

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
		} else ;
	}
	p = firstC;
	while (p->next != nullptr)
		p = p->next;
	//printAllChecking(firstC);
	
	//All accounts have been loaded from the file.
	//0 for checking account, 1 for savings account
	bool type = 0;
	checkingAccount *userAccount;
	//savingsAccount *userAccount;
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
			std::cout << "\nEnter your account name: ";
			std::cin.clear();
			std::cin.ignore(100, '\n');
			std::getline(std::cin, searchName);
			std::cout << "Enter your password: ";
			std::cin >> password;
			p->next = userAccount = findCAccount(firstC, searchName, 0);
			if (userAccount == nullptr) {
				std::cout << "\nWe do not have records of such an account.\n"
					<< std::endl;
				goto START;
			}
		}
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
			p->next = userAccount = newCAccount();
		userAccount->info();
		break;
	default:
		return userQuit();
	}
	//At this point one of the account ponters should hold the 
	//current user's account.

	userAccount->info();
	return 0;
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
	std::cout << "\nThe Bank of Nessus has three checking account plans:" << std::endl;
	std::cout << "|Basic (press b)       |Aggressive (press a)    |Exultant (press e)       |" << std::endl;
	std::cout << "|Minimum Balance: $0.00|Minimum Balance: $500.00|Minimum Balance: $8900.00|" << std::endl; 
	std::cout << "|Service Charges: $0.00|Service Charges: $50.00 |Service Charges: $1000.00|" << std::endl; 
	std::cout << "|Interest Rate:   0.01%|Interest Rate:    5.00% |Interest Rate:     15.00%|" << std::endl; 
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
	checkingPlan(plan, minBal, sCharges, rate);			
	cTemp = new checkingAccount(currentUser, initBalance, minBal, sCharges, rate);
	return cTemp;
}

void startupPrompt() {
	std::cout << "***************************************" << std::endl;
	std::cout << "* >> Welcome to the Bank of Nessus << *" << std::endl;
	std::cout << "***************************************" << std::endl;
	std::cout << "- log in (press l)" << "\n- sign up (press s)" << std::endl;
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
	}
}

checkingAccount *findCAccount(checkingAccount *cur, std::string name, int number) {
	if (cur == nullptr)
		return nullptr;
	if (!name.compare("byNumber")) {
		if (cur->getAccountNumber() == number)
			return cur;
		return findCAccount(cur->next, "byNumber", number);
	} else {
		if (cur->getAccountName() == name)
			return cur;
		return findCAccount(cur->next, name, 0);
	}
}

void printAllChecking(checkingAccount *cur) {
	if (cur == nullptr)
		return;
	cur->info();
	printAllChecking(cur->next);
}
