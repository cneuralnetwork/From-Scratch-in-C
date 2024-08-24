#include <stdio.h>
#include <stdlib.h>

struct Node{
        int val;
        struct Node* next;
};

struct Stack{
        struct Node* top;
};

struct Node* create_stack(int data){
        struct Node* newnode=(struct Node*)malloc(sizeof(struct Node));
        newnode->val=data;
        newnode->next=NULL;
        return newnode;
}

void init_stack(struct Stack* stk){
        stk->top=NULL;
}

int is_empty(struct Stack* stk){
        return stk->top==NULL;
}

void push(struct Stack* stk,int it){
        struct Node* newnode=create_stack(it);
        newnode->next=stk->top;
        stk->top=newnode;
}

int pop(struct Stack* stk){
        if(is_empty(stk)){
                printf("Empty Stack");
                return -1;
        }
        struct Node* temp=stk->top;
        int data=temp->val;
        stk->top=stk->top->next;
        return data;
}

void prnt(struct Stack* stk){
        if(is_empty(stk)){
                printf("Empty Stack");
                return;
        }
        printf("The Stack : ");
        struct Node* curr=stk->top;
        while(curr!=NULL){
                printf("%d ",curr->val);
                curr=curr->next;
        }
        printf("\n");
}

int peek(struct Stack* stk){
	return stk->top->val;
}