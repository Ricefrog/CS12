/*Define  theclassbankAccountto  implement  the  basic  properties  of  abank  account.  An  object  of  thisclassshould  store  the  following  data:Account  holder’s  name  (string),  account  number  (int),  account  type(string, checking/saving), balance (double), and interest rate (double).(Store interest rate as a decimal number.) Add appropriate member func-tions  to  manipulate  an  object.  Use  astaticmember  in  theclasstoautomatically assign account numbers. Also declare an array of 10 compo-nents  of  typebankAccountto  process  up  to  10  customers  and  write  aprogram to illustrate how to use yourclass.*/

#include <iostream>
#include <string>

using namespace std;

class bankAccount {

public:
    //constructor, parameter order => name, account type, initial balance
    bankAccount(string = "Anonymous", string = "Checking", double = 0.00);
    //change info after initialization
    void changeInfo(string = "none", string = "none", double = 0.00);
    //deposits money, returns new balance.
    double deposit(double);
    //withdraws money, returns new balance
    double withdraw(double);
    //prints account info
    void info() const;
    static int totalAccounts;
    //get balance bu itself
    double getBalance() {
        return accountBalance;
    }
private:
    string accountName;
    int accountNumber;
    string accountType;
    double accountBalance;
    const double interestRate = 0.02;
};

//initialize account counter
int bankAccount::totalAccounts = 0;

//constructor
bankAccount::bankAccount(string name, string accType, double balance) {
    accountName = name;

    accType[0] = toupper(accType[0]);
    if (accType != "Checking" && accType != "Savings") {
        cout << "\nInvalid account type. Setting to default.(Checking)\n";
        accountType = "Checking";
    } else
        accountType = accType;
    
    accountBalance = balance;
    accountNumber = 13370 + ++totalAccounts;
}

//change info after initialization. Will only change defaults if specified
void bankAccount::changeInfo(string name, string accType, double balance) {
    if (name != "none")
        accountName = name;
    if (accType != "none")
        accountType = accType;
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
    cout << "\nInsufficient funds.\n";
    return -90000;
}

void bankAccount::info() const {
    printf("\nAccount Number: %d\n", accountNumber);
    cout << "Account Holder: " << accountName;
    cout << "\nAccount Type: " << accountType;
    printf("\nBalance: $%.2f\nInterest Rate: %.2f\%\n", accountBalance, 100*interestRate);
}


