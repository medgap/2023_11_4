#include<stdio.h>
#include<stdlib.h>

typedef struct TreeNode
{
    char data;
    struct TreeNode* lchild;
    struct TreeNode* rchild;
}TreeNode;

typedef struct StackNode
{
    TreeNode* data;
    struct StackNode* next;
}StackNode;

void createTree(TreeNode** t,char* data,int* index){
    char ch = data[*index];
    *index += 1;
    if(ch == '#'){
        *t = NULL;
        return;
    }
    else{
        *t = (TreeNode*)malloc(sizeof(TreeNode));
        (*t)->data = ch;
        createTree(&((*t)->lchild),data,index);
        createTree(&((*t)->rchild),data,index);
    }
}

StackNode* initStack(){
    StackNode* s = (StackNode*)malloc(sizeof(StackNode));
    s->data = NULL;
    s->next = NULL;
    return s;
}

int isEmpty(StackNode* s){
    if(s->next == NULL)
        return 1;
    return 0;
}

//出栈
StackNode* pop(StackNode* s){
    if(isEmpty(s)){
        return NULL;
    }
    else{
        StackNode* node = s->next;
        s->next = node->next;
        return node;
    }
}

void push(StackNode* s,TreeNode* t){
    StackNode* node = (StackNode*)malloc(sizeof(StackNode));
    node->next = s->next;
    s->next = node;
    node->data = t;
}

void preOrder(TreeNode* t){
    StackNode* s = initStack();
    TreeNode* node = t;
    while(node || !isEmpty(s)){
        if(node){
            printf("%c ",node->data);
            push(s,node);
            node = node->lchild;
        }
        else{
            node = pop(s)->data;
            node = node->rchild;
        }
    }
}

void inOrder(TreeNode* t){
    StackNode* s = initStack();
    TreeNode* node = t;
    while(node || !isEmpty(s)){
        if(node){
            push(s,node);
            node = node->lchild;
        }
        else{
            node = pop(s)->data;
            printf("%c ",node->data);
            node = node->rchild;
        }
    }
}

int main(){
    TreeNode* t;
    int index = 0;
    createTree(&t,"ABD##E##CF##G##",&index);
    preOrder(t);
    printf("\n");
    inOrder(t);
    printf("\n");
    return 0;
}