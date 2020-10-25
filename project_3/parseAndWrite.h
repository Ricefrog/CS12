#include <iostream>
#include <fstream>
#include "bankAccount.h"
#include "serviceChargeChecking.h"
#include "noServiceChargeChecking.h"
#include "highInterestChecking.h"
#include "savingsAccount.h"
#include "highInterestSavings.h"
#include "certificateOfDeposit.h"

bankAccount *readData(); 
void saveData(bankAccount*);

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
	while (counter++ < 12){
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
			std::cout << "hIS";
		}
		//transactions
		outfile << "\n" << current->getTransactionStr() << "\n";
		current = current->next;
	}
}
