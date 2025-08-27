#include <stdio.h>
#include "structures.h"
#include "constants.h"
#include <stdbool.h>
#include <string.h>
#define element 't'

void deleteAllOccur(charList* L, char elem);

int main(){
    charList c = {"uuauuu", 5};
    deleteAllOccur(&c, element);
    for(int i = 0; i < c.count; i++){
        printf("%c", c.elem[i]);
    }
}

void deleteAllOccur(charList* L, char elem){
    int ndx, count = 0;
    for(ndx = 0; ndx < L->count; ndx++){
        // if(L->elem[ndx] == elem){
        //     L->count--;     
        //     // memcpy((L->elem + ndx), (L->elem + ndx + 1) , sizeof(char) * (L->count - ndx - 1));
        //     for(int j = ndx; j < L->count; j++){
        //         L->elem[j] = L->elem[j + 1];
        //     }
        // }else{
        //     ndx++;
        // }
    }
}

