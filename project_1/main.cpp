//Author: Koa Calloway
#include <iostream>
#include <fstream>
#include <iomanip>
#include "bankAccount.h"

using namespace std;

char menuPrompt(int, string);

int main() {
    const int numberOfAccounts = 10;
    int count = 0;
    bankAccount accounts[numberOfAccounts];
    ifstream input;
    input.open("input.txt");
    
    while (count < numberOfAccounts) { //I was having trouble with !input.eof()
        char c, f = 0;                 //so I resorted to using a counter
        string buf = "", name = "", type;
        double balance;
        input.get(c);
        
        while (c == '#') { //skip commented lines
            while (c != '\n') {
                input.get(c);
            }
            input.get(c);
        }
        input.putback(c);

        input >> buf;
        while (buf != "Checking" && buf != "Savings") {
            if (f > 0)
                name += " ";
            name += buf;
            input >> buf;
            f++;
        }
            
        type = buf;
        input >> balance;
        input.get(c); //swallow trailing newline
        accounts[count++].changeInfo(name, type, balance);
    }
    input.close();

    //for (count = 0; count < numberOfAccounts; count++)
    //    accounts[count].info();
    string user = "user";
    string type;
    double balance;
    char p = menuPrompt(numberOfAccounts, user);
    if (p != 'v') {
        cout << "\nHave a nice day!"
            << "\nAuthor: Koa Calloway";
        return 0;
    }
    //user decided to make a new account
    cout << "Please enter your name: ";
    cin >> user;
    string tmpstr;
    getline(cin, tmpstr);
    user += tmpstr;
    //if (tmpstr.length() > 1)
    //    user.pop_back();    
    cout << "Is this a checking or savings account?: ";
    cin >> type;
    cout << "What is your initial deposit?: $";
    cin >> balance;
    bankAccount userAccount(user, type, balance);
    cout << "An account has been opened in your name.\n";
    
    while ((p = menuPrompt(numberOfAccounts, user)) != 'e') {
        cout << setprecision(2) << fixed;
        double amount;
        double b;
        cout << "\n********************************************************************\n";
        switch (p) {
        case 'v':
            userAccount.info();
            break;
        case 'd':
            cout << "\nCurrent balance: $" << userAccount.getBalance();
            cout << "\nHow much would you like to deposit?: $";
            cin >> amount;
            userAccount.deposit(amount);
            cout << "$" << amount << " has been deposited in your account.\n";
            break;
        case 'w':
            cout << "\nCurrent balance: $" << userAccount.getBalance();
            cout << "\nHow much would you like to withdraw?: $";
            cin >> amount;
            b = userAccount.withdraw(amount);
            if (b != -90000)
                cout << "$" << amount << " has been withdrawn from your account.\n";
            break;
        case 'a':
            for (int i = 0; i < numberOfAccounts; i++)
                accounts[i].info();
            userAccount.info();
            break;
        default:
            cout << "\nInvalid option.";
            break;
        }
        cout << "\n********************************************************************\n";
    }
    
    return 0;
}

char menuPrompt(int initAcc, string user) {
    int tot = bankAccount::totalAccounts;
    char choice;
    cout << "\n***| Welcome to the Bank of E |***";
    cout << "\n  Currently serving " << tot 
         << " accounts!\n";
    cout << "\nWhat would you like to do?";
    if (tot == initAcc)
        cout << "\n- Create a new account (press v)";
    else {
        cout << "\n- View my account (press v)"
             << "\n- Deposit (press d)"
             << "\n- Withdraw (press w)"
             << "\n- View all accounts (press a)";
    } 
    cout << "\n- Exit (e)\n\n[" << user << "@bank]$ ";
    cin >> choice;
    return choice;
}
