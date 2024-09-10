#include<stdio.h>
#include <bits/stdc++.h>

struct slinklist {
    int data;
    struct slinklist* next;
};

typedef struct slinklist node;

node *start=NULL;

node* getnode(){
    node* newnode;
    newnode =(node*) malloc(sizeof(node));
    printf("\n Enter data :");
    scanf("%d",&newnode->data);
    newnode->next = NULL;
    return newnode;
}

void traverse()
{
    node *temp;
    temp = start;
    printf("\n The contents of List (Left to Right):\n"); 
    if(start == NULL )
        printf("\n Empty List");
    else
    {
        while (temp != NULL)
        {
            printf("%d ->", temp -> data);
            temp = temp -> next;
        }
    }
    printf("X");
}
int countnode(node *st){
    if(st == NULL)
        return 0;
    else
    return(1 + countnode(st -> next));
}
void createlist(int n){
    node* newnode;
    node* temp;
    for (int i=0;i<n;i++){
        newnode = getnode();
        if (start==NULL){
            start=newnode;
        }
        else {
            temp=start;
            while (temp->next!=NULL){
                temp=temp->next;
            }
            temp->next=newnode;
        }
    }
}
void insert_at_beg(){
    node* newnode;
    newnode=getnode();
    if (start==NULL){
        start=newnode;
    }
    else{
        newnode->next=start;
        start=newnode;
    }
}
void insert_at_end(){
    node *newnode, *temp;
    newnode=getnode();
    if (start==NULL){
        start=newnode;
    }
    else{
        temp=start;
        while(temp->next!=NULL){
            temp=temp->next;
        }
        temp->next=start;
    }
}
void insert_at_mid(){
    node *newnode, *temp, *prev;
    int pos,nodectr, ctr=1;
    newnode=getnode();
    printf("\n Enter the Position :");
    scanf("%d",&pos);
    nodectr=countnode(start);
    if(pos>1 && pos<nodectr){
        temp=prev=start;
        while(ctr<pos){
            prev=temp;
            temp=temp->next;
            ctr++;
        }
        prev->next=newnode;
        newnode->next=temp;
    }
    else {
        printf("%d is not a middle position",pos);
    }
}

void delete_at_beg(){
    node* temp;
    if (start==NULL){
        printf("\n No nodes exist");
        return ;
    }
    else{
        temp=start;
        start=temp->next;
        free(temp);
        printf("\n Node deleted");
    }
}

void delete_at_end(){
    node *temp,*prev;
    if (start==NULL){
        printf("\n No nodes exist");
        return ;
    }
    else{
        temp=start;
        prev=start;
        while(temp->next!=NULL){
            prev=temp;
            temp=temp->next;
        }
        prev->next=NULL;
        free(temp);
        printf("\n Node deleted");
    }
}

void delete_at_mid(){
    int ctr=1,pos,nodectr;
    node *temp,*prev;
    if (start==NULL){
        printf("\n No nodes exist");
        return ;
    }
    else{
        printf("\n Enter position of node to delete: ");
        scanf("%d", &pos);
        nodectr = countnode(start);
        if(pos > nodectr){
            printf("\nThis node doesnot exist");
        }
        if (pos>1 && pos<nodectr){
            temp=prev=start;
            while(ctr < pos)
            {
                prev = temp;
                temp = temp -> next;
                ctr ++;
            }
            prev -> next = temp -> next;
            free(temp);
            printf("\n Node deleted");
        } 
    }
}
