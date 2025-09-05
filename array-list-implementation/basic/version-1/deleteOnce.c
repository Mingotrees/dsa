#include <stdio.h>
#include "structures.h"
#include "constants.h"
#include <stdbool.h>
#include <string.h>
#define element 'e'

void deleteFirstOccur(charList* L, char elem);

int main(){
    charList c = {"usc", 3};
    deleteFirstOccur(&c, element);
    for(int i = 0; i < c.count; i++){
        printf("%c", c.elem[i]);
    }
}

void deleteFirstOccur(charList* L, char elem){
    int ndx;
    for(ndx = 0; ndx < L->count && L->elem[ndx] != elem; ndx++){}
    if(ndx < L->count){
        L->count--;     
        // memcpy((L->elem + ndx), (L->elem + ndx + 1) , sizeof(char) * (L->count - ndx - 1));
        for(;ndx < L->count; ndx++){
            L->elem[ndx] = L->elem[ndx + 1];
        }
    }
}

