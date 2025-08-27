#include <stdio.h>
#include "structures.h"
#include "constants.h"
#include <stdbool.h>
#define element 't'

bool findElem(charList nigga, char elem);

int main(){
    charList a = { "usc", 3};
    bool exist = findElem(a, element);
    printf("%s", a.count ? exist ? "Element Found" : "Element Not Found" : "No Elements in the Array");
}

bool findElem(charList nigga, char elem){
    int ndx;
    for(ndx = 0; ndx < nigga.count && nigga.elem[ndx] != elem; ndx++){}
    return ndx < nigga.count ? true : false;
}

