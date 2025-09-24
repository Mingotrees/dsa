#include <stdio.h>
#include <stdbool.h>
#define MAX 8


typedef unsigned int SET;

void initialize(SET*);
void display(int);
void insert(int a, SET* A);
void delete(SET* A, int x);

int main(){
    SET a;
    initialize(&a);
    // display(a);
    for(int ndx = 0; ndx <= 7; ndx++){
        insert(ndx, &a);
    }
    display(a);
    // delete(&a, 6);
    // delete(&a, 7);
    display(a);
}

void display(int a)
{
    unsigned int x;
    for(x = 1 << sizeof(int)* MAX -1; x!=0; x >>= 1){
        printf("%d ", (x&a) == 0 ? 0 : 1);
        
    }

    printf("\nMEMBERS OF THE SET: { ");
    int count = 0;
    for(int ndx = 0; ndx < MAX; ndx++){
        if((a >> ndx) & 1 == 1){
            printf("%d ", ndx);
        }
    }
    printf("}\n");

}

void initialize(SET* a){
    *a = 0;
}

void insert(int a, SET* A){
    unsigned int mask = 1 << a;
    *A  = *A | mask;
}

void delete(SET* A, int x){
    //version 1
    // if((*A & x) != 0){
    //     *A = *A ^ x;
    // }else{
    //     printf("Element is not in the set");
    // }

    if(x < MAX){ //check if bit position is valid;
        if((*A & 1 << x) != 0){
            *A ^= 1 << x;
            printf("Bit %d deleted sucessfully\n", x);
        }else{
            printf("Bit %d Doesn't Exist in the Set\n", x);
        }
        // *A &= ~(1 << x); //UNIVERSAL FORMULA
    }else{
        printf("Bit position out of bounds");
    }
}
