#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

//max 31 bits SET
typedef unsigned int SET;

void display(SET A, char* str);
void insert(SET* A, int x);
void initialize(SET* A);
void delete(SET* A, int x);
bool isSubset(SET A, SET B);
SET init2();
SET UNION(SET A, SET B);
SET INTERSECTION(SET A, SET B);
SET DIFFERENCE(SET A, SET B);
bool isMember(SET A, int x);

int main(){
    SET A = init2(), B = init2();
    insert(&A, 5);
    insert(&A, 3);
    insert(&A, 9);
    insert(&A, 1);
    insert(&A, 7);

    insert(&B, 2);
    insert(&B, 3);
    insert(&B, 6);
    insert(&B, 9);
    insert(&B, 10);

    display(A, "SET A");
    display(B, "SET B");
    SET C = UNION(A, B);
    display(C, "UNION OF SET A & B");
    C = INTERSECTION(A, B);
    display(C, "INTERSECTION OF SET A & B");
    C = DIFFERENCE(A, B);
    display(C, "DIFFERENCE OF SET A & B");

    printf("B is %s", isSubset(A, B) ? "a subset of A" : "is not a subset of A");
}

void display(SET A, char *str){
    printf("%s:{", str);
    int len = sizeof(A)*8 - 1;
    for(int i = 0; A != 0; i++){
        if((1 << i & A) > 0){
            printf("%d", i);
            A &= ~(1<<i);
            if(A != 0){
                printf(", ");
            }
        }
    }
    printf("}\n");
}

void insert(SET *A, int x){
    if(x < sizeof(SET)*8-1){
        *A |= (1 << x);
    }
}

void delete(SET *A, int x){
    if(x < sizeof(SET)*8-1){
        *A &= ~(1 << x);
    }
}

void initialize(SET* A){
    *A = 0;
}

bool isSubset(SET A, SET B){
    bool flag = true;
    int len = sizeof(A)*8 - 1;
    for(int ndx = 0; ndx < len && flag != false; ndx++){
        int mask = 1 << ndx;
        if((mask & B) > 0 && (mask & A) == 0){
            flag = false;
        }
    }

    return flag;
}

SET init2(){
    return 0;
}

SET UNION(SET A, SET B){
    return A|B;
}

SET INTERSECTION(SET A, SET B){
    return A&B;
}

SET DIFFERENCE(SET A, SET B){
    return A&~B;
}

bool isMember(SET A, int x);


