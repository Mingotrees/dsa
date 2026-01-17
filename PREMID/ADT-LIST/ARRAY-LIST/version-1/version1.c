/*
* This Program is made to simulate the version 1
* where Array List is a struct with an array and
* a count
*
* Programmer: Jhanell R. Mingo 
* Created: 01/17/2026
* Last Updated: 01/17/2026 @ 5:58PM
*
*/
#include <stdio.h>
#include <stdlib.h>
#define MAX 10

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
    studDetails elem[MAX]; 
    int count;
}LIST, *ListPtr;

//CRUD OPERATIONS
void insert(ListPtr arr, studDetails student);
void delete(ListPtr arr, int id);
int locate(LIST arr, int id);
void populate(ListPtr arr);
void initList(ListPtr arr);
ListPtr initList2();
void insertionSort(ListPtr arr);


//HELPER FUNCTIONS
void displayStuds(LIST arr);
void displayStud(studDetails details);
void mallocFail(){
    printf("Malloc Failed\n");
}
void invalidPos(){
    printf("Invalid Position\n");
}
void listIsFull(){
    printf("List is Full\n");
}


int main(){
    LIST stephen;
    initList(&stephen);
    populate(&stephen);
    insertionSort(&stephen);
    displayStuds(stephen);
}

void insert(ListPtr arr, studDetails student){
    if(arr->count >= MAX){
        listIsFull();
        return;
    }

    arr->elem[arr->count++] = student;
}

void delete(ListPtr arr, int id){
    if(arr->count == 0){
        printf("List is Empty");
        return;
    }

    int ndx, k = 0;
    for(ndx = 0; ndx < arr->count;){
        if(arr->elem[ndx].ID != id){
            arr->elem[k++] = arr->elem[ndx];
        }
    }

    arr->count = k;
}

int locate(LIST arr, int id){
    int ndx;
    for(ndx = 0; ndx < arr.count && arr.elem[ndx].ID != id; ndx++){}
    return ndx < arr.count ? ndx : -1;
}

void populate(ListPtr arr){
        /*
    * USE THESE TO POPULATE
    */
    studDetails students[] = {
        { {"Ella", "Garcia", 'L'}, 1005, "BSN", 1 },
        { {"David", "Reyes", 'J'}, 1004, "BSME", 4 }
    };
    int len = sizeof(students)/sizeof(students[0]);
    for(int ndx = 0; ndx < len; ndx++){ insert(arr, students[ndx]);}
}

void initList(ListPtr arr){
    arr->count = 0;
}

ListPtr initList2(){
    ListPtr ptr = (ListPtr)malloc(sizeof(LIST));
    ptr->count = 0;
    return ptr;
}

void insertionSort(ListPtr arr){
    int ndx;
    //imma do a pigeon hole method where u insert when its in position to avoid swapping
    //just imagine ni check ko if more than 1 ang inside sa array kay kapoy hehe
    for(ndx = 1; ndx < arr->count; ndx++){
        studDetails temp = arr->elem[ndx];
        int idx;
        for(idx = ndx; idx > 0 && arr->elem[idx-1].ID > temp.ID; idx--){
            arr->elem[idx] = arr->elem[idx-1];
        }
        if(idx != ndx){
            arr->elem[idx] = temp;
        }
    }
}

void displayStuds(LIST arr){
    printf("===== STUDENTS REMAINING IN LIST: %d =====\n", arr.count);
    for (int i = 0; i < arr.count; i++) {
        printf("ID: %d | Name: %s %c. %s | Course: %s | Year: %d\n",
            arr.elem[i].ID,
            arr.elem[i].name.FName,
            arr.elem[i].name.Mi,
            arr.elem[i].name.LName,
            arr.elem[i].course,
            arr.elem[i].Year
        );
    }
}


