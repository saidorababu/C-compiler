#ifndef TREENODE_H
#define TREENODE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

typedef struct List{
    int curr;
    struct List* next;
} List;
typedef struct TreeNode{
    char *label;
    int value;
    char *value_str;
    char *dtype;
    int scope;
    struct TreeNode **children;
    int num_children;
    struct List* trueList;
    struct List* falseList;
    struct List* nextList;
} TreeNode;

TreeNode *createNode(char *label, int value, char *value_str,char *dtype,int scope, int num_children, ...);
TreeNode *create_Node(char *label, int value, char *value_str,char *dtype, int num_children, ...);
#endif /* TREENODE_H */