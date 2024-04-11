#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

#define BUF_SIZE 255

int
main(void)
{
    char buf[BUF_SIZE];
    if (getcwd(buf, BUF_SIZE) == NULL) {
        fprintf(stderr, "getcwd error: %s\n", strerror(errno));
        _exit(1);
    }

    printf("%s\n",buf);
}