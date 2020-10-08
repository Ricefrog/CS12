#include <iostream>
#include <string>
#include "dayType.h"

using namespace std;
int prompt(dayType);

int main() {
    dayType myDay;
    string dayChoice;
    int offset;
    cout << "Choose the current day: ";
    cin >> dayChoice;
    myDay.setDay(dayChoice);
    printf("\n");
    while (prompt(myDay)) {
        cout << "By how many days would you like to increment/decrement?: ";
        cin >> offset;
        if (offset < 0) 
            for (int i = offset; i > 0; i--)
                myDay.setDay(myDay.returnPrevDay());
        else for (int i = 0; i < offset; i++)
                myDay.setDay(myDay.returnNextDay());
    }
    myDay.printDay();
    return 0;
}

int prompt(dayType myDay) {
    int choice;
    cout << "Current day: " << myDay.returnDay();
    cout << "\nWhat would you like to do?\nIncrement/decrement day: 1";
    cout << "\nExit: 0\n\nInput: ";
    cin >> choice;
    return choice; 
}
