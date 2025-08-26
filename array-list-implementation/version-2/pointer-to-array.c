/*
* This Program is made to simulate the version 2
* of ARRAY implementation where ListPtr is a ptr to
* a structure that contains an array and a variable count
*
* Programmer: Jhanell R. Mingo 
* Created: 08/26/2025
* Last Updated: 08/26/2025 @ 8:08PM
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
    studDetails elements[MAX];
    int count;
}LIST, *ListPtr;


//CRUD OPERATIONS
void insert(ListPtr arr, studDetails student, int pos);
void delete(ListPtr arr, int id);
void locate(LIST arr);
studDetails retrieve(LIST arr, int id);
void initList(ListPtr* arr);
ListPtr initList2();


//HELPER FUNCTIONS
void displayStuds(LIST arr);
void mallocFail(){
    printf("Malloc Failed\n");
}
void invalidPos(){
    printf("Invalid Position\n");
}


//MAIN DRIVER FUNCTION
int main(){
    /*
    * USE THESE TO POPULATE
    */
    studDetails students[] = {
    { {"Alice", "Santos", 'M'}, 1001, "BSCS", 1 },
    { {"Brian", "Cruz", 'D'}, 1002, "BSIT", 2 },
    { {"Carla", "Lopez", 'R'}, 1003, "BSEE", 3 },
    { {"David", "Reyes", 'J'}, 1004, "BSME", 4 },
    { {"Ella", "Garcia", 'L'}, 1005, "BSN", 1 }
    };
    int size = sizeof(students) / sizeof(students[0]);



    ListPtr a = initList2();
    initList(&a);
    insert(a, students[1], 0);
    printf("%d\n", a->count);
    insert(a, students[1], 1);
    printf("%d\n", a->count);
    displayStuds(*a);
    free(a);
}



ListPtr initList2(){
    ListPtr arr = (ListPtr)malloc(sizeof(LIST));
    if(arr == NULL){
        mallocFail();
    }else{
        arr->count = 0;
    }
    return arr;
}

void initList(ListPtr* arr){
    *arr = (ListPtr)malloc(sizeof(LIST));
    if(*arr == NULL){
        mallocFail();
    }else{
        (*arr)->count = 0;
    }
}

void displayStuds(LIST arr){
    for (int i = 0; i < arr.count; i++) {
        printf("ID: %d | Name: %s %c. %s | Course: %s | Year: %d\n",
            arr.elements[i].ID,
            arr.elements[i].name.FName,
            arr.elements[i].name.Mi,
            arr.elements[i].name.LName,
            arr.elements[i].course,
            arr.elements[i].Year
        );
    }
}

void insert(ListPtr arr, studDetails student, int pos){
    if(pos < 0 || pos > arr->count){
        invalidPos();
    }else{
        int ndx;
        for(ndx = arr->count; ndx > pos; ndx--){
            arr->elements[ndx] = arr->elements[ndx-1];
        }
        arr->elements[pos] = student;
        arr->count++;
    }
}

void delete(ListPtr arr, int id){
    
}


