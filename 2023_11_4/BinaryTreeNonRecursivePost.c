#include<stdio.h>
#include<stdlib.h>

typedef struct TreeNode
{
    char data;
    struct TreeNode* lchild;
    struct TreeNode* rchild;
    int flag;
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
    }
    else{
        *t = (TreeNode*)malloc(sizeof(TreeNode));
        (*t)->data = ch;
        (*t)->flag = 0;
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

StackNode* getTop(StackNode* s){
    if(isEmpty(s)){
        return NULL;
    }
    else{
        StackNode* node = s->next;
        return node;
    }
}

void push(StackNode* s,TreeNode* t){
    StackNode* node = (StackNode*)malloc(sizeof(StackNode));
    node->data = t;
    node->next = s->next;
    s->next = node;
}



void postOrder(TreeNode* t){
    StackNode* s = initStack();
    TreeNode* node = t;
    while(node || !isEmpty(s)){
        if(node){
            push(s,node);
            node = node->lchild;
        }
        else{
            TreeNode* top = getTop(s)->data;
            if(top->rchild && top->rchild-> flag == 0){
                top = top->rchild;
                push(s,top);
                node = top->lchild;
            }
            else{
                top = pop(s)->data;
                printf("%c ",top->data);
                top->flag = 1;
            }
        }
    }
}

int main(int argc, char* argv[]){
    TreeNode* t;
    int index = 0;
    //createTree(&t,"ABD##E##CF##G##",&index);
    createTree(&t,argv[1],&index);
    postOrder(t);
    printf("\n");
    return 0;
}