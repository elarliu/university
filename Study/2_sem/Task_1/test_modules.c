#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include "info_list.h"
#include "parser.h"

int
main(int argc, char *argv[])
{
    Node *cmd_list = NULL;
    cmd_list = get_list();
    print_list(cmd_list);

    detele_list(&cmd_list);
}