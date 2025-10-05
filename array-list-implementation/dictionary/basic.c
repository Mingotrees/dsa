/*
*  ORIGINAL CLOSED HASHING IMPLEMENTATION
*
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#define MAX 5

typedef int Dictionary[MAX];
typedef enum{EMPTY = -1, DELETED = -2, NON_EXISTENT = -10}FLAG;

int hash(int value);
void insert(Dictionary A, int x);
void delete(Dictionary A, int x);
void initDictionary(Dictionary A);
int isMember(Dictionary A, int x); //returns the position of the member
int getSearchLength(Dictionary A, int x, int index);
float calculateAvgSearchLen(Dictionary A);
void display(Dictionary A);


int main(){
    Dictionary B;
    initDictionary(B);
    display(B);
    insert(B, 61);
    display(B);
    insert(B, 71);
    insert(B, 81);
    insert(B, 101);
    display(B);
    insert(B, 31);
    display(B);
    display(B);
    int len = getSearchLength(B, 31, 0);
    float ave = calculateAvgSearchLen(B);
    printf("Average Search Length: %.2f", ave);
    
    
}

float calculateAvgSearchLen(Dictionary A){
    float sum = 0;
    for(int ndx = 0; ndx < MAX; ndx++){
        sum += getSearchLength(A, A[ndx], ndx);
    }

    return sum/MAX;
}

void display(Dictionary A){
    printf("\nELEMENTS OF THE DICTIONARY\n");
    for(int ndx = 0 ; ndx < MAX; ndx++){
        printf("[%d]: ", ndx);
        if(A[ndx] == DELETED){
            printf("DELETED\n");
        }else if(A[ndx] == EMPTY){
            printf("EMPTY\n");
        }else{
            printf("%d\n", A[ndx]);
        }
    }
}

//(Actual - Hash(x) + 1 + MAX) % MAX?
int getSearchLength(Dictionary A, int x, int index){
    int len = ((index - hash(x)) + 1 + MAX) % MAX;
    return  len == 0 ?  MAX : len;
}

void initDictionary(Dictionary A){
    for(int ndx = 0; ndx < MAX; ndx++){
        A[ndx] = EMPTY;
    }
}

int hash(int value){
    return abs(value % MAX);
}

void insert(Dictionary A, int x){
    /*  Steps to insert
        1. Find Hash Value
        2. Check if position of hash is already occupied
            if occupied - O(n);
                move to the nearest EMPTY slot
                if no empty slot 
                    move to the nearest DELETED slot
                else
                    dictionary is FULL
            else
                insert in the given hash position - O(1); 
    */
    int hashVal = hash(x), deletePos = -3; 
    // printf("%d", hashVal);
//    int stop = (hashVal - 1 + MAX) % MAX; //possible problem might be the last element of the array will not be checked if so
    int stop = 0; // instead of storing positions just based it on search length
    for(;stop != MAX && A[hashVal] != EMPTY; hashVal = (hashVal + 1) % MAX, ++stop){
        if(deletePos == -3 && A[hashVal] == DELETED){
            deletePos = hashVal;
        }
    }

    if(stop != MAX){
        A[hashVal] = x;
    }else if(deletePos != -3){
        A[deletePos] = x;
    }else{
        printf("List is Full\n");
    }
}



void delete(Dictionary A, int x){
    /*  Steps to delete
        1. Find Hash Value
        2. Check if Hash Position holds the passed value of x
            if not - O(n)
                check the position nearby hashValue if element exists
                    if you encounter an empty index while searching elem does not exist break immediately
                if it exists 
                    simply delete it
                if not 
                member does not exist
            else
                simply delete it - O(1)
    */
    printf("\nDELETING ELEMENT\n");
    int hashVal = isMember(A, x);
    if(hashVal != NON_EXISTENT){
        printf("Sucessfully Deleted\n");
        A[hashVal] = DELETED;
    }else{
        printf("it aint there\n");
    }
}



int isMember(Dictionary A, int x){
    int hashVal = hash(x);
    int start = hash(x);
    int sl = 1;
    //we could also search this way
    // by Zeus ElderField (🐐)
    bool isFull = false;
    //this how you manually get search length btw
    //which has a problem if element is not on the list it results to MAX + 1
    //which the else solves
    while(!isFull && A[hashVal] != x && A[hashVal] != EMPTY){
        hashVal = (hashVal + 1) % MAX;
        if(hashVal == start){
            isFull = true;
        }else{
            sl++;
        }
    }
    
    printf("Total Search Length: %d\n", sl);
    return A[hashVal] == x ? hashVal : NON_EXISTENT;
}
