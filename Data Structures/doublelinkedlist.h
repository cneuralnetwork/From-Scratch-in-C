#include <stdio.h>
#include <stdlib.h>

struct node
{
    int num;              // value
    struct node *preptr;  // head
    struct node *nextptr; // tail
} *stnode, *ennode;

void DlListcreation(int n);
void DlLinsertNodeAtBeginning(int num);
void DlLinsertNodeAtEnd(int num);
void DlLinsertNodeAtAny(int num, int pos);
void displayDlList(int a);

void DlListcreation(int n)
{
    int i, num;
    struct node *fnNode;
    if (n >= 1)
    {
        stnode = (struct node *)malloc(sizeof(struct node));
        if (stnode != NULL)
        {
            printf(" Input data for node 1 : "); // assigning data in the first node
            scanf("%d", &num);
            stnode->num = num;
            stnode->preptr = NULL;
            stnode->nextptr = NULL;
            ennode = stnode;
            for (i = 2; i <= n; i++)
            {
                fnNode = (struct node *)malloc(sizeof(struct node));
                if (fnNode != NULL)
                {
                    printf(" Input data for node %d : ", i);
                    scanf("%d", &num);
                    fnNode->num = num;
                    fnNode->preptr = ennode;  // new node is linking with the previous node
                    fnNode->nextptr = NULL;   // set next address of fnnode is NULL
                    ennode->nextptr = fnNode; // previous node is linking with the new node
                    ennode = fnNode;          // assign new node as last node
                }
                else
                {
                    printf(" Memory can not be allocated.");
                    break;
                }
            }
        }
        else
        {
            printf(" Memory can not be allocated.");
        }
    }
}

void DlLinsertNodeAtAny(int num, int pos)
{
    int i;
    struct node *newnode, *tmp;
    if (ennode == NULL)
    {
        printf(" No data found in the list!\n");
    }
    else
    {
        tmp = stnode;
        i = 1;
        while (i < pos - 1 && tmp != NULL)
        {
            tmp = tmp->nextptr;
            i++;
        }
        if (pos == 1)
        {
            DlLinsertNodeAtBeginning(num);
        }
        else if (tmp == ennode)
        {
            DlLinsertNodeAtEnd(num);
        }
        else if (tmp != NULL)
        {
            newnode = (struct node *)malloc(sizeof(struct node));
            newnode->num = num;              // next address of new node is linking with the next address of temp node
            newnode->nextptr = tmp->nextptr; // previous address of new node is linking with the tmp node
            newnode->preptr = tmp;
            if (tmp->nextptr != NULL)
            {
                tmp->nextptr->preptr = newnode; // n+1th node is linking with new node
            }
            tmp->nextptr = newnode; // n-1th node is linking with new node
        }
        else
        {
            printf(" The position you entered, is invalid.\n");
        }
    }
}

void DlLinsertNodeAtBeginning(int num)
{
    struct node *newnode;
    if (stnode == NULL)
    {
        printf(" No data found in the list!\n");
    }
    else
    {
        newnode = (struct node *)malloc(sizeof(struct node));
        newnode->num = num;
        newnode->nextptr = stnode; // next address of new node is linking with starting node
        newnode->preptr = NULL;    // set previous address field of new node is NULL
        stnode->preptr = newnode;  // previous address of starting node is linking with new node
        stnode = newnode;          // set the new node as starting node
    }
}

void DlLinsertNodeAtEnd(int num)
{
    struct node *newnode;
    if (ennode == NULL)
    {
        printf(" No data found in the list!\n");
    }
    else
    {
        newnode = (struct node *)malloc(sizeof(struct node));
        newnode->num = num;
        newnode->nextptr = NULL;   // set next address field of new node  is NULL
        newnode->preptr = ennode;  // previous address of new node is linking with ending node
        ennode->nextptr = newnode; // next address of ending node is linking with new node
        ennode = newnode;          // set the new node as ending node
    }
}

void displayDlList(int m)
{
    struct node *tmp;
    int n = 1;
    if (stnode == NULL)
    {
        printf(" No data found in the List yet.");
    }
    else
    {
        tmp = stnode;
        if (m == 1)
        {
            printf("\n Data entered in the list are :\n");
        }
        else
        {
            printf("\n After insertion the new list are :\n");
        }
        while (tmp != NULL)
        {
            printf(" node %d : %d\n", n, tmp->num);
            n++;
            tmp = tmp->nextptr; // current pointer moves to the next node
        }
    }
}