/*
* This Program is made to simulate the version 4
* of ARRAY implementation where a struct List has variable elemptr which is a ptr to
* an dynamically allocated array. The structure includes a count and an arrSize
*
* Programmer: Jhanell R. Mingo 
* Created: 08/27/2025
* Last Updated: 08/27/2025 @ 5:58PM
*
*/

#include <stdio.h>
#include <stdlib.h>
#define MAX 5

typedef struct{
    char FName[24];
    char LName[16];
    char Mi;
}nametype;

typedef struct{
    nametype name;
    int ID;
    char course[8];
    int Year;
}studDetails;

typedef struct{
    studDetails* elemptr; 
    int count;
    int arrSize;
}LIST;


LIST initList();
void insert(LIST, studDetails, int);
void mallocFail(){
    printf("Malloc Failed\n");
}
void invalidPos(){
    printf("Invalid Position\n");
}

// CRUD OPERATIONS

//MAIN DRIVER FUNCTION
int main(){

    //INSERT WITH THESE
    studDetails students[] = {
        { {"David", "Reyes", 'J'}, 1004, "BSME", 4 },
        { {"Ella", "Garcia", 'L'}, 1005, "BSN", 1 }
    };


    LIST L = initList();
    // printf("%d %d %p", L.count, L.arrSize, L.elemptr);
    insert(L, students[0], 0);
}


LIST initList(){
    LIST L = {.count = 0, .arrSize = MAX};
    L.elemptr = (studDetails*)malloc(sizeof(studDetails)* MAX);
    if(L.elemptr == NULL){
        mallocFail();
    }
    return L;
}

void insert(LIST A, studDetails B, int pos){
    if(pos < 0 || pos > A.count){
        invalidPos();
    }else{
        int ndx;
        for(ndx = A.count; ndx > pos; ndx--){}
        A.elemptr[pos] = B;
        A.count++;
    }
}
