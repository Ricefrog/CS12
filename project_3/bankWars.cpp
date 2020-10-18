#include <iostream>
#include "bankAccount.h"

bankAccount *rootAccount = bankAccount::root;

int main(void) {
	bankAccount test("BillyBob", 500);
	bankAccount test2("BillyBob", 600);
	test.info();
	printf("\n");
	test2.info();
	return 0;
}
