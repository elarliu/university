#include <stdlib.h>
#include <setjmp.h>
#include <stdio.h>
#include <string.h>
#include <signal.h>
#include <errno.h>
#include <sys/wait.h>
#include "list.h"
#include "tree.h"
#include "error.h"

// int
// is_parse(Node *elem)
// {
//     char c = elem->data[0];
//     switch (c)
//     {
//     case '|':
//     case '&':
//     case ';':
//     case '>':
//     case '<':
//     case ')':
//     case '(':
//         return 0;
//     }
//     return 1;
// }

tree_node *
init_tree(void)
{
    tree_node *root = calloc(1, sizeof(tree_node));
    
    root->argc = 0;
    root->argv = calloc(1, sizeof(char *));
    root->infile = NULL;
    root->outfile = NULL;
    root->append = 0;
    root->backgrnd = 0;
    root->psubcmd = NULL;
    root->pipe = NULL;
    root->type = NXT;
    
    return root;
    
}

void 
print_tree(tree_node *root)
{
    if (root == NULL)
        return;

    // the root itself should be -1
    printf("\n");
    // printf("who: %d\n", who);
    printf("argc: %d\n", root->argc);
    // printf("cmd: %s\n", root->argv[0]);
    // if (root->argv = NULL)
    // {
    //     printf("argv: %d\n", *(root->argv));
    // }
    // else
    // {
    for (int i = 0; (root->argv[i]) != NULL; i++)
    {
        printf("argv %d: %s\n", i, root->argv[i]);
    }
    // }

    printf("infile: %s\n", root->infile);
    printf("outfile: %s\n", root->outfile);
    printf("append: %d\n", root->append);
    printf("background: %d\n", root->backgrnd);
    printf("next cmd type: %d\n", root->type);

    if (root->psubcmd)
    {
        printf("exist psubcmd %s\n", root->psubcmd->argv[0]);
    }
    if (root->pipe)
    {
        printf("exist pipe %s\n", root->pipe->argv[0]);
    }
    if (root->next)
    {
        printf("exist next %s\n", root->next->argv[0]);
    }

    print_tree(root->psubcmd);       // 0 - psubcmd
    print_tree(root->pipe);          // 1 - pipe
    print_tree(root->next);          // 2 - next

}

void 
delete_tree(tree_node *root)
{
    if (root == NULL)
        return;
    
    delete_tree(root->psubcmd);
    delete_tree(root->pipe);
    delete_tree(root->next);

    for (int i = 0; root->argv[i] != NULL; i++)
    {
        free(root->argv[i]);
    }

    free(root->argv);
    // free(root->infile);
    // free(root->outfile);
    
    free(root);
}

void
add_argv(tree_node *root, char *arg)
{
    int num = ++root->argc;
    root->argv = realloc(root->argv, (num + 1)*sizeof(char *));
    root->argv[num - 1] = arg;
    root->argv[num] = NULL;
}

int
is_op(Node *list)
{
    if ((!strcmp(list->data, ">")) || (!strcmp(list->data, ">>")) || 
        (!strcmp(list->data, "&")) || (!strcmp(list->data, "|")) ||
        (!strcmp(list->data, "\"")) || (!strcmp(list->data, "<")) ||
        (!strcmp(list->data, "(")) || (!strcmp(list->data, ")")) ||
        (!strcmp(list->data, "||")) || (!strcmp(list->data, "&&")))
        return 0;                                                       // операнд
    
    return 1;
}

tree_node *
build_tree(Node *list)
{
    Node *p = list;
    tree_node *root = init_tree();

    int tree_finished = 0;

    for (; p != NULL; p = p->next)
    {
        if (!strcmp(p->data, ">"))
        {
            if(root->outfile != NULL)
            {
                printf("my_shell: error two output files\n");
                delete_tree(root);
                return NULL;
            }

            root->outfile = p->next->data;
            p = p->next;
        }
        else if (!strcmp(p->data, ">>"))
        {
            if(root->outfile != NULL)
            {
                printf("my_shell: error two output files\n");
                delete_tree(root);
                return NULL;
            }

            root->outfile = p->next->data;
            root->append = 1;
            p = p->next;
        }
        else if (!strcmp(p->data, "<"))
        {
            if(root->infile != NULL)
            {
                printf("my_shell: error: two input files\n");
                delete_tree(root);
                return NULL;
            }

            root->infile = p->next->data;
            p = p->next;
        }
        else if (!strcmp(p->data, ";"))
        {
            root->type = NXT;
            root->next = build_tree(p->next);
            break;
        }
        else if (!strcmp(p->data, "&&"))
        {
            root->type = AND;
            root->next = build_tree(p->next);
            break;
        }
        else if (!strcmp(p->data, "||"))
        {
            root->type = OR;
            root->next = build_tree(p->next);
            break;
        }
        else if (!strcmp(p->data, "&"))
        {
            root->backgrnd = 1;
            root->next = build_tree(p->next);
            break;
        }
        else if (!strcmp(p->data, "|"))
        {
            root->pipe = build_tree(p->next);
            break;
        }
        else if (!strcmp(p->data, "("))             // скобки не работают!!
        {
            if (root->argc != 0)
            {
                printf("my_shell: nexpected argument before '('\n");
                delete_tree(root);
                // return NULL;
            }
            // root->psubcmd = build_tree(p->next);
            // root->next = init_tree();
            // printf("%s\n", p->data);
            root->psubcmd = build_tree(p->next);
            // root->next = build_tree(get_cls_brckt(p));
            // root->next = build_tree(get_cls_brckt(p));

        }
        else if (!strcmp(p->data, ")"))             // проблемы с этими скобками
        {
            if (!tree_finished)
            {
                // printf("Invalid input\n");
                delete_tree(root);
                return NULL;
            }
            else
            {
                return root;
            }
        }
        else
        {
            char *arg = calloc(1, strlen(p->data) + 1);
            strcpy(arg, p->data);
            add_argv(root, arg);
        }
        tree_finished = 1;
    }

    if(!tree_finished)
    {
        delete_tree(root);
        return NULL;
    }
    else
    {
        return root;
    }
    
}

int
set_inp_outp(tree_node *root)
{
    int fd;
    if (root->infile != NULL)
    {
        if((fd = open(root->infile, O_RDONLY)) == -1)
        {
            // fprintf(stderr, "Error in opening file: %s\n", strerror(errno));
            perror("my_shell");
            return 1;
        }
        if (dup2(fd, 0) == -1)
        {
            // fprintf(stderr, "Error in dup2: %s\n", strerror(errno));
            perror("my_shell");
            return 1;
        }
    }

    if (root->outfile != NULL)
    {
        if (root->append)
        {
            if((fd = open(root->outfile, O_WRONLY | O_CREAT | O_APPEND, 0666)) == -1)
            {
                // fprintf(stderr, "Error in opening file: %s\n", strerror(errno));
                perror("my_shell");
                return 1;
            }
        }
        else
        {
            if((fd = open(root->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0666)) == -1)
            {
                // fprintf(stderr, "Error in opening file: %s\n", strerror(errno));
                perror("my_shell");
                return 1;
            }
        }
        
        if (dup2(fd, 1) == -1)
        {
            // fprintf(stderr, "Error in dup2: %s\n", strerror(errno));
            perror("my_shell");
            return 1;
        }
    }
    return 0;
}

tree_node *
rewind_pipe_subshell(tree_node *root)
{
    if ((root->pipe == NULL) && (root->psubcmd == NULL))
        return root;
    
    if(root->pipe != NULL)
        return rewind_pipe_subshell(root->pipe);

    if(root->psubcmd != NULL)
        return rewind_pipe_subshell(root->psubcmd);
}

// запускает команды или рекурсивно вызывает сабшелл
int 
run_shell_or_subshell(tree_node *root) 
{
    int returned_value = 0;

    if (root->argv[0] == NULL) 
    {
        returned_value = tree_handler(root->psubcmd);
    } 
    else 
    {
        // if (root->backgrnd)
        // {
        //     printf("finished: %d\n", getpid());
        //     fflush(stdout);
        // }

        if (execvp(root->argv[0], root->argv) == -1)
        {
            //	будет выдавать ошибки на cd и false
            // printf("wrong command\n");
            // printf("exec error\n");
            printf("my_shell: unknown command\n");
            return -1;
        }
        
    }
    return returned_value;
}

// в цикле обрабатывает пайп от начала до конца
int 
pipe_handler(tree_node *root) 
{    
    pid_t pid;
    int status;
    int fd[2];

    while (root != NULL) {
        pipe(fd);
        pid = fork();

        if (pid == 0) {
            int err = 0;
            signal(SIGINT, SIG_DFL);

            err = set_inp_outp(root);
            // set_inp_outp(root);

            if (err)
                return -1;

            if (root->pipe != NULL) {
                dup2(fd[1], 1);
            }
            close(fd[1]);
            close(fd[0]);

            if (run_shell_or_subshell(root) == -1) {
                // printf("error in line %d, file tree_handler.c\n", __LINE__);
                return -1;
            }

            exit(0);
        }
        dup2(fd[0], 0);
        close(fd[1]);
        close(fd[0]);

        root = root->pipe;
    }

    while (wait(&status) > 0);
    return status;
}

int counter = 0;

int 
tree_handler(tree_node *root) 
{
    // int dckgrnd_flag = 0;
    if (root == NULL)
        return 0;

    int status = 0;

    if ((root->argv[0] != NULL) && (strcmp(root->argv[0], "cd") == 0)) // обработка cd
    {
        chdir(root->argv[1]);
        status = tree_handler(root->psubcmd);

        if (root->next != NULL)
        {
            if ((root->type == NXT) || ((root->type == AND) && (status == 0)) ||
                ((root->type == OR) && (status != 0)))
                status = tree_handler(root->next);
        }
            
        return status;
    }

    // --cmnds;
    // pipe
    if (root->pipe != NULL) 
    {
        
        int in = dup(0); //  чудо - штучка
        status = pipe_handler(root);
        dup2(in, 0);
        root = rewind_pipe_subshell(root);

        if (root == NULL)
            return status;

        if (root->next != NULL)
            if ((root->type == NXT) ||
                ((root->type == AND) && (status == 0)) ||
                ((root->type == OR) && (status != 0)))
                    status = tree_handler(root->next);

        // printf("status: %d\n", status);
        // if (status != 0)
        // {
        //     printf("my_shell: incorrect command\n");
        // }
        return status;
    }

    // son
    // --cmnds;
    if (fork() == 0) {
        
        int err = 0;
        err = set_inp_outp(root);
        // set_inp_outp(root);

        if (err)
            return -1;

        // фон
        if (root->backgrnd == 1) 
        {
            pid_t pid;
            signal(SIGINT, SIG_IGN);
            
            // printf("pid: %d\n", getpid());
            // status = run_shell_or_subshell(root);

            if ((pid = fork()) == 0) // внук
            {
                if ((pid = fork()) == 0) // правнук
                {
                    printf("[started]: %d\n", getpid());
                    fflush(stdout);
                    status = run_shell_or_subshell(root);
                    exit(status);
                }
                else
                {
                    struct msgbuf
                    {
                    	long mtype;
                    	pid_t mes;
                    } Message;

                    // printf("flag: %d\n", bckrd_flg); 
                    fflush(stdout);

                    pid = wait(NULL);
                    key_t key = ftok ("/Users/nadezdabelousova/C/Programming/Studying/S_05.12.2023", 0);
	                int msgid = msgget(key, 0666);
                    // printf("total background amount: %d\n", *cmd_link);
                    // *cmd_link = (*cmd_link) - 1;
                    // printf("counter: %d\n", counter);
                    // ++counter;
                    // printf("\n");

                    Message.mtype = 1;
                    Message.mes = pid;

                    // printf("pid waited: %d\n", Message.mes);
                    // int err = 
                    msgsnd(msgid, (&Message), sizeof(pid_t), 0);
                    // if (err == -1)
                    //     printf("error\n");
                    

                    // printf("[finished]: %d\n", pid); // вывод pid-ов, завершившихся в фоне
                    // bckrd_pid = pid;
                    // bckrd_flg = 1;
                    // printf("[finished]: %d\n", pid); 
                    // fflush(stdout);
                    // fflush(stdout);
                    exit(0);
                }                
            } 
            else
            {
		        // фоновый процесс берет на себя 1
                kill(getpid(), SIGKILL);
            }

            // не фон
        } 
        else 
        {
            status = run_shell_or_subshell(root);
            if (status != 0)
                exit(1);
            else
                exit(0);
            // return status;
        }

      
    } 
    else //father
    {
        // if (!(root->backgrnd))
        // {
            // waitpid(-1, &status, WNOHANG);
            wait(NULL);
            // printf("exit status: %d\n", WEXITSTATUS(status));
            // printf("exit status: %d\n", WEXITSTATUS(status));
            // if (WIFEXITED(status))
            // {
                status = WEXITSTATUS(status);
                // printf("status: %d\n", status);

                if (root->next != NULL)
                {
                    if ((root->type == NXT) ||
                        ((root->type == AND) && (status == 0)) ||
                        ((root->type == OR) && (status != 0)))
                            status = tree_handler(root->next);
                }
                // printf("status: %d\n", status);
                // if (status == 1 || status == -1)
                //     printf("my_shell: incorrect command\n");
                return status;
            // }
            // else
            // {
            //     printf("aboba\n");
            //     return 1;
            // }
        // }
        // else
        // {
        //     wait(NULL);
        // }
    }
}

int
how_much_cmd(tree_node *root)
{
    
    int sum = 0;

    if ((root->pipe == NULL) && (root->next == NULL))
        return 1;
    else if (root->pipe != NULL)
    {
        sum = 1 + how_much_cmd(root->pipe);
    }
    else if (root->next != NULL)
    {
        sum = 1 + how_much_cmd(root->next);
    }

    return sum;
}