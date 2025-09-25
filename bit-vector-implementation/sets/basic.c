#include <stdio.h>
#include <stdlib.h>
#define MAX 10

typedef int SET[MAX];

void insert(SET A, int x);
void delete(SET A, int x);
SET* Union(SET A, SET B);
SET* Intersection(SET A, SET B);
SET* Difference(SET A, SET B);
void initialize(SET A);

int main(){

}

void initialize(SET A){
    for(int ndx = 0; ndx < MAX; ndx++){
        A[ndx] = 0;
    }
}

void insert(SET A, int x){

}

void delete(SET A, int x){

}

SET* Union(SET A, SET B){

}

SET* Intersection(SET A, SET B){

}

SET* Difference(SET A, SET B){

}
