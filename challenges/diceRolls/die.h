#include <iostream>
#include <stdlib.h>
#include <time.h>

using namespace std;

class die {
public:
    //roll() sets val to a random number and sets it
    int roll();
    //constructor
    die();
    static int totalDie;
private: 
    int val;
    int sides = 6;
};

int die::totalDie = 0;

int die::roll() {
    return val = (rand() % sides + 1);
}

die::die() {
    srand(time(NULL));
    roll();
    totalDie++;
}
