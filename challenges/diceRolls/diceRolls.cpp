#include <iostream>
#include <math.h>
#include "die.h"

using namespace std;

const int numberOfDice = 6;
struct pNode {
    //value is set through the previous node
    //the first node's value is zero
    int value;
    //sum is determined by the path taken on the tree
    int sum;
    //level starts at 0, ends at 6
    int level;
    //pointers to the 6 possible dice rolls
    pNode *s[6];
};

//creates a probability tree of every possible sum 
//choose an arbitrary value, however RAM is an issue.
//Usage, create a root node, assign with the function
pNode *populate(pNode *curNode,int curLev=0,int curVal=0, int prevSum=0) {
    //no more branches after 10 levels
    if (curLev > numberOfDice)
        return NULL;
    curNode = new pNode;
    int l = curNode->level = curLev;
    int v = curNode->value = curVal;
    int s = curNode->sum = prevSum + curVal;
    l++;

    for (int i = 0; i < 6; i++) {
        pNode *temp = curNode->s[i];
        curNode->s[i] = populate(temp, l, (i+1), s);
    }

    return curNode;
}

void troubleshooting(pNode *curNode) {
    printf("\nNode stats:");
    printf(" value = %d, sum = %d, level = %d\n", curNode->value,curNode->sum,curNode->level);
    for (int i = 0; i < 6; i++) {
        pNode *temp = curNode->s[i];
        if (temp == NULL)
            printf("%d is NULL", i+1);
        else {
            printf("\nNode stats:");
            printf(" value = %d, sum = %d, level = %d\n", temp->value,temp->sum,temp->level);
        }
        for (int j = 0; j < 6; j++) {
            pNode *temp2 = temp->s[j];
            if (temp2 == NULL)
                printf("%d is NULL", j+1);
            else {
                printf("\nNode stats:");
                printf(" value = %d, sum = %d, level = %d\n", temp2->value,temp2->sum,temp2->level);
             }
        }
    }
}

//This will traverse the tree and count the number of times a certain 
//sum was encountered
//If a sum is encountered, every node past it will have a higher sum
//Same logic applies if a node is encountered that already has a higher sum
int findSums(int search, pNode *curNode, int count = 0) {
   //Only the sums at the last level matter. 
   if (curNode->level == numberOfDice)
       if (curNode->sum == search)
           return ++count;
        else return 0;

   //sum can still be found. keep searching
   int rCount = count;
   for (int i = 0; i < 6; i++) {
       pNode *temp = curNode->s[i];
       rCount += findSums(search, temp, count);
   }
   //printf("\nreturning count of %d", count);
   return rCount;
}

int main() {
    pNode *temp;
    pNode *root;
    root = populate(temp);
    /*
    troubleshooting(root);
    int occurrences = findSums(6, root);
    printf("6 occurs %d times in the tree.", occurrences);
    occurrences = findSums(25, root);
    printf("\n25 occurs %d times in the tree.\n", occurrences);
    printf("36 occurs %d times in the tree.\n", findSums(36, root));
````*/
    die myDice[numberOfDice];
    int numOfRolls;
    int sum;
    int targetSum;
    int count;
    double probability;
    cout << "How many times would you like to roll the dice?: ";
    cin >> numOfRolls;
    printf("%d <= Possible Sum <= %d\n", numberOfDice, 6*numberOfDice); 
    cout << "What sum are you aiming for?: ";
    cin >> targetSum;
    probability = findSums(targetSum, root)/pow(6,numberOfDice) * 100;
    printf("There is a %f%c chance per roll that %d will be the sum.", probability, '%', targetSum);
    printf("\nThere is a %f%c chance that %d will be rolled at least once.", probability*numOfRolls, '%', targetSum);
    printf("\nRolling...");
    
    count = 0;
    for (int i = 0; i < numOfRolls; i++) {
        sum = 0;
        for (int j = 0; j < numberOfDice; j++)
            sum += myDice[j].roll();

        if (sum == targetSum)
            count++;
    }
    printf("\nThe sum %d was rolled %d times.", targetSum, count);
    printf("\n");
    return 0;
}

