#ifndef CODE_H
#define CODE_H
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct threeAddrCode{
    char *result;
    char* operation;
    char* op1;
    char* op2;
} threeAddrCode;

typedef struct List{
    int curr;
    struct List* next;
}List;

static inline threeAddrCode* createCode(char* result, char* operation, char* op1, char* op2){
    threeAddrCode* code = (threeAddrCode*)malloc(sizeof(threeAddrCode));
    code->result = (char*)malloc(strlen(result)+1);
    strcpy(code->result, result);
    code->operation = (char*)malloc(strlen(operation)+1);
    strcpy(code->operation, operation);
    code->op1 = (char*)malloc(strlen(op1)+1);
    strcpy(code->op1, op1);
    code->op2 = (char*)malloc(strlen(op2)+1);
    strcpy(code->op2, op2);
    return code;
}

static inline void printCode(threeAddrCode* code){
    printf("%s = %s %s %s\n", code->result, code->op1, code->operation, code->op2);
}

static inline List* newList(int i){
    List* list = (List*)malloc(sizeof(List));
    list->curr = i;
    list->next = NULL;
    return list;
}

static inline List* mergeList(List* list1, List* list2){
    List* temp = list1;
    while(temp->next != NULL){
        temp = temp->next;
    }
    temp->next = list2;
    return list1;
}


