/*
*  ORIGINAL CLOSED HASHING IMPLEMENTATION
*
*/

#include <stdio.h>
#include <math.h>
#define MAX 10

typedef int Dictionary[MAX];
typedef enum{EMPTY = -1, DELETED = -2}FLAG;

int hash(int value);
void insert(Dictionary A, int x);
void delete(Dictionary A, int x);
void initDictionary(Dictionary A);

int main(){
    
}

int hash(int value){
    return value < 0 ? abs(value % MAX) : -9999999999; //means invalid since im using the -1 values for the FLAGS
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
   int stop = (hashVal - 1 + MAX) % MAX; //possible problem might be the last element of the array will not be checked if so
   for(;hashVal != stop && A[hashVal] != EMPTY; hashVal = hashVal + 1 % MAX){
        if(deletePos == -3 && A[hashVal] == DELETED){
            deletePos = hashVal;
        }
   }

   if(hashVal != stop){
        A[hashVal] = x;
   }else if(deletePos != -3){
        A[deletePos] = x;
   }else{
        printf("List is Full");
   }
}

void delete(Dictionary A, int x){
    /*  Steps to delete
        1. Find Hash Value
        2. Check if Hash Position holds the passed value of x
            if not - O(n)
                check the position nearby hashValue if element exists
                if it exists 
                    simply delete it
                if not 
                member does not exist
            else
                simply delete it - O(1)
    */
   int 


}

void initDictionary(Dictionary A){

}