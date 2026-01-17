#include <stdio.h>
#define MAX 0x14
#define MAXPRIME 0xA
#include <stdlib.h>

/*
*   CLOSED HASHING VARIATION BY MS. PENA
*
*/

typedef enum{EMPTY = -10, DELETED = -20, FULL = -30} DictStatus;

typedef struct{
    int data;
    int link;
}nodetype;

typedef struct{
    nodetype arr[MAX];
    int avail;
}Dictionary;

int hash(int value);
void insert(Dictionary* A, int value);
void delete(Dictionary* A, int value);
void initDictionary(Dictionary A);
int isMember(Dictionary A, int x);
int getSearchLength(Dictionary A, int x, int index);
float calculateAvgSearchLen(Dictionary A);
void display(Dictionary A);
void init(Dictionary *A);

int main(){
    system("cls");
    Dictionary A;
    init(&A);
    insert(&A, 12);
    insert(&A, 11);
    insert(&A, 10);
    insert(&A, 13);
    insert(&A, 14);
    insert(&A, 15);
    insert(&A, 16);
    insert(&A, 17);
    insert(&A, 18);
    insert(&A, 19);
    insert(&A, 20);
    delete(&A, 10);
    delete(&A, 30);
    

    display(A);
    // for(int ndx = 0; ndx < MAX; ndx++){
    //     printf("ndx: %d (%d | %d)\n", ndx, A.arr[ndx].data, A.arr[ndx].link);
    // }
    // printf("AVAIL VALUE: %d", A.avail);
}
void init(Dictionary* A){
    int ndx; 
    for(ndx = 0; ndx < MAXPRIME; ndx++){
        A->arr[ndx].data = EMPTY;
        A->arr[ndx].link = -1;
    }
    for(ndx = MAXPRIME; ndx < MAX; ndx++){
        A->arr[ndx].data = EMPTY;
        A->arr[ndx].link = ndx + 1;
    }
    A->arr[ndx-1].link = -1;
    A->avail = MAXPRIME;
}

void display(Dictionary A){
    printf("==============PRESENTING THE MADAFAKEN DICKTIONARY================\n");
    for(int ndx = 0; ndx < MAXPRIME; ndx++){
        int idx;
        printf("[%d]: %d -> ", ndx, A.arr[ndx].data);
        for(idx = A.arr[ndx].link; idx != -1; idx = A.arr[idx].link){
            printf("[%d] ", A.arr[idx].data);
        }
        printf("\n");
    }
}

int hash(int value){
    return abs(value) % MAXPRIME;
}

void insert(Dictionary* A, int value){
    /*
    *   ASSUMING NGA THE WAY SA SYNONYM MO BEHAVE KAY IGO RA I ULI SA AVAIL ANG SYNONYM DELE SIYA I "DELETED"
    *   STEPS TO INSERT
    *   1. Check if the position given by the hash value is empty
    *      1.1 If Empty Insert Directly
    *      1.2 If position is already occupied OR deleted, call the kind of VHEAP to alloc space for the synonym
    *         1.2.1 save the link of the one occupying the actual hash position
    *         1.2.2 insert the data to the new allocated space, as well as the link that we saved from the original placement
    *         1.2.3 update the link of the original placement to the index given by the alloc
    *       FUCKKK WA NAKO NA HANDLE KUNG PUNO NA ANG SYNOYNM NIYA NAA PAY DELETED SA PRIME AREA
    * */
    printf("Inserting element %d....\n", value);
    int hashVal = hash(value), space = -9999;
    if(A->arr[hashVal].data == EMPTY){
        A->arr[hashVal].data = value;
        printf("Insert value %d was inserted at index %d successfully\n", value, hashVal);
    }else{
        //alloc space code can be modularize 
        space = A->avail;
        if(space != -1){
            A->avail = A->arr[space].link;
            A->arr[space].data = value;
            A->arr[space].link = A->arr[hashVal].link;
            A->arr[hashVal].link = space;
            printf("Insert value %d was inserted at index %d successfully\n", value, space);
        }else if(A->arr[hashVal].data == DELETED){
            A->arr[hashVal].data = value;
            printf("Insert value %d was inserted at index %d successfully\n", value, hashVal);
        }else{
            printf("Insert failed dictionary is full\n");
        }
    }
}

void delete(Dictionary* A, int value){
    printf("Deleting %d.....\n", value);
    int hashVal = hash(value);
    int *ndx;
    for(ndx = &hashVal; *ndx != -1 && A->arr[*ndx].data != value; ndx = &A->arr[*ndx].link){}
    if(*ndx != -1){
        if(*ndx == hashVal){
            A->arr[*ndx].data = DELETED;
        }else{
            int temp = *ndx;
            *ndx = A->arr[temp].link;
            A->arr[temp].link = A->avail;
            A->avail = temp;
        }   
        printf("Element %d Found at index %d and was deleted successfully\n", value, *ndx);
    }else{
        printf("Delete failed, the element does not exist\n");
    }
}