#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXLEN 10


enum
{
    CODE_FOR_WRONG_INPUT = 1,
};

typedef char * Data;
typedef struct Node Node;

struct Node 
{
    Data data;
    Node *next;
};

// void push(Node **list, Data x);

Data pop(Node **plist)
{
    Node *p = *plist;
    Data res = p->data;
    *plist = p->next;

    free(p);
    return res;
}   

void print(Node *list)
{
    printf("List: ");
    
    for(Node *p = list ; p!=NULL ; p = p->next)
    {
        printf("%s ",p->data);
     
    }
    putchar('\n');
}

void pop_alike(Node *plist)
{
    Node *p = plist;
    Data check = plist->data;
    
    while (p->next != NULL)
    {
        // printf("Comparing data: %s Temporary data: %s\n",check,(p->next)->data);
        
        if (strcmp(check,(p->next)->data)==0)
        {
            // printf("pops\n");
            // pop(&(p->next));
            free(pop(&(p->next)));
        }
        else
        {
            p = p->next;
        }
            
    }
    
}

int is_empty(Node * list) 
{
    return list == NULL;
}

void
the_longest(Node *plist)
{
    char longest[MAXLEN];
    Node *p = plist;

    while (p != NULL)
    {
        if (strlen(p->data) > strlen(longest))
        {
            memcpy(longest,p->data,strlen(p->data));
        }
        p = p->next;
    }
    printf("The longest line: %s\n",longest);
    
    
}

void push_frwrd(Node **plist, Data d)
{
    Node *p = calloc(1,sizeof(Node));
    // char * const ptr = d;

    p->data = strdup(d);
    p->next = *plist;

    *plist = p;

}

void push_end(Node **plist, Data d)
{
    Node *p = calloc(1,sizeof(Node));
    Node *q = calloc(1,sizeof(Node));
    q = *plist;
    // Node *q = calloc(1,sizeof(Node));
    p->data = d;
	p->next = NULL;
    
    if (*plist == NULL)
    {
        *plist = p;
    }
    else
    {
        while ((q->next)!=NULL)
        {
            q = q->next;
        }
        (q->next) = p;
    }
    
}

void detele_list(Node **plist)
{
    while (!is_empty(*plist))
    {
        free(pop(plist));
    }
    
}

int
main(void)
{
    Node *list = NULL;
    int s;
    
    char *str,str_push[MAXLEN];

    // char *ptr;
    // ptr = "123";

    // push_frwrd(&list,ptr);
    // ptr = "abc";
    // push_frwrd(&list,ptr);

    // // push(&list,"dshjhsdf")
    // // push(&list,"kfsjg")
    // print(list);
    // detele_list(&list);

    

    while ((s = (scanf("%s",str_push)))!=EOF)
    {
        // printf("%s\n",str_push);
        // strcpy(str_push,str);
        push_frwrd(&list,str_push);
        
    }
    
    // print(list);


    if(s!=-1)
    {
        fprintf(stderr, "There is an error in input: %d\n", CODE_FOR_WRONG_INPUT);
        return CODE_FOR_WRONG_INPUT;
    }
    else
    {
        if (list != NULL)
        {

            pop_alike(list);
            // pop(&(list->next));
            print(list);
            the_longest(list);
            detele_list(&list);
        }
        else
        {
            printf("List is empty");
        }

        

        // printf("%s\n",pop(&list));
        // print(list);
        return 0;
    }
}
