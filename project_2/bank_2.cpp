#include <iostream> 					//Koa Calloway 
#include <iomanip>						//CS12 Project 2
#include <fstream>						//10/15/20
#include "bankAccount.h"
#include "checkingAccount.h"
#include "savingsAccount.h"

#define inputPrompt() std::cout << "[" << currentUser << "@nessus]$ "

#define EXEC(type, ptr, member)\
	if (!type)\
		(static_cast<checkingAccount*>(ptr))->member;\
	else \
		(static_cast<savingsAccount*>(ptr))->member;

#define ASSIGN(lVal, type, ptr, member)\
	if (!type)\
		lVal = (static_cast<checkingAccount*>(ptr))->member;\
	else \
		lVal = (static_cast<savingsAccount*>(ptr))->member;

checkingAccount *newCAccount(); 
savingsAccount *newSAccount();
void startupPrompt();
void mainPrompt();
int userQuit(checkingAccount*, savingsAccount*);
void saveData(checkingAccount*, savingsAccount*);

//will modify minimum balance, service charges, and interest rate
//based on the plan specified in the string variable
void checkingPlan(std::string, double&, double&, double&);
//will modify interestRate variable based on the plan specified
void savingsPlan(std::string, double&);
bool allDigits(std::string);

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
	infile.open("datastore.txt");

	//load accounts from file.
	while (infile >> checkEnd) {

		if (!checkEnd.compare("endfile"))
			break;
		for (int i = checkEnd.length()-1; i >= 0; i--)
			infile.putback(checkEnd[i]);

		std::string name = "";
		std::string accountType;
		std::string tempStr;
		std::string plan;
		std::string pass;
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

		//tempStr now holds the account type
		accountType = tempStr;
		infile >> initBalance;
		infile >> plan;
		infile >> pass;
		if (accountType == "Checking") {
			double minBal = 0.0;
			double sCharges = 0.0;
			double rate = 0.0;

			checkingPlan(plan, minBal, sCharges, rate);			
			cTemp = new checkingAccount(name, initBalance, minBal, sCharges, rate, pass);
			
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
			sTemp = new savingsAccount(name, initBalance, rate, pass);

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

	//p and q now point to the last account of their account lists.
	//All accounts have been loaded from the file.

	checkingAccount *userCAccount;
	savingsAccount *userSAccount;
	std::string searchName, password;

	//Log In, Sign Up, or Quit
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
			userCAccount = findAccount(firstC, searchName, 0);
			if (userCAccount == nullptr) {
				std::cout << "\nWe do not have records of such an account.\n"
					<< std::endl;
				goto START;
			} else if (password.compare(userCAccount->getPassword()) != 0) {
				std::cout << "\nPassword does not match.\n" << std::endl;
				goto START;
			}
		} else {
			std::cout << "\nSavings Account Log In:" << std::endl;
			std::cout << "Enter your account name: ";
			std::cin.clear();
			std::cin.ignore(100, '\n');
			std::getline(std::cin, searchName);
			std::cout << "Enter your password: ";
			std::cin >> password;
			userSAccount = findAccount(firstS, searchName, 0);
			if (userSAccount == nullptr) {
				std::cout << "\nWe do not have records of such an account.\n"
					<< std::endl;
				goto START;
			} else if (password.compare(userSAccount->getPassword()) != 0) {
				std::cout << "\nPassword does not match.\n" << std::endl;
				goto START;
			}
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
		return userQuit(firstC, firstS);
	}
	//one of these account pointers points to the account that the 
	//current user has created or logged in to.
	void *userAccount;
	if (!type)
		userAccount = userCAccount;
	else 
		userAccount = userSAccount;
	
	ASSIGN(currentUser, type, userAccount, getAccountName());
	std::cin.clear();
	std::cin.ignore(255, '\n');
	std::cout << std::fixed << std::setprecision(2);
	
	//main selection prompt
	while (1) {
		double amount;
		double balance;
		double newBal;
		std::string search;
		int num;
		checkingAccount *found = nullptr;
		ASSIGN(balance, type, userAccount, getBalance());

		mainPrompt();
		std::cin >> c;
		switch (c) {
		case 'v':
			std::cout << "\n***************************************";
			EXEC(type, userAccount, info());
			std::cout << "***************************************\n" << std::endl;
			break;
		case 'd':
			std::cout << "\n***************************************" << std::endl;
			std::cout << "Current Balance: $" << balance << std::endl; 
			std::cout << "How much would you like to deposit?: $";
			std::cin >> amount;
			signFix(amount);
			ASSIGN(newBal, type, userAccount, deposit(amount));
			std::cout << "Successfully deposited $" << amount << "." << std::endl;
			std::cout << "***************************************\n" << std::endl;
			break;
		case 'w':
			std::cout << "\n***************************************" << std::endl;
			std::cout << "Current Balance: $" << balance << std::endl;
			std::cout << "How much would you like to withdraw?: $";
			std::cin >> amount;
			signFix(amount);
			ASSIGN(newBal, type, userAccount, withdraw(amount));
			if (newBal >= 0)
				std::cout << "Successfully withdrew $" << amount << "." << std::endl;
			std::cout << "***************************************\n" << std::endl;
			break;
		case 'c':
			if (type) break;

			std::cout << "\n***************************************" << std::endl;
			std::cout << "Enter the account number or the name of the account holder: ";
			std::cin.clear();
			std::cin.ignore(100, '\n');
			std::getline(std::cin, search);
			if (allDigits(search)) {
				num = stoi(search);
				found = findAccount(firstC, "byNumber", num);
			} else 
				found = findAccount(firstC, search, 0);
			if (found == nullptr) {
				std::cout << "That account could not be found." << std::endl;
				std::cout << "***************************************\n" << std::endl;
				break;
			}
			std::cout << "Current Balance: $" << balance << std::endl;
			std::cout << "Enter the amount you would like to send to " << found->getAccountName()
				<< ": $";
			std::cin >> amount;
			signFix(amount);
			static_cast<checkingAccount*>(userAccount)->writeCheck(found, amount); 
			std::cout << "***************************************\n" << std::endl;
			break;
		case 'a':
			std::cout << "\n***************************************" << std::endl;
			printAll(firstS);
			printAll(firstC);
			std::cout << "\n***************************************\n" << std::endl;
			break;
		case 'q':
			return userQuit(firstC, firstS);
		default:
			std::cout << "Invalid option." << std::endl;
		}
	}
}

checkingAccount *newCAccount() {
	checkingAccount *cTemp = nullptr;
	std::string plan;
	std::string pass;
	char c;
	double initBalance;
	double minBal;
	double sCharges;
	double rate;

	std::cout << "\n...creating a new checking account\n" << std::endl;
	std::cout << "Under what name will you be creating this account?" << std::endl;
	inputPrompt();
	std::cin >> currentUser;
	std::cout << "Enter a password for your account: " << std::endl;
	inputPrompt();
	std::cin >> pass;
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
	cTemp = new checkingAccount(currentUser, initBalance, minBal, sCharges, rate, pass);
	return cTemp;
}

savingsAccount *newSAccount() {
	savingsAccount *sTemp = nullptr;
	std::string plan;
	std::string pass;
	char c;
	double initBalance;
	double rate;

	std::cout << "\n...creating a new savings account\n" << std::endl;
	std::cout << "Under what name will you be creating this account?" << std::endl;
	inputPrompt();
	std::cin >> currentUser;
	std::cout << "Enter a password for your account: " << std::endl;
	inputPrompt();
	std::cin >> pass;
	std::cout << "\nThe Bank of Nessus has two savings account plans:\n" << std::endl;
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
	sTemp = new savingsAccount(currentUser, initBalance, rate, pass);
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
	std::cout << "- view all accounts (press a)" << std::endl;
	std::cout << "- quit (press q)" << std::endl;
	inputPrompt();
}

int userQuit(checkingAccount *firstC, savingsAccount *firstS) {
	saveData(firstC, firstS);
	std::cout << "\nThank you for choosing the Bank of Nessus!" << std::endl;
	return 0;
}

void saveData(checkingAccount *firstC, savingsAccount *firstS) {
	std::string entry;
	checkingAccount *p = firstC;
	savingsAccount *q = firstS;

	std::ofstream outfile;
	outfile.open("datastore.txt");
	outfile << std::fixed << std::setprecision(2);
	outfile << "# name accountType initialBalance plan password\n";

	while (q != nullptr) {
		entry = "";
		entry += q->getAccountName();
		entry += '\t';
		entry += "Savings";
		entry += '\t';
		outfile << entry;
		outfile << q->getBalance();
		entry = '\t';
		if (q->getInterestRate() == 0.05)
			entry += "Fox";
		else 
			entry += "Turtle";
		entry += '\t';
		entry += q->getPassword();
		entry += '\n';
		outfile << entry;
		q = q->next;
	}

	while (p != nullptr) {
		entry = "";
		entry += p->getAccountName();
		entry += '\t';
		entry += "Checking";
		entry += '\t';
		outfile << entry;
		outfile << p->getBalance();
		entry = '\t';
		if (p->getMinimumBalance() == 0.00)
			entry += "Basic";
		else if (p->getMinimumBalance() == 500.00)
			entry += "Aggressive";
		else 
			entry += "Exultant";
		entry += '\t';
		entry += p->getPassword();
		entry += '\n';
		outfile << entry;
		p = p->next;
	}
	outfile << "endfile";
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

bool allDigits(std::string line) {
	    char* p;
		    strtol(line.c_str(), &p, 10);
			    return *p == 0;
}
