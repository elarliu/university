#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <limits.h>
#include <sys/socket.h>
#include <netinet/in.h>

#ifndef INFO_LIST_H
#define INFO_LIST_H

#define BUFF_SIZE 150

typedef char * Name;
typedef struct Info_Node Info_Node;

struct Info_Node 
{
    Name data;
    int num;
    int socket;
    int msg;
    Info_Node *next;
};

Name 
client_pop(Info_Node **plist);

void 
client_print_list(Info_Node *list);

int 
client_is_empty(Info_Node * list);

void 
client_push_frwrd(Info_Node **plist, Name name, int num, int socket);

void 
client_push_end(Info_Node **plist, Name name, int num, int socket);

int
client_get_len(Info_Node *list);

void 
client_detele_list(Info_Node **plist);

// Node *
// client_get_node(Node *list, int index);

// void 
// client_s_sort(Node *list, int n);

void
client_print_size(Info_Node *list);

int 
client_count_word(Info_Node *list, char *word);

void 
client_most_recent_word(Info_Node *list);

Name
client_get_name(Info_Node *list, int num);

Name
client_pop_by_num(Info_Node **list, int num);

int
client_decrease_num(Info_Node *list);

Info_Node *
client_get_node_by_num(Info_Node *list, int num);

Info_Node *
client_get_node_by_num_2(Info_Node *list, int num);

#endif