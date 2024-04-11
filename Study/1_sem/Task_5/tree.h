#ifndef TREE_H
#define TREE_H
#include <stdlib.h>
#include <setjmp.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include "list.h"

// виды связей соседних команд в списке команд
enum type_of_next
{
    NXT, 
    AND, 
    OR   
};

typedef struct cmd_inf tree_node;
// typedef node *tree;

struct cmd_inf 
{
    int argc;                           // количество аргументов
    char **argv;                        // список из имени команды и аргументов
    char *infile;                       // переназначенный файл стандартного ввода
    char *outfile;                      // переназначенный файл стандартного вывода
    int append;                         // дозапись в файл
    int backgrnd;                       // = 1, если команда подлежит выполнению в фоновом режиме
    struct cmd_inf *psubcmd;            // команды для запуска в дочернем shell
    struct cmd_inf *pipe;               // следующая команда после "|"
    struct cmd_inf *next;               // следующая после ";" (или после "&")
    enum type_of_next type;             // связь со следующей командой через ; или && или ||
};

void 
print_tree(tree_node *root);

tree_node *
build_tree(Node *list);

void 
delete_tree(tree_node *root);

extern pid_t bckrd_pid;
extern int bckrd_flg;

tree_node *
init_tree(void);

int
is_op(Node *list);

void
add_argv(tree_node *root, char *arg);

tree_node *
rewind_pipe_subshell(tree_node *root);

int 
run_shell_or_subshell(tree_node *root);

int 
tree_handler(tree_node *root);

int
how_much_cmd(tree_node *root);

#endif