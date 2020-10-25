#include <iostream>
#include "parseAndWrite.h"
#include "bankAccount.h"
#include "serviceChargeChecking.h"
#include "noServiceChargeChecking.h"
#include "highInterestChecking.h"
#include "savingsAccount.h"
#include "highInterestSavings.h"
#include "certificateOfDeposit.h"

int monthOffset = 0;
bool nameChangeNotification = false;
int main() {
	bankAccount *rootAccount = readData();
	printAllInfo(rootAccount);
	printAllTransactionStr(rootAccount);
	return 0;
}
