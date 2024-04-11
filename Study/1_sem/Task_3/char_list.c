#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#define BUFF_SIZE 10

typedef char * Data;
typedef struct Node Node;

struct Node 
{
    Data data;
    Node *next;
};

Data 
pop(Node **plist)
{
    Node *p = *plist;
    Data res = p->data;
    *plist = p->next;

    free(p);
    return res;
}   

void
print_size(Node *list)
{
    int size = 0;

    for(Node *p = list ; p!=NULL ; p = p->next)
    {
        ++size;
    }

    printf("List length: %d\n",size);
}

void 
print(Node *list)
{
    
    
    printf("List: ");

    for(Node *p = list ; p!=NULL ; p = p->next)
    {
        printf("%s ",p->data);
    }
    putchar('\n');
}

int 
is_empty(Node * list) 
{
    return list == NULL;
}

void push_frwrd(Node **plist, Data d)
{
    Node *p = calloc(1,sizeof(Node));
    // char * const ptr = d;
    if (d!= NULL)
    {
        p->data = strdup(d);
        p->next = *plist;

        *plist = p;
    }
}

void 
push_end(Node **plist, Data d)
{
    Node *p = calloc(1,sizeof(Node));
    Node *q = *plist;
    // Node *q = calloc(1,sizeof(Node));
    p->data = strdup(d);
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

int
get_len(Node *list)
{
    int size = 0;

    for(Node *p = list ; p!=NULL ; p = p->next)
    {
        ++size;
    }
    return size;
}

void 
detele_list(Node **plist)
{
    while (!is_empty(*plist))
    {
        free(pop(plist));
    }
}

Node *
get_node(Node *list, int index)
{
    int i = 0;
    for(Node *p = list ; (i <= index) && p!=NULL ; p = p->next, ++i)
    {
        if (i == index)
            return p;
        
    }
}

void 
s_sort(Node *list, int n)
{
    if (list == NULL || n == 1)
        return;

    int min_index,i,j;
    char *s_exch = NULL;
    
    Data data_exch = NULL;

    i = 0;
	
	while (i < n - 1) {
		min_index = i;
		j = i+1;
        // if (arr[i].inode == -1)
        //     printf("popaa");
		while (j<n) 
        {
            // printf("j: %d\n",j);
            // printf("min_index: %d\n",min_index);
            //printf("%s\n",get_node(list,j)->data);
            //printf("%s\n",get_node(list,min_index)->data);
            if (strcmp(get_node(list,j)->data,get_node(list,min_index)->data) < 0)
            {
				min_index = j;
            }
			++j;
		}
        if (strcmp(get_node(list,i)->data,get_node(list,min_index)->data) > 0)
        {
            data_exch = get_node(list,min_index)->data;
            get_node(list,min_index)->data = get_node(list,i)->data;
            get_node(list,i)->data = data_exch;
        }
        
		++i;
	}

}

int 
count_word(Node *list, char *word)
{
    Node *p = list;
    int res = 0;
    while (p != NULL)
    {
        if (!strcmp(p->data, word))
            ++res;
        p = p->next;
    }
    return res;
    // printf("%d\n",res);
}

void 
most_recent_word(Node *list)
{
    int count = 0, max = 0;
    Node *most_recent_node;
    Node *p = list;

    while (p != NULL)
    {
        if ((count = count_word(list, p->data)) > max)
        {
            max = count;
            most_recent_node = p;
        }
        // printf("Times: %d\n",count);
        // printf("Word: %s\n",p->data);
        p = p->next;
    }
    
    printf("Most recent word: %s\n", most_recent_node->data);
    printf("Amount: %d\n", max);


}
