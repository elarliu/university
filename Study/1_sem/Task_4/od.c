#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

#define BUF_SIZE 10

enum
{
    ERR_ARGS = 1,
    ERR_OPEN = 2,
    ERR_READ = 3
    
};

int
main(int argc, char *argv[])
{
    if (argc < 2)
    {
        fprintf(stderr, "Incorrect number of arguments\n");
        return ERR_ARGS;
    }

    int b = !strcmp(argv[1], "-b");

    if (b && (argv[2] == NULL))
    {
        fprintf(stderr, "Incorrect number of arguments\n");
        return ERR_ARGS;
    }

    int fd;
    if (b)
    {
        fd = open(argv[2], O_RDONLY);
    }
    else
    {
        fd = open(argv[1], O_RDONLY);
    }

    if (fd == -1)
    {
        fprintf(stderr,"Error in opening first file: %s", strerror(errno));
        return ERR_OPEN;
    }
    // printf("b: %d\n",b);
    char buf[BUF_SIZE];
    int err = 0;
    int len = 1;

    while ((err = read(fd, &buf, BUF_SIZE)) > 0)
    {
        printf("%06d ", len);
        for (int i = 0; i < err; i++)
        {
            if (b)
            {
                printf(" %03o ", buf[i]);
            }
            else
            {
                if (buf[i] == '\n')
                {
                    printf(" \\n ");
                }
                else if (buf[i] == '\t')
                {
                    printf(" \\t ");
                }
                else
                {
                    printf(" %c  ", buf[i]);
                }
            }

        }
        printf("\n");
        len += err;
        
    }

    if (err == -1)
    {
        fprintf(stderr,"Read from file error: %s", strerror(errno));
        return ERR_READ;
    }

}