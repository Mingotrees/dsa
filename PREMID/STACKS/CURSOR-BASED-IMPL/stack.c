#include <stdio.h>
#include <stdlib.h>
#define MAX 10

typedef struct{
    int data;
    int next;
}nodetype;

typedef struct{
    nodetype arr[MAX];
    int avail;
}VHeap;

typedef int Stack;

int allocSpace(VHeap*);
void deallocSpace(VHeap*, int);
void push(Stack*, VHeap*, int);
void pop(Stack*, VHeap*);
void display(Stack*, VHeap*);
void initStack(Stack*, VHeap*);
int top(Stack, VHeap );


int main(){
 Stack S;
    VHeap H;

    printf("=== STACK TEST PROGRAM ===\n\n");

    /* ------------------------------
       Uncomment one test block at a time
    ----------------------------------- */

    /* ---------- Test 1: Basic Push ---------- */
    
   /*  initStack(&S, &H);
    push(&S, &H, 10);
    push(&S, &H, 20);
    push(&S, &H, 30);
    display(&S, &H);   // Expected: 30 20 10
    */

    /* ---------- Test 2: Push Until Full ---------- */
    
   /*  initStack(&S, &H);
    for(int i = 1; i <= 10; i++){
        push(&S, &H, i * 5);
    }
    display(&S, &H);   // Expected: 50 45 40 35 30 25 20 15 10 5 */
    

    /* ---------- Test 3: Pop Test ---------- */
    
/*     initStack(&S, &H);
    push(&S, &H, 1);
    push(&S, &H, 2);
    push(&S, &H, 3);
    pop(&S, &H);
    pop(&S, &H);
    display(&S, &H);   // Expected: 1
    */

    /* ---------- Test 4: Underflow Test ---------- */
    
/*     initStack(&S, &H);
    pop(&S, &H);       // Should do nothing
    display(&S, &H);   // Expected: <no output> */
   

    /* ---------- Test 5: Top Test ---------- */
    
/*     initStack(&S, &H);
    push(&S, &H, 100);
    push(&S, &H, 200);
    printf("Top = %d\n", top(S, H));  // Expected: 200
     */

    /* ---------- Test 6: Random Push/Pop Sequence ---------- */
    
   /*  initStack(&S, &H);
    push(&S, &H, 10);
    push(&S, &H, 20);
    pop(&S, &H);
    push(&S, &H, 30);
    push(&S, &H, 40);
    pop(&S, &H);
    display(&S, &H);   // Expected: 30 10
     */

    /* ---------- Test 7: Display should not destroy stack ---------- */
    
  /*   initStack(&S, &H);
    push(&S, &H, 5);
    push(&S, &H, 6);
    push(&S, &H, 7);

    printf("Display 1: ");
    display(&S, &H);
    printf("\nDisplay 2: ");
    display(&S, &H);
    // Expected both: 7 6 5
     */

    return 0;
}

int allocSpace(VHeap* a){
    int temp = a->avail;
    if(temp != -1){
        a->avail = a->arr[temp].next;
    }
    return temp;
}

void deallocSpace(VHeap* a, int node){
    if(node != -1){
        a->arr[node].next = a->avail;
        a->avail = node;
    }
}

void push(Stack* s, VHeap* a, int data){
    int space = allocSpace(a);
    if(space != -1){
        a->arr[space].data = data;
        a->arr[space].next =  *s;
        *s = space;
    }
}

void pop(Stack* s, VHeap* a){
    if(*s != -1){
        int temp = *s;
        *s = a->arr[temp].next;
        deallocSpace(a, temp);
    }
}

int top(Stack s, VHeap a){
    return s != -1 ? a.arr[s].data : -1;
}

void display(Stack* a, VHeap* b){
    Stack temp;
    VHeap tempHeap;
    initStack(&temp, &tempHeap);
    while(*a != -1){
        printf("%d ", top(*a, *b));
        push(&temp, &tempHeap, top(*a, *b));
        pop(a, b);
    }

    while(temp != -1){
        push(a, b, top(temp, tempHeap));
        pop(&temp, &tempHeap);
    }
}

void initStack(Stack* a,  VHeap* b){
    *a = -1;
    int ndx;
    b->avail = MAX-1;
    for(ndx = 0; ndx < MAX; ndx++){
        b->arr[ndx].next = ndx-1;
    }
}

