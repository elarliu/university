#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

#define BUF_SIZE 256
enum
{
    ERR_ARGS = 1,
    ERR_OPEN = 2,
    ERR_READ = 3
};

int
main(int argc, char *argv[])
{
    if (argc < 3)
    {
        fprintf(stderr, "Incorrect number of arguments\n");
        return ERR_ARGS;
    }

    int fd1, fd2;

    fd1 = open(argv[1], O_RDONLY);
    fd2 = open(argv[2], O_RDONLY);

    char buf1[BUF_SIZE];
    char buf2[BUF_SIZE];

    if (fd1 == -1)
    {
        fprintf(stderr,"Error in opening first file: %s", strerror(errno));
        return ERR_OPEN;
    }
    
    if (fd2 == -1)
    {
        fprintf(stderr,"Error in opening second file: %s", strerror(errno));
        return ERR_OPEN;
    }
    
    int err1 = 0, err2 = 0, err = 1;
    int line = 1, ch = 1, fl = 0;
    while (((err1 = read(fd1, &buf1, BUF_SIZE)) > 0) && ((err2 = read(fd2, &buf2, BUF_SIZE)) > 0) && err)
    {
        // printf("err1: %d\n",err1);
        // printf("err2: %d\n",err2);
        for (int i = 0; (i < err1) && (i < err2); i++)
        {

            // printf("i: %d\n", i + 1);
            // printf("ch: %d\n", ch);
            // printf("Char from 1 buf: %c\n", buf1[i]);
            // printf("Char from 2 buf: %c\n", buf2[i]);
            if (buf1[i] != buf2[i])
            {
                err = 0;
                break;
            }
            ++ch;

            if (buf1[i] == '\n')
            {
                ++line;
                // ch = 1;
            }
        }

        // printf("err1: %d\n",err1);
        // printf("err2: %d\n",err2);
        // printf("err: %d\n",err);
        if (err && (err1 < err2))
        {
            printf("EOF on %s after byte %d in line %d\n", argv[1], ch - 1, line);
            break;
        }
        else if (err && (err1 > err2))
        {
            printf("EOF on %s after byte %d in line %d\n", argv[1], ch - 1, line);
            break;
        }
        else if (err && (err1 == err2) && (err1 < BUF_SIZE))
            break;
            
        if (!err)
            break;
        
        
    }

    // printf("err1: %d\n",err1);
    // printf("err2: %d\n",err2);

    if (err1 == 0 && err2 != 0)
    {
        printf("EOF on %s which is empty\n", argv[1]);
    }
    else if (err1 != 0 && err2 == 0)
    {
        printf("EOF on %s which is empty\n", argv[2]);
    }


    if (err1 == -1)
    {
        fprintf(stderr, "Read from first file error: %s\n", strerror(errno));
        return ERR_READ;
    }

    if (err2 == -1)
    {
        fprintf(stderr, "Read from second file error: %s\n", strerror(errno));
        return ERR_READ;
    }

    if (!err)
        printf("%s %s differ: line %d, char %d\n", argv[1], argv[2], line, ch);
    
}