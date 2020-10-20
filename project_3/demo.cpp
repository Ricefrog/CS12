#include <iostream>
#include "bankAccount.h"
#include "checkingAccount.h"

bankAccount *rootAccount = bankAccount::root;

int main(void) {
	bankAccount test("BillyBob", 500);
	bankAccount test2("BillyBob", 600);
	test.info();
	printf("\n\n");
	test2.info();
	printf("\n\n");
	test.deposit(34);
	test2.withdraw(32);
	test.info();
	printf("\n\n");
	test2.info();
	printf("\n\n");
	test.info();
	printf("\n\n");
	test2.info();
	printf("\n\n");
	std::cout << "test: " << test.getTransactionStr() << std::endl;
	std::cout << "test2: " << test2.getTransactionStr() << std::endl;
	return 0;
}
