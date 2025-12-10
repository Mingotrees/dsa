#include <stdio.h>
#include <stdlib.h>
#define MAX 5
#define INF 999

typedef struct{
    int source;
    int destination;
    int cost;
}edge;

typedef struct edge{
    int destination;
    int cost;
    struct edge* next;
}node;

typedef node* AdjacencyList[MAX];

void insertAllEdge(AdjacencyList a, edge list[], int count);
node* createEdge(edge);
void init_matrix(AdjacencyList a);
void display(AdjacencyList a);
void displayDijkstra(int dist[]);
void dijkstra(AdjacencyList a, int start, int dist[]);

int main(){
    edge list[] = {{0,1,10}, {0,3,30}, {0,4,100}, {1,2,50}, {2,1,20},
                    {2,4,10}, {3,2,20}, {3,4,60}};
    int count = sizeof(list)/sizeof(list[0]);
    AdjacencyList b;
    init_matrix(b);
    insertAllEdge(b, list, count);
    display(b);
    int dist[MAX] = {0};
    dijkstra(b, 0, dist);
    displayDijkstra(dist);
    
    return 0;
}

//directed
void insertAllEdge(AdjacencyList a, edge list[], int count){
    node* newEdge = NULL;
    node* temp = NULL;
    for(int ndx = 0; ndx < count; ndx++){
        temp = a[list[ndx].source];
        a[list[ndx].source] = createEdge(list[ndx]);   
        a[list[ndx].source]->next = temp;              
    }
}

node* createEdge(edge a){
    node* newEdge = NULL;
    newEdge = (node*)malloc(sizeof(node));
    if(newEdge != NULL){
        newEdge->destination = a.destination;
        newEdge->cost = a.cost;
        newEdge->next = NULL;
    }

    return newEdge;
}

void init_matrix(AdjacencyList a){
    for(int ndx = 0; ndx < MAX; ndx++){
        a[ndx] = NULL;
    }
}
void display(AdjacencyList a){
    for(int ndx = 0; ndx < MAX; ndx++){
        node* trav = a[ndx];
        printf("%d: ", ndx);
        while(trav != NULL){
            printf("(%d, %d) ", trav->destination, trav->cost);
            trav = trav->next;
        }
        printf("\n");;
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

void dijkstra(AdjacencyList a, int start, int dist[]){
    int visited[MAX] = {0};
    node* trav;

    for(int ndx = 0; ndx < MAX; ndx++){
        dist[ndx] = INF;
    }
    dist[start] = 0;
    visited[start] = 1;

    for(trav = a[start]; trav != NULL; trav = trav->next){
        dist[trav->destination] = trav->cost; 
    }

    int n;
    for(n = 1; n < MAX; n++){
        int min = INF;
        int minNdx = -1;
        for(int jdx = 0; jdx < MAX; jdx++){
            if(visited[jdx] == 0 && dist[jdx] < min){
                min = dist[jdx];
                minNdx = jdx;
            }
        }
        if(min != INF){
            visited[minNdx] = 1;
            for(int idx = 0; idx < MAX; idx++){
                if(visited[idx] == 0){
                    for(trav = a[minNdx]; trav!= NULL && trav->destination != idx; trav = trav->next){}
                    if(trav != NULL){
                        if(trav->cost + min < dist[idx]){
                            dist[idx] = trav->cost + min;
                        }
                    }
                }
            }
        }else{
            printf("graph is disconnected\n");
        }
    }
}