#include <iostream>
#include "bankAccount.h"

class checkingAccount: public bankAccount {
public:
	//constructor
	//name, balance, minimum balance, service charge, interest rate
	checkingAccount(std::string = "Anonymous", double = 0.0, double = 0.0, double = 0.0, double = 0.0, std::string = "password");

	void setInterestRate(double);
	double getInterestRate() const;

	//Returns the balance in x number of years, interest is assumed to compound annually
	//double interestGains(int) const;

	void setMinimumBalance(double);
	double getMinimumBalance() const;

	void setServiceCharges(double);
	double getServiceCharges() const;

	bool isAboveMinimum() const;

	double withdraw(double);
	
	//will transfer money to the account specified
	void writeCheck(checkingAccount*, double); 

	void info() const;
	checkingAccount *next;
private:
	double minimumBalance;
	//account is charged this fee once at the end of the month if account goeas under at all
	double serviceCharges;
	bool willBeCharged;
	double interestRate;
};

checkingAccount::checkingAccount(std::string name, double balance, double minBalance, double charge, double rate, std::string pass) 
	: bankAccount(name, balance, pass) {
	minimumBalance = minBalance;
	serviceCharges = charge;
	interestRate = rate;
	willBeCharged = (balance < minBalance) ? true : false;
	next = nullptr;
}

void checkingAccount::setInterestRate(double rate) {
	if (rate < 0)
		rate = -1 * rate;
	interestRate = rate;
}

double checkingAccount::getInterestRate()  const {
	return interestRate;
}

void checkingAccount::setMinimumBalance(double minBal) {
 	if (minBal < 0)
		minBal = -1 * minBal;
	minimumBalance = minBal;
}

double checkingAccount::getMinimumBalance() const {
	return minimumBalance; 
}

void checkingAccount::setServiceCharges(double sCharges) {
	if (sCharges < 0)
		sCharges = -1 * sCharges;
}

double checkingAccount::getServiceCharges() const {
	return serviceCharges;
}

bool checkingAccount::isAboveMinimum() const {
	return (getBalance() >= minimumBalance);
}

//If the return value is -90000 then the account had insufficient funds and nothing was withdrawn.
//If the return value is the same as the account balance previous to the function call
//then the withdrawal was cancelled.
//Otherwise, the function will return the new account balance.
double checkingAccount::withdraw(double amount) {
	double retVal = bankAccount::withdraw(amount);
	//will not continue if account has insufficient funds
	if (retVal >= 0) {
		if (!isAboveMinimum() && !willBeCharged) {
			char c;
			printf("\nWithdrawing $%.2f will put your account ", amount);
			printf("below the required minimum balance of $%.2f.\n", minimumBalance);
			printf("If you proceed, you will be charged $%.2f at the end of the month.", serviceCharges);
			printf("\nContinue?(y or n): ");
			std::cin >> c;

			if (tolower(c) == 'n') {
				printf("Withdrawal cancelled.\n");
				deposit(amount);
				return -90000;
			}

			willBeCharged = true;
		}
	}
	return retVal;
}

// In main, create another function to find an account by name or number. Error checking should also be done in main.
void checkingAccount::writeCheck(checkingAccount *toThisAccount, double amount) {
	if (checkingAccount::withdraw(amount) >= 0) {
		toThisAccount->deposit(amount);
		printf("You have written a check of $%.2f to ", amount);
		std::cout << toThisAccount->getAccountName()
			<< "'s checking account." << std::endl;
	}
}

void checkingAccount::info() const {
	bankAccount::info();	
	std::cout << "Account Type: Checking" << std::endl;
	std::string chargeStatus = willBeCharged ? "Yes" : "No"; 
	printf("Minimum Balance: $%.2f\n", minimumBalance);
	printf("Service Charges: $%.2f\n", serviceCharges);
	std::cout << "Charge Invoked: " << chargeStatus << std::endl;
	printf("Interest Rate: %.2f\%\n", 100 * interestRate);
}
