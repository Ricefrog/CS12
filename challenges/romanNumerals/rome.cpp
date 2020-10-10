#include <iostream>
#include "romanType.h"

using namespace std;

int prompt(romanType&, char*);
void newNumerals(romanType&, char*);

int main() {
	char s[] = "V";
	romanType athens(s);
	newNumerals(athens, s);
	while(prompt(athens, s)!=0);

	return 0;
}

int prompt(romanType &athens, char *s) {
	int val = athens.getValue();
	cout << "Roman numerals: " << athens.getNumerals();
	cout << "\nValue: " << val << endl;
	cout << "New value (1)" << endl;
	cout << "Quit (0)\n-> ";
	cin >> val;
	if (val)
		newNumerals(athens, s);
	return val;
}

void newNumerals(romanType &athens, char *s) {
	cout << "Please enter Roman numerals: ";
	cin >> s;
	cout << endl;
	athens.changeNumerals(s);
}
