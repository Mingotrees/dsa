#include <stdio.h>

typedef struct{
    int count;
}letters;

int main(){
    letters letter[28] = {0};
    printf("%d", letter[0].count);
}