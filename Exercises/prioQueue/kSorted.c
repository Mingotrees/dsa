#include <stdio.h>
#include <stdlib.h>
#define SIZE 3

struct ListNode{
    int val;
    struct ListNode* next;
};

// lists = [[1,4,5],[1,3,4],[2,6]
struct ListNode* merger(struct ListNode* list1, struct ListNode* list2);
struct ListNode* mergeKLists(struct ListNode** lists, int listsSize);

int main(){
    struct ListNode** lists = NULL;
    lists = (struct ListNode**)malloc(sizeof(struct ListNode*)*SIZE);
    lists[0] = (struct ListNode*)malloc(sizeof(struct ListNode));
    lists[0]->val = 1;
    lists[0]->next = (struct ListNode*)malloc(sizeof(struct ListNode));
    lists[0]->next->val = 4;
    lists[0]->next->next = (struct ListNode*)malloc(sizeof(struct ListNode));
    lists[0]->next->next->val = 5;
    lists[0]->next->next->next = NULL;

    lists[1] = (struct ListNode*)malloc(sizeof(struct ListNode));
    lists[1]->val = 1;
    lists[1]->next = (struct ListNode*)malloc(sizeof(struct ListNode));
    lists[1]->next->val = 3;
    lists[1]->next->next = (struct ListNode*)malloc(sizeof(struct ListNode));
    lists[1]->next->next->val = 4;
    lists[1]->next->next->next = NULL;

    lists[2] = (struct ListNode*)malloc(sizeof(struct ListNode));
    lists[2]->val = 2;
    lists[2]->next = (struct ListNode*)malloc(sizeof(struct ListNode));
    lists[2]->next->val = 6;
    lists[2]->next->next = NULL;

    mergeKLists(lists, SIZE);
}

struct ListNode* merger(struct ListNode* list1, struct ListNode* list2){
    struct ListNode* merge = NULL;
    struct ListNode** mergePtr = &merge;
    while(list1 != NULL && list2 != NULL){
        if(list1->val < list2->val){
            *mergePtr = list1;
            list1 = list1->next;
        }else{
            *mergePtr = list2;
            list2 = list2->next;
        }

        mergePtr = &(*mergePtr)->next;
    }

    if(list1 == NULL){
        *mergePtr = list2;
    }else if(list2 == NULL){
        *mergePtr = list1;
    }

    return merge;
}

struct ListNode* mergeKLists(struct ListNode** lists, int listsSize) {
    if (listsSize == 0) return NULL;
    if (listsSize == 1) return lists[0];

    while (listsSize > 1) {
        int parent = 0;
        for (int i = 0; i < listsSize; i += 2) {
            if (i + 1 < listsSize)
                lists[parent++] = merger(lists[i], lists[i + 1]);
            else
                lists[parent++] = lists[i];
        }
        listsSize = parent; 
    }

    return lists[0];
}
