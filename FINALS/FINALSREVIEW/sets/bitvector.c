#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define MAX 10

typedef int Set[MAX];

void insert(Set, int);
void delete(Set, int);
bool is_member(Set, int);
Set* Union(Set, Set);
Set* Intersection(Set, Set);
Set* Difference(Set, Set);
void init_set(Set); //or can just use calloc honestly
void display(Set, char[]);

int main(){
    Set A, B; init_set(A), init_set(B);
    for(int ndx = 0; ndx < 4; ndx++){
        insert(A, ndx);
        insert(B, ndx+2);
    }
    insert(A, 7);
    display(A, "SET A");
    display(B, "SET B");
    Set* C = Union(A, B);
    display(*C, "UNION OF A & B");
    free(C);
    C = Intersection(A, B);
    display(*C, "INTERSECTION OF A & B");
    
    free(C);
    C = Difference(A, B);
    display(*C, "DIFFERENCE OF A & B");
    free(C);
}

void insert(Set A, int x){
    if(x < MAX){
        A[x] = 1;
    }
}
void delete(Set A, int x){
    A[x] &= ~(A[x]);
}

bool is_member(Set A, int x){
    return (A[x] & 1) == 1 ? true : false;
}

Set* Union(Set A, Set B){
    Set* C = (Set*)malloc(sizeof(int)*MAX);   
    for(int ndx = 0; ndx < MAX; ndx++){
        (*C)[ndx] = A[ndx] | B[ndx];
    } 
    return C;
}
Set* Intersection(Set A,  Set B){
    Set* C = (Set*)malloc(sizeof(int)*MAX);   
    for(int ndx = 0; ndx < MAX; ndx++){
        (*C)[ndx] = A[ndx] & B[ndx];
    } 
    return C;
}
Set* Difference(Set A, Set B){
    Set* C = (Set*)malloc(sizeof(int)*MAX);   
    for(int ndx = 0; ndx < MAX; ndx++){
        (*C)[ndx] = A[ndx] & ~B[ndx];
    } 
    return C;
}
void init_set(Set A){
    memset(A,0,sizeof(int)*MAX);
}

void display(Set A, char message[]){
    printf("%s: ", message);
    for(int ndx = 0; ndx < MAX; ndx++){
        if(A[ndx] == 1){
            printf("%d ", ndx);
        }
    }
    printf("\n");
}