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
#define MAX 1

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
}LIST, *ListPtr;



//MAIN FUNCTIONS
LIST initList();
void insert(ListPtr, studDetails, int);
void expandArr(ListPtr);
void delete(ListPtr, int ID);


void displayStuds(LIST arr);
void mallocFail(){
    printf("Malloc Failed\n");
}
void invalidPos(){
    printf("Invalid Position\n");
}
void listIsFull(){
    printf("List is Full\n");
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
    insert(&L, students[0], 0);
    insert(&L, students[1], 1);
    insert(&L, students[0], 1);
    displayStuds(L);
    delete(&L, 1004);
    displayStuds(L);
    free(L.elemptr);
}

void displayStuds(LIST arr){
    printf("===== STUDENTS REMAINING IN LIST: %d ========\n", arr.count);
    for (int i = 0; i < arr.count; i++) {
        printf("ID: %d | Name: %s %c. %s | Course: %s | Year: %d\n",
            arr.elemptr[i].ID,
            arr.elemptr[i].name.FName,
            arr.elemptr[i].name.Mi,
            arr.elemptr[i].name.LName,
            arr.elemptr[i].course,
            arr.elemptr[i].Year
        );
    }
}


LIST initList(){
    LIST L = {.count = 0, .arrSize = MAX};
    L.elemptr = (studDetails*)malloc(sizeof(studDetails)* MAX);
    if(L.elemptr == NULL){
        mallocFail();
    }
    return L;
}

void expandArr(ListPtr A){
    studDetails* newPtr = realloc(A->elemptr, sizeof(studDetails) * (A->arrSize*2));
    if(newPtr == NULL){
        mallocFail();
    }else{
        A->elemptr = newPtr;
        A->arrSize *= 2;
    }
}

void insert(ListPtr A, studDetails B, int pos){
    if(pos < 0 || pos > A->count){
        invalidPos();
    }else{
        if(A->count >= A->arrSize){
            listIsFull();
            printf("Increasing Size....\n");
            expandArr(A);
        }
        int ndx;
        for(ndx = A->count; ndx > pos; ndx--){
            A->elemptr[ndx] = A->elemptr[ndx-1];
        }
        A->elemptr[pos] = B;
        A->count++;
    }
}

void delete(ListPtr arr, int id){
    int ndx;
    for(ndx = 0; ndx < arr->count && arr->elemptr[ndx].ID != id; ndx++){}
    if(ndx < arr->count){
        arr->count--;
        for(;ndx < arr->count; ndx++){
            arr->elemptr[ndx] = arr->elemptr[ndx+1]; 
        }
    }else{
        printf("Elem not Found");
    }
}
