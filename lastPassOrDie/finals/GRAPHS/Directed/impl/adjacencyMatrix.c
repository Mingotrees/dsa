#include <stdio.h>
#include <stdlib.h>
#define NOPATH 999 //this could also mean its a path to itself or it has no adjacent nodes
#define SIZE 5
//this is an boolean adjacency matrix btw
//id suggest u draw the table and then make the graph ong
typedef int matrix[SIZE][SIZE];


matrix* build();

/*
1. FIRST(v) returns the index for the first vertex adjacent to v. The index for the
null vertex Λ is returned if there is no vertex adjacent to v.
2. NEXT(v, i) returns the index after index i for the vertices adjacent to v. Λ is
returned if i is the last index for vertices adjacent to v.
3. VERTEX(v, i) returns the vertex with index i among the vertices adjacent to v.
*/

int first(matrix m, int v);
int next(matrix m, int v, int i);
int vertex(matrix m, int v, int i);
void display(matrix m);

int main(){
    matrix* m = build();
    display(*m);
    free(m);
}

matrix* build(){
    matrix a = {{0,1,0,1,1},{0,0,1,0,0},{1,0,0,0,1},{0,0,1,0,1},{0,1,0,0,0}};
    matrix* ret = (matrix*)malloc(sizeof(matrix));
    for(int ndx = 0; ndx < SIZE; ndx++){
        for(int idx = 0; idx < SIZE; idx++){
            (*ret)[ndx][idx] = a[ndx][idx];
        }
    }
    return ret;
}

int first(matrix m, int v){
    int ndx;
    for(ndx = 0; ndx < SIZE && m[v][ndx] != 1; ndx++){ }
    return ndx < SIZE ? ndx : NOPATH;
}

int next(matrix m, int v, int i){
    i = i+1;
    for(; i < SIZE && m[v][i] != 1; i++){}
    return (i < SIZE) ? i : NOPATH;
}

int vertex(matrix m, int v, int i){
    return i;
}

void display(matrix m){
    for(int ndx = 0; ndx < SIZE; ndx++){
        printf("Nodes adjacent to %d: ", ndx);
        int i = first(m, ndx);
        while (i != NOPATH) {
            int w = vertex(m, ndx, i);
            printf("%d ", w);
            i = next(m, ndx, i);
        }
        printf("\n");
    }
}



