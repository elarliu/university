#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include "list.h"
#include "tree.h"
#include "error.h"

pid_t bckrd_pid = 0;
int bckrd_flg = 0;
int bckrd_cmd = 0;

void 
invitation(void) 
{
    char s[PATH_MAX];
    getcwd(s, PATH_MAX);
    printf("%s", "\033[01;35m");  // цвет меняется на розовый
    printf("%s", s);
    printf(" >>> ");
    printf("%s", "\033[0m");   
}

int
run_cmd(Node *list)
{
    int err = 0;
    tree_node *root = NULL;
    err = check_error(list);

    if(!print_error(err))
    {
        dollar_handler(list);
        
        // print_list(list);
        bckrd_cmd = count_word(list, "&");
        // printf("amount of background commands: %d\n", bckrd_cmd);
        root = build_tree(list);
    
        // print_tree(root);
        
        err = tree_handler(root);

        // fflush(stdout);
        // printf("err: %d\n", err);
        
        delete_tree(root);
    }
    // printf("aboba\n");
    detele_list(&list);
    return err;
}

int
main(int argc, char *argv[])
{
    struct msgbuf
    {
    	long mtype;
    	pid_t mes;
    } Message;

    pid_t msg_pid = 0;
    signal(SIGINT, SIG_IGN);
    key_t key = ftok ("/Users/nadezdabelousova/C/Programming/Studying/S_05.12.2023", 0);
    int msgid = msgget(key, 0666 | IPC_CREAT | IPC_EXCL);

    int err = 0;
    // int end_flag = 1;

    Node *list = NULL;
    int stdin_copy = dup(0);

    while (!feof(stdin))  // экстренное завершение
    {
        int stdin_copy = dup(0);
        // start: 
        invitation();
        
        list = get_list();        

        // print_list(list);
        fflush(stdout);
        fflush(stdin);
        fflush(stderr);
        close(0);
        dup2(stdin_copy, 0);

        if ((get_len(list) == 1) && ((!strcmp(list->data, "exit")) || (!strcmp(list->data, "q")))) // завершение работы shell
        {
            detele_list(&list);
            // printf("aboba\n");
            break;
        }

        err = run_cmd(list);

        // printf("err: %d\n", err);
        
        if (err == -1 || err == 1 || err == 13)
        {
            // fprintf(stderr, "my_shell: incorrect command\n");
            printf("my_shell: incorrect command\n");
        }

        for (int i = 0; i < bckrd_cmd; i++)
        {
            msgrcv(msgid, (&Message), sizeof(pid_t), 1, 0);
            msg_pid = Message.mes;
        }

        if(msg_pid > 0)
        {
            printf("last background finished: %d\n", msg_pid);
            fflush(stdout);
            msg_pid = 0;
        }
    }
    msgctl(msgid, IPC_RMID, NULL);
}


// pid последнего завершившегося в фоне