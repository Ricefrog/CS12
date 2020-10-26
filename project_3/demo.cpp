#include <iostream>
#include "parsingEtc.h"
#include "bankAccount.h"
#include "serviceChargeChecking.h"
#include "noServiceChargeChecking.h"
#include "highInterestChecking.h"
#include "savingsAccount.h"
#include "highInterestSavings.h"
#include "certificateOfDeposit.h"

bool nameChangeNotification = true;
int monthOffset = 0;

int main(void) {
	std::cout << "Service Checking: " << std::endl;
	serviceChargeChecking test1(sCC, "BillyBob", 500);
	serviceChargeChecking test2(sCC, "BillyBob", 600);
	bankAccount *rootAccount = bankAccount::root;
	test1.info();
	printf("\n\n");
	test2.info();
	printf("\n\n");
	test1.deposit(34);
	test2.withdraw(32);
	std::cout << "After deposit and withdrawal.\n" << std::endl;
	test1.info();
	printf("\n\n");
	test2.info();
	printf("\n\n");
	test1.writeCheck(400, &test2);
	std::cout << "After writing check.\n" << std::endl;
	test1.info();
	printf("\n\n");
	test2.info();
	printf("\n\n");
	std::cout << "test1: " << test1.getTransactionStr() << std::endl;
	std::cout << "test2: " << test2.getTransactionStr() << std::endl;

	std::cout << "\nnoService Checking:" << std::endl;
	noServiceChargeChecking test3(nSCC, "BillyBob", 500, 0.02, 135, 800);
	noServiceChargeChecking test4(nSCC, "BillyBob", 600, 0.03, 570, 900);
	test3.info();
	printf("\n\n");
	test4.info();
	printf("\n\n");
	test3.deposit(34);
	test4.withdraw(32);
	std::cout << "After deposit and withdrawal.\n" << std::endl;
	test3.info();
	printf("\n\n");
	test4.info();
	printf("\n\n");
	test3.writeCheck(400, &test4);
	std::cout << "After writing check.\n" << std::endl;
	test3.info();
	printf("\n\n");
	test4.info();
	printf("\n\n");
	std::cout << "test3: " << test3.getTransactionStr() << std::endl;
	std::cout << "test4: " << test4.getTransactionStr() << std::endl;

	std::cout << "\nHighInterest Checking:" << std::endl;
	highInterestChecking test5(hIC, "BillyBob", 500, 0.02, 135, 800);
	highInterestChecking test6(hIC, "BillyBob", 600, 0.03, 570, 900);
	test5.info();
	printf("\n\n");
	test6.info();
	printf("\n\n");
	test5.deposit(34);
	test6.withdraw(32);
	std::cout << "After deposit and withdrawal.\n" << std::endl;
	test5.info();
	printf("\n\n");
	test6.info();
	printf("\n\n");
	test5.writeCheck(400, &test6);
	std::cout << "After writing check.\n" << std::endl;
	test5.info();
	printf("\n\n");
	test6.info();
	printf("\n\n");
	std::cout << "test5: " << test5.getTransactionStr() << std::endl;
	std::cout << "test6: " << test6.getTransactionStr() << std::endl;

	std::cout << "\nSavings Account:" << std::endl;
	savingsAccount test7(sA, "BillyBob", 500, 0.02);
	savingsAccount test8(sA, "BillyBob", 600, 0.03);
	test7.info();
	printf("\n\n");
	test8.info();
	printf("\n\n");
	test7.deposit(34);
	test8.withdraw(32);
	std::cout << "After deposit and withdrawal.\n" << std::endl;
	test7.info();
	printf("\n\n");
	test8.info();
	printf("\n\n");
	std::cout << "test7: " << test7.getTransactionStr() << std::endl;
	std::cout << "test8: " << test8.getTransactionStr() << std::endl;

	std::cout << "\nhighInterestSavings Account:" << std::endl;
	highInterestSavings test9(hIS, "BillyBob", 500, 0.02, 35, 50);
	highInterestSavings test10(hIS, "BillyBob", 600, 0.03, 40, 60);
	test9.info();
	printf("\n\n");
	test10.info();
	printf("\n\n");
	test9.deposit(34);
	test10.withdraw(567);
	std::cout << "After deposit and withdrawal.\n" << std::endl;
	test9.info();
	printf("\n\n");
	test10.info();
	printf("\n\n");
	newMonth(rootAccount);
	std::cout << "test9: " << test9.getTransactionStr() << std::endl;
	std::cout << "test10: " << test10.getTransactionStr() << std::endl;

	std::cout << "\ncertificateOfDeposit:" << std::endl;
	certificateOfDeposit test11(cOD, "BillyBob", 500, 0.02, 5);
	certificateOfDeposit test12(cOD, "BillyBob", 600, 0.03, 7);
	test11.info();
	printf("\n\n");
	test12.info();
	printf("\n\n");
	test11.deposit(34);
	test12.withdraw(567);
	std::cout << "After deposit and withdrawal.\n" << std::endl;
	test11.info();
	printf("\n\n");
	test12.info();
	printf("\n\n");
	std::cout << "test11: " << test11.getTransactionStr() << std::endl;
	std::cout << "test12: " << test12.getTransactionStr() << std::endl;
	saveData(rootAccount);
	return 0;
}
