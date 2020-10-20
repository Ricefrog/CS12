#include <iostream>
#include "bankAccount.h"
#ifndef C_TEST
#define C_TEST
class checkingAccount : public bankAccount {
public:
	virtual	double writeCheck(double) = 0;
};
#endif
