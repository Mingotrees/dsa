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
int locate(LIST arr, int id);
void populate(ListPtr arr);
studDetails retrieve(LIST arr, int id);
void initList(ListPtr* arr);
ListPtr initList2();


//HELPER FUNCTIONS
void displayStuds(LIST arr);
void displayStud(studDetails details);
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
    { {"David", "Reyes", 'J'}, 1004, "BSME", 4 },
    { {"Ella", "Garcia", 'L'}, 1005, "BSN", 1 }
    };

    ListPtr a = initList2();
    // initList(&a);
    populate(a);
    // insert(a, students[0], 0);
    // insert(a, students[1], 1);
    displayStuds(*a);
    int location = locate(*a, 1001);
    printf("%d\n", location + 1);
    studDetails details = retrieve(*a, 1001);
    displayStud(details);
    // delete(a, 1003);
    // displayStuds(*a);
    // delete(a, 1002);
    // displayStuds(*a);
    free(a);
}

void populate(ListPtr arr){
    studDetails students[] = {
        { {"Alice", "Santos", 'M'}, 1001, "BSCS", 1 },
        { {"Brian", "Cruz", 'D'}, 1002, "BSIT", 2 },    
        { {"Carla", "Lopez", 'R'}, 1003, "BSEE", 3 },
    };
    int size = sizeof(students) / sizeof(students[0]);

    for(int ndx = 0; ndx < size; ndx++){
        insert(arr, students[ndx], ndx);
    }
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

void displayStud(studDetails details){
    printf("===== STUDENT %d=====\n", details.ID);
    printf("Name: %s %c. %s | Course: %s | Year: %d\n" ,
        details.name.FName,
        details.name.Mi,
        details.name.LName,
        details.course,
        details.Year
    );
}


void displayStuds(LIST arr){
    printf("===== STUDENTS REMAINING IN LIST: %d\n", arr.count);
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
    int ndx;
    for(ndx = 0; ndx < arr->count && arr->elements[ndx].ID != id; ndx++){}
    if(ndx < arr->count){
        arr->count--;
        for(;ndx < arr->count; ndx++){
            arr->elements[ndx] = arr->elements[ndx+1]; 
        } 
    }else{
        printf("Elem not Found");
    }
}

int locate(LIST arr, int id){
    int ndx;
    for(ndx = 0; ndx < arr.count && arr.elements[ndx].ID != id; ndx++){}
    return ndx < arr.count ? ndx : -1;
}

studDetails retrieve(LIST arr, int ID){
    int ndx;
    studDetails dummy = {.ID = -1};
    for(ndx = 0; ndx < arr.count && arr.elements[ndx].ID != ID; ndx++){}
    return ndx < arr.count ? arr.elements[ndx] : dummy;
}


