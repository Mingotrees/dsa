#include <stdio.h>
#include <stdbool.h>
#define MAX 8

typedef unsigned int SET;

void initialize(SET*);
void display(SET);
void insert(int a, SET* A);
void delete(SET* A, int x);
SET Union(SET A, SET B);
SET Intersection(SET A, SET B);
SET Difference(SET A, SET B);

int main(){
    SET a;
    SET b;
    initialize(&b);
    initialize(&a);
    // display(a);
    for(int ndx = 0; ndx <= 7; ndx++){
        insert(ndx, &a);
        insert(7+ndx, &b);
    }
    insert(31, &a);
    printf("SET A:\n");
    display(a);
    printf("SET B:\n");
    display(b);

    printf("Union:\n");
    SET c = Union(a, b);
    display(c);

    printf("Interesction:\n");
    c = Intersection(a, b);
    display(c);

    printf("Difference:\n");
    c = Difference(a, b);
    display(c);
    // delete(&a, 6);
    // delete(&a, 7);
}

void display(SET a)
{
    unsigned int x;
    for(x = 1 << (sizeof(int)* MAX - 1); x != 0; x >>= 1){
        printf("%d ", (x&a) == 0 ? 0 : 1);
        
    }

    printf("\nMEMBERS OF THE SET: { ");
    int count = 0;
    int len = sizeof(int)*MAX - 1;
    for(int ndx = 0; ndx < len; ndx++){
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
    if(a < sizeof(int)*MAX){
        *A |= (1 << a);
    }
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

SET Union(SET A, SET B){
    return A|B;
}

SET Intersection(SET A, SET B){
    return A&B;
}

SET Difference(SET A, SET B){
    return A&~B;
}
