#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct node{
    int data;
    struct node* next;
}*LIST;

void init_list(LIST*);
void read_list(LIST); // display
int locate_elem(LIST, int);
bool is_member(LIST, int);
void make_null(LIST*);

void insert_first(LIST*, int);
void insert_last(LIST*, int);
void insert_sorted(LIST*, int);
void insert_sorted_unique(LIST*, int);

void delete_first(LIST*);
void delete_last(LIST*);
void delete_elem(LIST*, int);
void delete_all_occur(LIST*, int);

int main(){
    LIST a;
    init_list(&a);
    insert_sorted(&a, 1);
    insert_sorted(&a, 2);
    insert_sorted(&a, 2);
    insert_sorted_unique(&a, 4);
    insert_sorted_unique(&a, 3);
    read_list(a);
    delete_all_occur(&a, 2);
    read_list(a);
    int location = locate_elem(a, 1);
    printf("%d", location + 1);

}

void init_list(LIST* A){
    *A = NULL;
}

void read_list(LIST A){
    for(;A != NULL; A = A->next){
        printf("%d ", A->data);
    }
    printf("\n");
} // display

int locate_elem(LIST A, int B){
    int ndx;
    for(ndx = 0;A != NULL && A->data != B; A = A->next, ndx++){}
    return A != NULL ? ndx : -1;
}

bool is_member(LIST A, int B){
    for(;A != NULL && A->data != B; A = A->next){}
    return A != NULL ? true : false;
}

void make_null(LIST* A){
    LIST temp;
    for(;*A != NULL; A = &(*A)->next, free(temp)){
        temp = *A;
    }
}

void insert_first(LIST* A, int B){
    LIST temp = *A;
    *A = (LIST)malloc(sizeof(struct node));
    (*A)->data = B;
    (*A)->next = temp;
}

void insert_last(LIST* A, int B){
    LIST* ptr;
    for(ptr = A; *A != NULL ; A = &(*A)->next){}
    *ptr = (LIST)malloc(sizeof(struct node));
    if(ptr != NULL){
        (*ptr)->data = B;
        (*ptr)->next = NULL;
    }
}

void insert_sorted(LIST* A, int B){
    LIST* ptr;
    for(ptr = A; *ptr != NULL && (*ptr)->data < B; ptr = &(*ptr)->next){}
    if(*ptr == NULL || (*ptr)->data <= B){
        LIST temp = *ptr;
        *ptr = (LIST)malloc(sizeof(struct node));
        if(*ptr != NULL){
            (*ptr)->data = B;
            (*ptr)->next = temp;
        }
    } 
}

void insert_sorted_unique(LIST* A, int B){
    LIST* ptr;
    for(ptr = A; *ptr != NULL && (*ptr)->data < B; ptr = &(*ptr)->next){}
    if(*ptr == NULL || (*ptr)->data != B){
        LIST temp = *ptr;
        *ptr = (LIST)malloc(sizeof(struct node));
        if(*ptr != NULL){
            (*ptr)->data = B;
            (*ptr)->next = temp;
        }
    }else{
        printf("element already exists\n");
    }
}

void delete_first(LIST* A){
    if(*A != NULL){
        LIST temp = *A;
        *A = temp->next;
        free(temp);
    }
}

void delete_last(LIST* A){
    LIST* ptr;
    for(ptr = A; *ptr != NULL && (*ptr)->next != NULL; ptr = &(*ptr)->next){}
    if(*ptr != NULL){
        LIST temp = *ptr;
        *ptr = NULL;
        free(temp);
    }
}

void delete_elem(LIST* A, int B){
    LIST* ptr;
    for(ptr = A; *ptr != NULL && (*ptr)->data != B; ptr = &(*ptr)->next){}
    if(*ptr != NULL){
        LIST temp = *ptr;
        *ptr = temp->next;
        free(temp);
    }
}

void delete_all_occur(LIST* A, int B){
    LIST* ptr;
    for(ptr = A; *ptr != NULL; ){
        if((*ptr)->data == B){
            LIST temp = *ptr;
            *ptr = temp->next;
            free(temp);
        }else{
            ptr = &(*ptr)->next;
        }
    }
}