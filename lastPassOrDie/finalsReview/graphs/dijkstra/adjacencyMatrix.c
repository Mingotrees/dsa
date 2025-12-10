#include <stdio.h>
#include <stdlib.h>
#define MAX 5
#define INF 999

typedef struct{
    int source;
    int destination;
    int cost;
}edge;

typedef int AdjacencyMatirx[MAX][MAX];

void insertAllEdge(AdjacencyMatirx a, edge list[], int count);
void init_matrix(AdjacencyMatirx a);
void display(AdjacencyMatirx a);
void displayDijkstra(int dist[]);
void dijkstra(AdjacencyMatirx a, int start, int dist[]);

int main(){
    edge list[] = {{0,1,10}, {0,3,30}, {0,4,100}, {1,2,50}, {2,1,20},
                    {2,4,10}, {3,2,20}, {3,4,60}};
    int count = sizeof(list)/sizeof(list[0]);
    AdjacencyMatirx b;
    init_matrix(b);
    insertAllEdge(b, list, count);
    // display(b);
    int dist[MAX] = {0};
    dijkstra(b, 0, dist);
    displayDijkstra(dist);
    
    return 0;
}

//directed
void insertAllEdge(AdjacencyMatirx a, edge list[], int count){
    for(int ndx = 0; ndx < count; ndx++){
        a[list[ndx].source][list[ndx].destination] = list[ndx].cost;
    }
}

void init_matrix(AdjacencyMatirx a){
    for(int ndx = 0; ndx < MAX; ndx++){
        for(int idx = 0; idx < MAX; idx++){
            a[ndx][idx] = INF;
        }
    }

    for(int ndx = 0; ndx < MAX; ndx++){
        a[ndx][ndx] = 0;
    }
}

void dijkstra(AdjacencyMatirx a, int start, int dist[]){
    int s[MAX] = {0}; //bit-vector
    for(int ndx = 0; ndx < 5; ndx++){
        dist[ndx] = a[start][ndx];
    }
    s[start] = 1;
    //mane i already set that start to 0 in my init
    for(int ndx = 1; ndx < MAX; ndx++){
        int idx;
        int min;
        int near = INF;
        for(idx = 0; idx < MAX; idx++){
            if(s[idx] != 1 && dist[idx] < near){
                near = dist[idx];
                min = idx;
            }
        }

        s[min] = 1;
        int jdx;
        for(jdx = 0; jdx < MAX; jdx++){
            if(s[jdx] != 1){
                if(dist[jdx] > (dist[min] + a[min][jdx])){
                    dist[jdx] = (dist[min] + a[min][jdx]);
                } 
            } 
        }
    }

}

void displayDijkstra(int dist[]){
    for(int ndx = 0; ndx < MAX;ndx++){
        if(dist[ndx] == INF){
            printf("%5s ", "INF");
        }else{
            printf("%5d ", dist[ndx]);
        }
    }
}

void display(AdjacencyMatirx a){
    for(int ndx = 0; ndx < MAX; ndx++){

        for(int idx = 0; idx < MAX; idx++){
            if(a[ndx][idx] == INF){
                printf("%5s ", "INF");
            }else{
                printf("%5d ", a[ndx][idx]);
            }
        }
        printf("\n");
    }
}