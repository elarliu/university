#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <limits.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include "info_list.h"
// #define BUFF_SIZE 30

// typedef char * Data;
// typedef struct Info_Node Info_Node;

// struct Info_Node 
// {
//     Data data;
//     Info_Node *next;
// };

// enum
// {
//     ORDINARY_WORK = 0,
//     END_OF_LINE = 1,
//     END_OF_FILE = 2
// };

Name 
client_pop(Info_Node **plist)
{
    Info_Node *p = *plist;
    Name res = p->data;
    *plist = p->next;

    // close(p->num);
    free(p);
    return res;
}   

Name
client_pop_by_num(Info_Node **list, int num)
{
        
    Info_Node *p = *list;
    Info_Node *q = NULL;

    // printf("num: %d\n", num);
    // printf("p_num: %d\n", p->num);
    
    while ((p != NULL) && (p->num != num))
    {
        q = p;
        p = p->next;
    }
    
    
    if (p->num == num)
    {
        Name res = p->data;
        
        if((q == NULL) && (p->next == NULL))
        {
            *list = NULL;
            free(p);
            return res;    
        }
        else if(q == NULL)
        {
            *list = p->next;
            free(p);
            return res; 
        }
        else
        {
            q->next = p->next;
            free(p);
            return res;
        }

    }

    return NULL;

}

void
client_print_size(Info_Node *list)
{
    int size = 0;

    for(Info_Node *p = list ; p != NULL ; p = p->next)
    {
        ++size;
    }

    printf("List length: %d\n",size);
}

void 
client_print_list(Info_Node *list)
{
    printf("Users:\n");

    for(Info_Node *p = list ; p != NULL ; p = p->next)
    {
        printf("Name: %s",p->data);
        // printf("Name: %s",p->data);
        printf("Socket ID: %d\n",p->socket);
        printf("Num: %d\n",p->num);
        // printf("\n");
    }

}

int 
client_is_empty(Info_Node * list) 
{
    return list == NULL;
}

void 
client_push_frwrd(Info_Node **plist, Name name, int num, int socket)
{
    Info_Node *p = calloc(1,sizeof(Info_Node));
    // char * const ptr = d;
    if (name != NULL)
    {
        p->data = strdup(name);
        p->next = *plist;
        p->num = num;
        p->socket = socket;

        *plist = p;
    }
}

void 
client_push_end(Info_Node **plist, Name name, int num, int socket)
{
    Info_Node *p = calloc(1,sizeof(Info_Node));
    Info_Node *q = *plist;
    // Info_Node *q = calloc(1,sizeof(Info_Node));
    p->data = strdup(name);
    p->socket = socket;
	p->next = NULL;
    p->msg = 3;
    p->num = num;
    
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
client_get_len(Info_Node *list)
{
    int size = 0;

    for(Info_Node *p = list ; p!=NULL ; p = p->next)
    {
        ++size;
    }
    return size;
}

void 
client_detele_list(Info_Node **plist)
{
    while (!client_is_empty(*plist))
    {
        free(client_pop(plist));
    }
}

// Info_Node *
// get_node(Info_Node *list, int index)
// {
//     int i = 0;
//     for(Info_Node *p = list ; (i <= index) && p!=NULL ; p = p->next, ++i)
//     {
//         if (i == index)
//             return p;
        
//     }
//     return NULL;
// }

// void 
// s_sort(Info_Node *list, int n)
// {
//     if (list == NULL || n == 1)
//         return;

//     int min_index,i,j;
//     char *s_exch = NULL;
    
//     Name data_exch = NULL;

//     i = 0;
	
// 	while (i < n - 1) {
// 		min_index = i;
// 		j = i+1;
//         // if (arr[i].inode == -1)
//         //     printf("popaa");
// 		while (j<n) 
//         {
//             // printf("j: %d\n",j);
//             // printf("min_index: %d\n",min_index);
//             //printf("%s\n",get_node(list,j)->data);
//             //printf("%s\n",get_node(list,min_index)->data);
//             if (strcmp(get_node(list,j)->data, get_node(list,min_index)->data) < 0)
//             {
// 				min_index = j;
//             }
// 			++j;
// 		}
//         if (strcmp(get_node(list,i)->data, get_node(list,min_index)->data) > 0)
//         {
//             data_exch = get_node(list,min_index)->data;
//             get_node(list,min_index)->data = get_node(list,i)->data;
//             get_node(list,i)->data = data_exch;
//         }
        
// 		++i;
// 	}

// }

int 
client_count_word(Info_Node *list, char *word)
{
    Info_Node *p = list;
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
client_most_recent_word(Info_Node *list)
{
    int count = 0, max = 0;
    Info_Node *most_recent_node;
    Info_Node *p = list;

    while (p != NULL)
    {
        if ((count = client_count_word(list, p->data)) > max)
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

Name
client_get_name(Info_Node *list, int num)
{
    Info_Node *p = list;
    int i = 1;
    while (p->num != num)
    {
        p = p->next;
    }
    // p->data[strlen(p->data) - 1] = '\0';
    return p->data;    
}

int
client_decrease_num(Info_Node *list)
{
    Info_Node *p = list;
    while (p != NULL)
    {
        --p->num;
        p = p->next;
    }

    return 0;
    
}

Info_Node *
client_get_node_by_num(Info_Node *list, int num)
{
    Info_Node * p = list;
    while ((p != NULL) && (p->num != num))
    {
        p = p->next;
    }

    if (p == NULL)
        return NULL;
    else
        return p->next;
}

Info_Node *
client_get_node_by_num_2(Info_Node *list, int num)
{
    Info_Node * p = list;
    while ((p != NULL) && (p->num != num))
    {
        p = p->next;
    }

    return p;
}