#include <iostream>
#include <iomanip>

template <class type>
void fixSign(type &num) {
	if (num < 0)
		num = -1 * num;
}

class bankAccount {
public:
	bankAccount(std::string = "anonymous", double = 0.0);
	std::string getAccountName() const;
	void info() const;
	
	bankAccount *next;
	static int totalAccounts;
	static bankAccount *root;
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

void bankAccount::info() const {
	std::cout << std::fixed << std::setprecision(2);
	std::cout << "Account Number: " << accountNumber << std::endl;
	std::cout << "Account Name: " << accountName << std::endl;
	std::cout << "Balance: " << accountBalance;
}


