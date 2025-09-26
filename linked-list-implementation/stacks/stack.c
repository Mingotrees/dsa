#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


#define MAX 10

typedef struct box{
    char cat[MAX];
    struct box* next;
}*PandorasStack;

void whatsInside(PandorasStack*, char cat[]);
void giveUp(PandorasStack*);
char* reveal(PandorasStack S);


int main(){

    return 0;
}