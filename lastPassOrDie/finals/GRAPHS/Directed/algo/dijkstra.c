#include <stdio.h>
#include <stdlib.h>
#define SIZE 5
#define NOPATH 999
#define VERTEX 0

typedef int Graph[SIZE][SIZE];
typedef int SET[SIZE];


//rubber duck
//steps to dijkstra
//(pre-requisite)0. Have a set that has all vertices we will call it V
//1. Decide what vertex u want to find the shortest path to all other vertex
//2. Declare and Fill set D with size n(number of vertices) with all of the chosen vertex's distance from the matrix adjacency matrix
//3. Declare a set S of size n and put chosen vertex inside it
//4. Choose D[i] which has minimum distance in V-S in the matrix
//5. Add i into set S
//6. For each vertex that is not in V calculate the minimum distance and assign it to the shortest Path table D[v] = min(D[v], C[w][v])
void dijkstra(Graph G, SET V, SET S, SET D);
void build(Graph m);
int findMin(SET D, SET S, SET V);
int min(int x, int y);

int main(){
    Graph G = {0};
    build(G);
    //all vertices
    SET V = {1, 1, 1, 1, 1};
    //traversed set tracker
    //I choose to find the shortest path from vertex 2 to anywhere ong
    SET S = {1,0,0,0,0};

    //shortest paths
    SET D = {0};
    dijkstra(G, V, S, D);
    for(int ndx = 0; ndx < SIZE; ndx++){
        printf("%d ", D[ndx]);
    }
}

void build(Graph m){
    Graph a = {{0, 10, NOPATH, 30, 100},{NOPATH, 0, 50, NOPATH, NOPATH},{20, NOPATH, 0, NOPATH, 10},{NOPATH, NOPATH, 20, 0, 60},{NOPATH, NOPATH, NOPATH, NOPATH,0}};
    for(int ndx = 0; ndx < SIZE; ndx++){
        for(int idx = 0; idx < SIZE; idx++){
            m[ndx][idx] = a[ndx][idx];
        }
    }
}

void dijkstra(Graph G, SET V, SET S, SET D){
    //distances
    for(int ndx = 0; ndx < SIZE; ndx++){
        D[ndx] = G[VERTEX][ndx];
    }

    for(int ndx = 1; ndx < SIZE; ndx++){
        int w = findMin(D, S, V);
        S[w] = 1;
        for(int idx = 0; idx < SIZE; idx++){
            if((V[idx] & S[idx]) != 1){
                D[idx] = min(D[idx], D[w] + G[w][idx]);
            }
        }
    }
}

int findMin(SET D, SET S, SET V){
    int ndx, distance = NOPATH, retVal = -1;
    for(ndx = 0; ndx < SIZE; ndx++){
        if((V[ndx] & S[ndx]) != 1 && D[ndx] < distance){
            distance = D[ndx];
            retVal = ndx;
        }
    }
    
    return retVal;
}

int min(int x, int y){
    return x < y ? x : y;
}
