#include <iostream>
#include <ctype.h>
#include <cstring>

int individualToInt(char);

using namespace std;

class romanType {
public:
	romanType(char*);
	int getValue();
	char *getNumerals();
	void changeNumerals(char*);
private:
	int value;
	char *numerals;
};

int numeralToInt(char *n) {
	int len = strlen(n);
	if (len == 1)
		return individualToInt(n[0]);
	int sum = 0;
	int vals[len];

	for (int i = 0; i < len; i++) {
		vals[i] = individualToInt(n[i]);
		printf("\nvals[%d] = %d", i, vals[i]);
	}
	printf("\n");

	for (int i = 0; i < len; i++) {
		int cur = vals[i];
		int next;
		if (i == len-1)
			next = 0;
		else next = vals[i+1];
		if (cur >= next) {
			sum += cur;
		} else {
			sum += (next - cur);
			i++;
		}
	}

	return sum;
}

int individualToInt(char c) {
	switch (c) {
	case 'M': return 1000;
	case 'D': return 500;
	case 'C': return 100;
	case 'L': return 50;
	case 'X': return 10;
	case 'V': return 5;
	case 'I': return 1;
	}
	return 69;
}

char *toCaps(char *s) {
	//cout << s << " received." << endl;
	char *t = s;
	while (*s != '\0') 
		*s++ = toupper(*s);
	return t;
}

bool isValidNumeral(char *numeral) {
	bool valid = true;
	char c;
	c = *numeral;
	
	do {
		switch (c) {
		case 'M': case 'D': case 'C': case 'L':
		case 'X': case 'V': case 'I': break;
		default: valid = false;
		}
	} while ((c = *(++numeral)) != '\0');
	
	return valid;
}

romanType::romanType(char *entry) { 
	entry = toCaps(entry);
	if (isValidNumeral(entry)) {
		numerals = entry;
	} else {
		//cout << "\nInvalid numeral. Setting to default(V)";
		numerals = entry;
		*entry++ = 'V';
		*entry = '\0';
	}
	value = numeralToInt(numerals);
}

int romanType::getValue() {
	//printf("\ngetValue called. value:%d\n", value);
	return value;
}

char *romanType::getNumerals() {
	return numerals;
}

void romanType::changeNumerals(char *entry) {
	entry = toCaps(entry);
	if (isValidNumeral(entry)) {
		numerals = entry;
	} else {
		cout << "\nInvalid numeral. Setting to default(V)";
		numerals = entry;
		*entry++ = 'V';
		*entry = '\0';
	}
	value = numeralToInt(numerals);
	//printf("\nin changeNumerals, value:%d, numerals:%s", value, numerals);
}
