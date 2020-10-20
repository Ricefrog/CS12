#include <iostream>
#include <iomanip>
#include <chrono>
#include <ctime>

#ifndef B_TEST
#define B_TEST
std::string getCurrentTime();

template <class type>
void fixSign(type &num) {
	if (num < 0)
		num = -1 * num;
}

class bankAccount {
public:
	bankAccount(std::string = "anonymous", double = 0.0);

	std::string getAccountName() const;
	int getAccountNumber() const;
	double getAccountBalance() const;
	std::string getTransactionStr() const;

	double deposit(double);
	double withdraw(double);
	void info() const;
	
	bankAccount *next;
	static int totalAccounts;
	static bankAccount *root;
protected:
	std::string transactions;
private:
	int accountNumber;
	std::string accountName;
	double accountBalance;
};

bankAccount *bankAccount::root = nullptr;
int bankAccount::totalAccounts = 0;

bankAccount *getLastPtr() {
	bankAccount *cur = bankAccount::root;
	while ((cur = cur->next) != nullptr);

	return cur;
}

bankAccount *findName(std::string searchName, bankAccount *cur) {
	if (cur == nullptr)
		return cur;
	if (cur->getAccountName() == searchName)
		return bankAccount::root;
	return findName(searchName, cur->next);
}

bankAccount::bankAccount(std::string name, double balance) {
	transactions = "created("+getCurrentTime()+")";

	char nameModifier = 'S';
	fixSign(balance);
	accountBalance = balance;

	while (findName(name, root) != nullptr) {
		nameModifier++;
		name.push_back(nameModifier);
	}
	if (nameModifier != 'S') {
		std::cout << "\nSomeone already has an account "
			"with that name.\nYour account name was changed "
			"to " << name << "." << std::endl;
	}
	accountName = name;

	totalAccounts++;
	accountNumber = 7432760 + totalAccounts;

	if (root != nullptr) {
		bankAccount *temp = getLastPtr();
		temp = this;
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

std::string bankAccount::getTransactionStr() const {
	return transactions;
}

double bankAccount::deposit(double amount) {
	fixSign(amount);
	std::string temp = "deposit("+std::to_string(amount)+")";
	transactions += temp;
	return (accountBalance += amount);
}
 
double bankAccount::withdraw(double amount) {
	fixSign(amount);
	if (accountBalance - amount >= 0) {
		std::string temp = "withdraw("+std::to_string(amount)+")";
		transactions += temp;
		return (accountBalance -= amount);
	}
	std::cout << "\nInsufficient funds.\n";
	return -1;
}

void bankAccount::info() const {
	std::cout << std::fixed << std::setprecision(2);
	std::cout << "Account Number: " << accountNumber << std::endl;
	std::cout << "Account Name: " << accountName << std::endl;
	std::cout << "Balance: " << accountBalance;
}

std::string getCurrentTime() {
	auto curTime = std::chrono::system_clock::now();
	std::time_t time = std::chrono::system_clock::to_time_t(curTime);
	std::string timeStr = std::ctime(&time);
	timeStr.pop_back();
	return timeStr;
}
#endif
