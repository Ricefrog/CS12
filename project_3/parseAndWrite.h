#include <iostream>
#include <fstream>
#include "bankAccount.h"

void saveData(bankAccount*);

void saveData(bankAccount *root) {
	bankAccount *current = root;
	std::string entry;
	std::ofstream outfile;
	outfile.open("dataStore.txt");
	while (current != nullptr) {
		entry = "";
		accountType currentType = current->getAccountType();
		outfile << std::fixed << std::setprecision(2) << currentType;
		outfile << " " << current->getAccountNumber() << " ";
		outfile << current->getAccountName() << " ";
		outfile << current->getAccountBalance();
		switch (currentType) {
		case sCC:
			break;
		case nSCC:
			break;
		case hIC:
			break;
		case cOD:
			break;
		case sA:
			break;
		case hIS:
			std::cout << "hIS";
		}
		outfile << "\n" << current->getTransactionStr() << "\n";
		current = current->next;
	}
}
