#include <iostream>
#include "bankAccount.h"

#ifndef CERT_TEST
#define CERT_TEST
class certificateOfDeposit : public bankAccount {
public:
	//Parameters: accoutnType, accountName, accountBalance, interestRate, 
	//maturityMonths, currentMonths
	certificateOfDeposit(accountType = cOD, std::string = "anonymous", double = 0.0, double = 0.0,
			int = 5, int = 0);
	int incrementMonths();
	double getInterestRate() const;
	int getCurrentMonths() const;
	void setCurrentMonths(int);
	int getMaturityMonths() const;
	bool isMature() const;

	double withdraw(double) override;
	double deposit(double) override;
	double receive(double, bankAccount*) override;
	void info() const override;
private:
	double interestRate;
	int maturityMonths;
	int currentMonths;
};

certificateOfDeposit::certificateOfDeposit(accountType t, std::string name, double balance, 
		double rate, int mMonths, int cMonths)
		: bankAccount(t, name, balance) {
	fixSign(rate);
	interestRate = rate;
	fixSign(mMonths);
	maturityMonths = mMonths;
	fixSign(cMonths);
	currentMonths = cMonths;
}

int certificateOfDeposit::incrementMonths() {
	currentMonths++;
	return currentMonths;
}

double certificateOfDeposit::getInterestRate() const {
	return interestRate;
}

int certificateOfDeposit::getCurrentMonths() const {
	return currentMonths;
}

void certificateOfDeposit::setCurrentMonths(int m) {
	fixSign(m);
	currentMonths = m;
}

int certificateOfDeposit::getMaturityMonths() const {
	return maturityMonths;
}

bool certificateOfDeposit::isMature() const {
	return (currentMonths >= maturityMonths);
}

//Returns -2 if certificate is not ready to be withdrawn.
//Returns -1 if the account has inssuficient funds.
//Otherwise returns the balance after withdrawal.
double certificateOfDeposit::withdraw(double amount) {

	if (currentMonths < maturityMonths && !battleMode) {
		std::cout << "\nYou certificate of deposit has not reached" <<
			" maturity yet." << std::endl;
		return -2;
	}

	double myBalance = this->getAccountBalance();
	fixSign(amount);
	if ((myBalance -= amount) < 0 && !battleMode) {
		std::cout << "\nInsufficient funds." << std::endl;
		return -1;
	}

	std::string temp = "withdraw("+std::to_string(amount)+","
		+getCurrentTime()+")";
	transactions += temp;
	std::cout << "cOD withdraw, myBalance: " << myBalance << std::endl;
	if (myBalance < 0)
		myBalance = 0;
	this->setAccountBalance(myBalance);
	return myBalance;
}

//Returns -1 if not battleMode
double certificateOfDeposit::deposit(double amount) {
	if (!battleMode) {
		std::cout << "\nYou can only deposit once." << std::endl;
		return -1;
	}
	double myBalance = this->getAccountBalance();
	fixSign(amount);
	myBalance += amount;
	this->setAccountBalance(myBalance);
	return myBalance;
}

double certificateOfDeposit::receive(double t, bankAccount *b) {
	std::cout << "\nThis account cannot receive checks" << std::endl;
	return -1;
}

void certificateOfDeposit::info() const {
	bankAccount::info();
	std::cout << "\nInterest Rate: " << 100*interestRate << "%" << std::endl;
	std::cout << "Months until mature: "; 
	if (maturityMonths - currentMonths > 0)
		std::cout << (maturityMonths - currentMonths) << std::endl;
	else 
		std::cout << "Mature" << std::endl;
}
#endif
