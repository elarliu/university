#ifndef CHAR_LIST
#define CHAR_LIST

#define BUFF_SIZE 10

typedef char * Data;
typedef struct Node Node;

struct Node 
{
    Data data;
    Node *next;
};

Data 
pop(Node **plist);

void 
print(Node *list);

int 
is_empty(Node * list);

void 
push_frwrd(Node **plist, Data d);

void 
push_end(Node **plist, Data d);

int
get_len(Node *list);

void 
detele_list(Node **plist);

Node *
get_node(Node *list, int index);

void 
s_sort(Node *list, int n);

void
print_size(Node *list);

int 
count_word(Node *list, char *word);

void 
most_recent_word(Node *list);

#endif