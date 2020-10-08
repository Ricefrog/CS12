#include <iostream>
#include <string>

using namespace std;

class dayType {
public:
    dayType(string = "Sunday");
    void setDay(string);
    void printDay();
    string returnDay();
    string returnNextDay();
    string returnPrevDay();
private:
    int day;
};

string daysRef[] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday",
"Friday", "Saturday"};

int dayToNum(string d) {
    for (int i = 0; i < 7; i++) {
        if (daysRef[i] == d)
            return i;
    }
    return -1;
}

dayType::dayType(string selection) {
    setDay(selection);
}

string dayType::returnDay() {
    return daysRef[day];
}

string dayType::returnNextDay() {
    int num;
    if (day == 6)
        num = 0;
    else 
        num = day + 1;
    return daysRef[num];
}

string dayType::returnPrevDay() {
    int num;
    if (day == 0)
        num = 6;
    else 
        num = day - 1;
    return daysRef[num];
}

void dayType::printDay() {
    cout << returnDay();
}

void dayType::setDay(string newDay) {
     int c;
     newDay[0] = toupper(newDay[0]);
     //cout << "\nselection: " << newDay << endl;
     if ((c = dayToNum(newDay)) == -1) {
        printf("\nInvalid day. Setting to default(Sunday).");
        day = 0;
     } else day = c;
}
