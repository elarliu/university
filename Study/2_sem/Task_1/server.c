#include <sys/socket.h>
#include <sys/types.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <netinet/ip.h>
#include <poll.h>
#include "parser.h"
#include "info_list.h"

#define MAX_QUEUE 4
#define MEM_INC_SIZE 8
#define BUF_SIZE 256

void
write_name(int fd, char name[])
{
    // printf("%s",name);
    for (int i = 0; name[i] != '#'; i++)
    {
        // printf("pops");
        // fflush(stdout);
        // printf("%c", name[i]);
        // fflush(stdout);
        write(fd, &name[i], 1);
    }
    
}

int
check_quote(Info_Node * client_list)
{
    Info_Node * p = client_list;
    while (p != NULL)
    {
        if((p->msg) != 0)
            return 1;
        p = p->next;
    }
    
    return 0;
}

int
set_quote(Info_Node * client_list)
{
    Info_Node * p = client_list;
    while (p != NULL)
    {
        p->msg = 3;
        write(p->socket, "The message quota has been restored\n", 
            strlen("The message quota has been restored\n"));
        p = p->next;
    }
    return 0;
}

int
print_users(char *cmd, Info_Node *client_list, int main_socket)
{
    // printf("Got string: %s\n", cmd);
    if(!strcmp(cmd, "\\users\n"))
    {
        // printf("Users:\n");
        client_print_list(client_list);
        // fflush(stdout);
        // Info_Node *p = client_list;

        // while (p != NULL)
        // {
        //     write_name(1, p->data);
        //     printf("\n");
        //     fflush(stdout);
        //     p = p->next;
        // }
        
        return 1;
    }

    if((!strcmp(cmd, "\\quit\n")) || (!strcmp(cmd, "\\q\n")))
    {
        // printf("boba\n");
        Info_Node *p = client_list;
        while (p != NULL)
        {
            write(p->socket, "server-borsh was shut down\n", strlen("server-borsh was shut down\n"));
            close(p->socket);
            p = p->next;
        }
        // printf("main socket:%d\n", main_socket);
        // close(main_socket);
        // shutdown(main_socket, 2);
        // client_detele_list(&client_list);
        return 0;
    }
}

int main(int argc, char * argv[])
{
    int main_socket, port, clients, max_clients, events, temp_socket, i;
    ssize_t n_read;
    int flag = 1;
    char buf[BUF_SIZE], cmd[BUF_SIZE];
    memset(cmd, '\0', BUF_SIZE);
    memset(buf, '\0', BUF_SIZE);
    struct sockaddr_in adr;
    struct pollfd * fds, * temp_fds; 

    Info_Node *client_list = NULL; 

    if(argc < 2)
    {
        fprintf(stderr,"Необходимо указать номер порта в параметрах\n");
        return 1;
    }

    port = atoi(argv[1]);
     
    adr.sin_family = AF_INET;
    adr.sin_port = htons(port);
    adr.sin_addr.s_addr = INADDR_ANY;

    errno = 0;
    main_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (main_socket == -1)
    {
        fprintf(stderr, "%s (%d): Сокет не был создан: %s\n",
                __FILE__, __LINE__ - 2,  strerror(errno));  
        exit(1);
    }

    errno = 0;
    if(bind(main_socket, (struct sockaddr *) &adr, sizeof(adr)) == -1)
    {
        fprintf(stderr, "%s (%d): Не удалось привязать к адресу: %s\n",
                __FILE__, __LINE__ - 2,  strerror(errno));  
        exit(1);
    }
    
    errno = 0;
    if(listen(main_socket, MAX_QUEUE) == -1)
    {
        fprintf(stderr, "%s (%d): Не удалось установить сокет в режим TCP: %s\n",
                __FILE__, __LINE__ - 2,  strerror(errno));  
        exit(1);
    }

    max_clients = MEM_INC_SIZE;
    clients = 0;

    errno =  0;
    fds = malloc(sizeof(struct pollfd) * (max_clients + 1));
    if(fds == NULL)
    {
        fprintf(stderr, "%s (%d): Структура не была создана: %s\n",
                __FILE__, __LINE__ - 2,  strerror(errno));  
        exit(1);
    }

    fds[0].fd = main_socket;
    fds[0].events = POLLIN | POLLERR | POLLPRI | POLLOUT;
    fds[0].revents = 0;

    // printf("main socket:%d\n", main_socket);

    for(;;)
    {
        events = poll(fds, clients + 1, 100);
        if(events == -1){
            fprintf(stderr, "%s (%d): Проблемы с poll: %s\n",
                    __FILE__, __LINE__ - 2,  strerror(errno));  
            exit(1);
        }

        // if(events == 0)
        // {
        //     continue;
        // }

        memset(buf, '\0', BUF_SIZE);
        memset(cmd, '\0', BUF_SIZE);
        n_read = read(0, cmd, BUF_SIZE);
        // printf("after\n");
        // fflush(stdout);
        if(cmd[0] != '\n')
            flag = print_users(cmd, client_list, main_socket);
        // printf("flag: %d\n", flag);
        if(!flag)
            break;
        
        // printf("Events = %d\n",events);

        if(fds[0].revents)
        {
            temp_socket = accept(main_socket, NULL, NULL);

            if(temp_socket == -1)
            {
                fprintf(stderr, "%s (%d): Failed accept: %s\n",
                        __FILE__, __LINE__ - 2,  strerror(errno));  
                exit(1);
            }

            clients++;

            write(temp_socket,"server-borsh: Please, enter your name and type #\n", 
                                strlen("server-borsh: Please, enter your name and type #\n"));
            memset(buf, 0, BUF_SIZE);
            read(temp_socket, buf, BUF_SIZE);

            // printf("name: %s\n", name);
            // printf("Client <%s> has connected\n", buf);

            printf("Client <");
            fflush(stdout);
            write_name(1, buf);
            printf("> has connected\n");
            fflush(stdout);

            
            if (clients >= max_clients)
            {
                max_clients += MEM_INC_SIZE;
                temp_fds = fds;
                fds = realloc(fds, sizeof(struct pollfd) * (max_clients + 1));
                if(fds == NULL){
                    fprintf(stderr, "%s (%d): Ошибка realloc: %s\n",
                            __FILE__, __LINE__ - 2,  strerror(errno));  
                    free(temp_fds);
                    exit(1);
                }
            }
            // printf("Socket created: %d\n", temp_socket);

            client_push_end(&client_list, buf, clients, temp_socket);
            fds[clients].fd = temp_socket;
            fds[clients].events = POLLIN | POLLERR | POLLPRI | POLLHUP;
            fds[clients].revents = 0;

            // client_print_list(client_list);
            //shutdown(temp_socket, SHUT_WR);
            fds[0].revents = 0;
        }

        for(i = 1; i <= clients; i++){
            if(fds[i].revents)
            {
                // printf("aboba\n");
                char *name = client_get_name(client_list, i);
                // printf("Name: %s", name);
                n_read = read(fds[i].fd, buf, BUF_SIZE);

                if(n_read == 0)
                {
                    // printf("Client <%s> has disconnested\n", name);
                    
                    printf("Client <");
                    fflush(stdout);
                    write_name(1, name);
                    printf("> has disconnected\n");
                    fflush(stdout);

                    for(int j = 1; j <= clients; ++j)
                    {
                        if (i != j)
                        {
                            write(fds[j].fd, "Client <", strlen("Client <"));
                            write_name(fds[j].fd, name);
                            write(fds[j].fd, "> has disconnected", strlen("> has disconnected"));
                        }
                    }

                    close(fds[i].fd);
                    fds[i].fd = -1;
                    client_decrease_num(client_get_node_by_num(client_list, i));
                    free(client_pop_by_num(&client_list, i));
                    // client_print_list(client_list);
                    for (int k = i; k < clients; ++k)
                    {
                        fds[k].fd = fds[k + 1].fd;
                    }
                    fds[clients].fd = -1;
                    --clients;
                    
                }

                if(n_read == -1)
                {
                    fprintf(stderr, "%s (%d): Ошибка при чтении из сокета: %s\n",
                            __FILE__, __LINE__ - 2,  strerror(errno));
                    close(fds[i].fd);
                    fds[i].fd = -1;
                }

                if(n_read > 0)
                {
                    if (buf[0] == '\\' && buf[1] == 'q' && buf[2] == ' ')
                    {

                        printf("Client <");
                        fflush(stdout);
                        write_name(1, name);
                        printf("> has disconnected with message: ");
                        fflush(stdout);
                        write(1, buf + 3, strlen(buf + 3));

                        for(int j = 1; j <= clients; ++j)
                        {
                            if (i != j)
                            {
                                write(fds[j].fd, "Client <", strlen("Client <"));
                                write_name(fds[j].fd, name);
                                write(fds[j].fd, "> has disconnected with message: ", strlen("> has disconnected with message: "));
                                write(fds[j].fd, buf + 3, strlen(buf + 3));
                            }
                        }

                        close(fds[i].fd);
                        client_decrease_num(client_get_node_by_num(client_list, i));
                        free(client_pop_by_num(&client_list, i));
                        // client_print_list(client_list);
                        fds[i].fd = -1;
                        for (int k = i; k < clients; ++k)
                        {
                            fds[k].fd = fds[k + 1].fd;
                        }
                        fds[clients].fd = -1;
                        --clients;
                        
                    } 
                    else if (buf[0] == '\\' && buf[1] == 'q' && buf[2] == '#')
                    {
                        printf("Client <");
                        fflush(stdout);
                        write_name(1, name);
                        printf("> has disconnected");
                        fflush(stdout);
                        write(1, buf + 3, strlen(buf + 3));

                        for(int j = 1; j <= clients; ++j)
                        {
                            if (i != j)
                            {
                                write(fds[j].fd, "Client <", strlen("Client <"));
                                write_name(fds[j].fd, name);
                                write(fds[j].fd, "> has disconnected\n", strlen("> has disconnected\n"));
                            }
                        }

                        // for (int k = 1; k <= clients; ++k)
                        // {
                        //     printf("fds: %d\n", fds[k].fd);
                        // }
                        
                        close(fds[i].fd);

                        // client_print_list(client_list);
                        client_decrease_num(client_get_node_by_num(client_list, i));
                        free(client_pop_by_num(&client_list, i));
                        
                        fds[i].fd = -1;

                        for (int k = i; k < clients; ++k)
                        {
                            fds[k].fd = fds[k + 1].fd;
                        }
                        fds[clients].fd = -1;
                        --clients;

                    }
                    else if (buf[0] == '\\' && buf[1] == 'u' && buf[2] == 's' && 
                             buf[3] == 'e' && buf[4] == 'r' && buf[5] == 's' && buf[6] == '#')
                    {
                        // printf("here\n");
                        Info_Node *p = client_list;
                        write(fds[i].fd, "Users:\n", strlen("Users:\n"));
                        while (p != NULL)
                        {
                            // if (p->num != i)
                            write_name(fds[i].fd, p->data);
                            write(fds[i].fd, "\n", 1);
                            p = p->next;
                        }
                        
                        
                    }
                    else
                    {
                        // printf("<%s>: %s\n", name, buf);
                        
                        if(((client_get_node_by_num_2(client_list, i))->msg) == 0)
                        {
                            write(1, "<", strlen("<"));
                            write_name(1, name);
                            write(1, ">: the message quota has been exceeded\n", 
                                         strlen(">: the message quota has been exceeded\n"));
                            // printf("aboba\n");  
                            write(fds[i].fd, "The message quota has been exceeded\n", 
                                             strlen("The message quota has been exceeded\n"));
                        } 
                        else
                        {
                            write(1, "<", strlen("<"));
                            write_name(1, name);
                            write(1, ">: ", strlen(">: "));
                            write(1, buf, strlen(buf));

                            for(int j = 1; j <= clients; ++j)
                            {
                                if (i != j)
                                {
                                    write(fds[j].fd, "<", strlen("<"));
                                    write_name(fds[j].fd, name);
                                    write(fds[j].fd, ">: ", strlen(">: "));
                                    write(fds[j].fd, buf, strlen(buf));
                                }
                            }
                            --((client_get_node_by_num_2(client_list, i))->msg);
                        }
                        // printf("%d quoute: %d\n", i, client_get_node_by_num_2(client_list, i)->msg);

                        // printf("quotes flag: %d\n", check_quote(client_list));
                        if(!(check_quote(client_list)))
                        {
                            set_quote(client_list);
                        }
                        
                    }

                }
       
            }
            fds[i].revents = 0;
        }

        memset(buf, '\0', BUF_SIZE);
        memset(cmd, '\0', BUF_SIZE);
        n_read = read(0, cmd, BUF_SIZE);
        // printf("after\n");
        // fflush(stdout);
        if(cmd[0] != '\n')
            flag = print_users(cmd, client_list, main_socket);
        // printf("flag: %d\n", flag);
        if(!flag)
            break;
        
    }

    close(main_socket);
    free(fds);
    client_detele_list(&client_list);
    
}