#include <iostream>
#include <iomanip>
#include <chrono>
#include <ctime>

#ifndef B_TEST
#define B_TEST

//In main, set to true if user is creating account from console.
//Otherwise, set to false.
extern bool nameChangeNotification; 
extern int monthOffset;
enum accountType {sCC, nSCC, hIC, cOD, sA, hIS};
std::string getCurrentTime();

template <class type>
void fixSign(type &num) {
	if (num < 0)
		num = -1 * num;
}

class bankAccount {
public:
	bankAccount(accountType = sCC, std::string = "anonymous", double = 0.0);

	std::string getAccountName() const;
	int getAccountNumber() const;
	double getAccountBalance() const;
	void setAccountBalance(double);
	std::string getTransactionStr() const;
	void setTransactionStr(std::string);
	accountType getAccountType() const;

	virtual double deposit(double);
	virtual double withdraw(double);
	virtual double receive(double, bankAccount*);
	virtual void info() const;
	
	static int totalAccounts;
	bankAccount *next;
	static bankAccount *root;

protected:
	std::string transactions;
private:
	accountType type;
	int accountNumber;
	std::string accountName;
	double accountBalance;
};

bankAccount *bankAccount::root = nullptr;
int bankAccount::totalAccounts = 0;

bankAccount *getLastPtr() {
	bankAccount *cur = bankAccount::root;
	while (cur->next != nullptr)
		cur = cur->next;

	return cur;
}

bankAccount *findName(std::string searchName, bankAccount *cur) {
	if (cur == nullptr)
		return cur;
	if (cur->getAccountName() == searchName)
		return cur;
	return findName(searchName, cur->next);
}

void printAllInfo(bankAccount *current) {
	if (current == nullptr)
		return;
	current->info();
	printf("\n");
	printAllInfo(current->next);
}

void printAllTransactionStr(bankAccount *current) {
	if (current == nullptr)
		return;
	std::cout << current->getTransactionStr() << std::endl;
	printAllTransactionStr(current->next);
}

bankAccount::bankAccount(accountType t, std::string name, double balance) {
	transactions = "created("+getCurrentTime()+")";

	type = t;
	char nameModifier = 'S';
	fixSign(balance);
	accountBalance = balance;

	while (findName(name, root) != nullptr) {
		nameModifier++;
		name.push_back(nameModifier);
	}
	if (nameModifier != 'S' && nameChangeNotification) {
		std::cout << "\nSomeone already has an account "
			"with that name.\nYour account name was changed "
			"to " << name << "." << std::endl;
	}
	accountName = name;

	totalAccounts++;
	accountNumber = 7432760 + totalAccounts;

	if (root != nullptr) {
		bankAccount *temp = getLastPtr();
		temp->next = this;
	} else 
		root = this;
	next = nullptr;
}

std::string bankAccount::getAccountName() const {
	return accountName;
}

int bankAccount::getAccountNumber() const {
	return accountNumber;
};

double bankAccount::getAccountBalance() const {
	return accountBalance;
};

void bankAccount::setAccountBalance(double newBalance) {
	fixSign(newBalance);
	accountBalance = newBalance;
}

std::string bankAccount::getTransactionStr() const {
	return transactions;
}

void bankAccount::setTransactionStr(std::string str) {
	transactions = str;
}

accountType bankAccount::getAccountType() const {
	return type;
}

//Returns the balance after deposit.
double bankAccount::deposit(double amount) {
	fixSign(amount);
	std::string temp = "deposit("+std::to_string(amount)
		+","+getCurrentTime()+")";
	transactions += temp;
	return (accountBalance += amount);
}

//Returns -1 if the account does not have enough money.
//Otherwise returns the balance after withdrawal.
double bankAccount::withdraw(double amount) {
	fixSign(amount);
	if (accountBalance - amount >= 0) {
		std::string temp = "withdraw("+std::to_string(amount)
			+","+getCurrentTime()+")";
		transactions += temp;
		return (accountBalance -= amount);
	}
	return -1;
}

//Called when another account sends money.
//The sender's data and the amount received is stored in the
//transaction string. The amount received is returned.
double bankAccount::receive(double amount, bankAccount *sender) {
	std::string name = sender->getAccountName();
	int num = sender->getAccountNumber();
	std::string temp = "receive("+name+","+std::to_string(num)
		+","+std::to_string(amount)+")";
	transactions += temp;
	accountBalance += amount;
	return amount;	
}

void bankAccount::info() const {
	std::cout << std::fixed << std::setprecision(2);
	std::cout << "Account Type: ";
	switch (type) {
	case sCC:
		std::cout << "serviceChargeChecking" << std::endl;
		break;
	case nSCC:
		std::cout << "noServiceChargeChecking" << std::endl;
		break;
	case hIC:
		std::cout << "highInterestChecking" << std::endl;
		break;
	case cOD:
		std::cout << "certificateOfDeposit" << std::endl;
		break;
	case sA:
		std::cout << "savingsAccount" << std::endl;
		break;
	case hIS:
		std::cout << "highInterestSavings" << std::endl;
	}
	std::cout << "Account Number: " << accountNumber << std::endl;
	std::cout << "Account Name: " << accountName << std::endl;
	std::cout << "Balance: $" << accountBalance;
}

std::string getCurrentTime() {
	auto curTime = std::chrono::system_clock::now();
	std::time_t time = std::chrono::system_clock::to_time_t(curTime);
	std::string timeStr = std::ctime(&time);
	std::string thisMonth = timeStr.substr(4, 3);
	std::string months[12] = {"Jan", "Feb", "Mar",
						"Apr", "May", "Jun", 
						"Jul", "Aug", "Sep",
						"Oct", "Nov", "Dec"};
	int i = 0;
	while (months[i++] != thisMonth);
	std::string adjustedMonth = months[(--i + monthOffset)%12];
	timeStr.replace(4, 3, adjustedMonth);
	timeStr.pop_back();
	return timeStr;
}

void newMonth(bankAccount *cur) {
	if (cur == nullptr)
		return;
	std::string temp = cur->getTransactionStr();
	temp += "|";
	cur->setTransactionStr(temp);
	newMonth(cur->next);
}
#endif
