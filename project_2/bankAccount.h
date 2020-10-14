#include <iostream>
#include <string>

#ifndef B_TEST
#define B_TEST
class bankAccount {

public:
    //constructor, parameter order => name, account type, initial balance
    bankAccount(std::string = "Anonymous", double = 0.00);
    //change info after initialization
    void changeInfo(std::string = "none", double = 0.00);
    //deposits money, returns new balance.
    double deposit(double);
    //withdraws money, returns new balance
    double withdraw(double);
    //prints account info
    void info() const;
    static int totalAccounts;
    //get balance bu itself
    double getBalance() const {
        return accountBalance;
    }
	//retrieve account number
	int getAccountNumber() const {
		return accountNumber;
	}

	//retrieve account name
	std::string getAccountName() const {
		return accountName;
	}
private:
    std::string accountName;
    int accountNumber;
    double accountBalance;
};

//initialize account counter
int bankAccount::totalAccounts = 0;

//constructor
bankAccount::bankAccount(std::string name, double balance) {
    accountName = name;
    accountBalance = balance;
    accountNumber = 13370 + ++totalAccounts;
}

//change info after initialization. Will only change defaults if specified
void bankAccount::changeInfo(std::string name, double balance) {
    if (name != "none")
        accountName = name;
    if (balance != 0.00)
        accountBalance = balance;
}

double bankAccount::deposit(double amount) {
    //do nothing if negative amount
    if (amount < 0)
        return 0;
    return (accountBalance += amount);
}

double bankAccount::withdraw(double amount) {
    if (amount < 0)
        amount = -1 * amount;
    if (accountBalance - amount >= 0)
        return (accountBalance -= amount);
    std::cout << "\nInsufficient funds.\n";
    return -90000;
}

void bankAccount::info() const {
    printf("\nAccount Number: %d\n", accountNumber);
    std::cout << "Account Holder: " << accountName;
    printf("\nBalance: $%.2f\n", accountBalance);
}
#endif
