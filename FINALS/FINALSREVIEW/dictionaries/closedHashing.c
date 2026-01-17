#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 10
#define EMPTY -1
#define DELETED -2

typedef struct{
    int data;
    char* key;
}item;

typedef item Set[MAX];

int hash(char*);
void insertUnique(item, Set);
void delete(char*, Set);
void init(Set);
void display(Set);

int main(){
    Set table;
    init(table);

    item t;

    printf("=== Insertion Tests ===\n");
    t = (item){10, "a"};      insertUnique(t, table);  // hash 1
    t = (item){20, "bb"};     insertUnique(t, table);  // hash 2
    t = (item){30, "ccc"};    insertUnique(t, table);  // hash 3
    t = (item){40, "dddd"};   insertUnique(t, table);  // hash 4

    printf("\n=== Duplicate Insert Tests ===\n");
    t = (item){10, "a"};      insertUnique(t, table);  // duplicate
    t = (item){99, "a"};      insertUnique(t, table);  // same key
    t = (item){10, "hello"};  insertUnique(t, table);  // same data

    printf("\n=== Collision Tests ===\n");
    t = (item){50, "kkkkkkkkkk"}; insertUnique(t, table); // len=10 → bucket 0
    t = (item){60, "xyzxyzxyzx"}; insertUnique(t, table); // len=10 → bucket 0
    t = (item){70, "tenchars!!"}; insertUnique(t, table); // len=10 → bucket 0

    printf("\n=== Display After Inserts ===\n");
    display(table);

    printf("\n=== Delete Tests ===\n");
    delete("a", table);           
    delete("xyzxyzxyzx", table);  
    delete("unknown", table);     

    printf("\n=== Display After Deletes ===\n");
    display(table);

    printf("%d", sizeof(int) * sizeof(short int) * 8);
    return 0;
}

int hash(char* key){
    return strlen(key)%10;
}

void insertUnique(item x, Set a){
    int hashVal = hash(x.key);
    int ndx, stopper = (hashVal - 1 + MAX) % MAX;
    int deleted = -5;
    for(ndx = hashVal; ndx != stopper && a[ndx].data != EMPTY && strcmp(a[ndx].key, x.key) != 0; ndx = (ndx + 1) % MAX){
        if(a[ndx].data == DELETED){
            deleted = ndx;
        }
    }

    if(a[ndx].data == EMPTY || deleted != -5){
        int b = a[ndx].data != EMPTY ? deleted : ndx; 
        a[b] = x;
        printf("inserted item %d %s successfully\n", x.data, x.key);
    }else{
        printf("element already exists or no space available\n");
    }
}   

void delete(char* key, Set a){
     int hashVal = hash(key);
    int ndx, stopper = (hashVal - 1 + MAX) % MAX;
    int deleted = -5;
    for(ndx = hashVal; ndx != stopper && a[ndx].data != EMPTY && strcmp(a[ndx].key, key) != 0; ndx = (ndx + 1) % MAX){}
    if(a[ndx].data != EMPTY && strcmp(a[ndx].key, key) == 0){
        printf("item %d, %s deleted successfully\n", a[ndx].data, a[ndx].key);
        a[ndx].data = DELETED;
    }else{
        printf("Data with key %s not found\n", key);
    }
}

void init(Set a){
    for(int ndx = 0; ndx < MAX; ndx++){
        a[ndx].data = EMPTY;
    }
}

void display(Set a){
    for(int ndx = 0; ndx < MAX; ndx++){
        printf("%d: (%d, %s)\n", ndx, a[ndx].data, a[ndx].key);
    }
}