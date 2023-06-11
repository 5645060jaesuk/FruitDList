#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef char element[100];
typedef struct DListNode {
    element data;
    struct DListNode* llink;
    struct DListNode* rlink;
} DListNode;

DListNode* current;

void init(DListNode* phead)
{
    phead->llink = phead;
    phead->rlink = phead;
}

void dinsert(DListNode* before, element data)
{
    DListNode* newnode = (DListNode*)malloc(sizeof(DListNode));
    strcpy_s(newnode->data, sizeof(newnode), data);
    newnode->llink = before;
    newnode->rlink = before->rlink;
    before->rlink->llink = newnode;
    before->rlink = newnode;
}

void ddelete(DListNode* head, DListNode* removed)
{
    if (removed == head) return;
    removed->llink->rlink = removed->rlink;
    removed->rlink->llink = removed->llink;
    free(removed);
}

void print_dlist(DListNode* phead)
{
    DListNode* p;
    for (p = phead->rlink; p != phead; p = p->rlink) {
        if (p == current)
            printf("%s [o]", p->data);
        else
            printf("%s", p->data);
        printf("\n");
    }
    printf("\n");
}



void error(char* message)
{
    fprintf(stderr, "%s\n", message);
    exit(1);
}

int main(void)
{
    int cnt = 0;
    char ch;
    char name[100];
    DListNode* head = (DListNode*)malloc(sizeof(DListNode));
    init(head);
    current = head->rlink;

    do
    {
        printf("==== MENU ====\n");
        printf("n) next fruit\n");
        printf("p) previous fruit\n");
        printf("d) delete the current fruit\n");
        printf("i) insert fruit after current fruit\n");
        printf("o) output the fruit list(Output [o] at the end of the currently selected fruit)\n");
        printf("e) exit the program\n");
        printf("====================\n");
        printf("Select a menu : ");
        scanf_s(" %c", &ch, sizeof(ch));

        if (ch == 'n')
        {
            current = current->rlink;
            if (current == head)
                current = current->rlink;
            printf("\n");
            cnt++;
        }
        else if (ch == 'p')
        {
            current = current->llink;
            if (current == head)
                current = current->llink;
            printf("\n");
            cnt--;
        }
        else if (ch == 'd')
        {
            current = head->rlink;
            ddelete(current, current->rlink);
        }
        else if (ch == 'i')
        {
            printf("enter the name of the fruit to add :");
            scanf_s("%s", &name, sizeof(name));
            printf("\n");
            dinsert(current, name);
            current = head->rlink;

        }

        else if (ch == 'o')
        {
            if (cnt >= 0)
            {
                for (int i = 0; i < cnt; i++)
                {
                    current = current->rlink;
                    if (current == head)
                        current = current->rlink;
                }
                print_dlist(head);
            }
            else if (cnt < 0)
            {
                for (int i = 0; i > cnt; i--)
                {
                    current = current->llink;
                    if (current == head)
                        current = current->llink;
                }
                print_dlist(head);
            }

        }

        else if (ch == 'e')
        {
            break;
        }
        else
        {
            printf("invalid menu\n");
        }
    } while (1);

    return 0;
}