#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 10

typedef struct node{
    int data;
    char* key;
    struct node* next;   
}*List;

typedef List Set[10];

int hash(char*);
void insertUnique(int , char*, Set);
void delete(char*, Set);
void display(Set);

int main(){
    Set table = {NULL};   // initialize all buckets to NULL

    printf("=== Insertion Tests ===\n");
    insertUnique(10, "a", table);     // hash = 1
    insertUnique(20, "bb", table);    // hash = 2
    insertUnique(30, "ccc", table);   // hash = 3
    insertUnique(40, "dddd", table);  // hash = 4

    printf("\n=== Duplicate Insert Tests ===\n");
    insertUnique(10, "a", table);     // duplicate key/data
    insertUnique(99, "a", table);     // duplicate key only
    insertUnique(10, "hello", table); // duplicate data only (your check treats it as duplicate)

    printf("\n=== Collision Tests ===\n");
    insertUnique(50, "kkkkkkkkkk", table);  // len=10 → hash=0
    insertUnique(60, "xyzxyzxyzx", table);  // len=10 → hash=0 (collision)
    insertUnique(70, "tenchars!!", table);  // len=10 → hash=0 (collision)

    printf("\n=== Display After Inserts ===\n");
    display(table);

    printf("\n=== Delete Tests ===\n");
    delete("a", table);          // delete existing
    delete("xyzxyzxyzx", table); // delete in collision chain
    delete("unknown", table);    // delete non-existent

    printf("\n=== Display After Deletes ===\n");
    display(table);
}

int hash(char* key){
    return strlen(key)%10;
}

void insertUnique(int x, char* key, Set a){
    int hashVal = hash(key);
    List* ptr;
    for(ptr = &a[hashVal]; *ptr != NULL && strcmp((*ptr)->key, key) != 0; ptr = &(*ptr)->next){}
    if(*ptr == NULL){
        *ptr = (List)malloc(sizeof(struct node));
        (*ptr)->key = (char*)malloc(sizeof(char)*strlen(key)+1);
        strcpy((*ptr)->key, key);
        (*ptr)->data = x;
        (*ptr)->next = NULL;
    }else{
        printf("key or data already exist");
    }
}

void delete(char* key, Set a){
    int hashVal = hash(key);
    List* ptr;
    for(ptr = &a[hashVal]; *ptr != NULL && strcmp((*ptr)->key, key) != 0; ptr = &(*ptr)->next){}
    if(*ptr != NULL){
        List temp = *ptr;
        *ptr = temp->next;
        free(temp->key);
        free(temp);
    }else{
        printf("elem not found");
    }
}

void display(Set a){
    int ndx;
    for(ndx = 0; ndx < MAX; ndx++){
        printf("Bucket %d: ", ndx);
        List b = a[ndx];
        while(b != NULL){
            printf("(%d, %s) ", b->data, b->key);
            b = b->next;
        }
        printf("\n");
    }
}




