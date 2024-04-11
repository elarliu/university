#include <stdio.h>
#include <string.h>
#include <unistd.h>

enum
{
    ERR_ARGS = 1,
    ERR_LINK = 2,
    ERR_SYMLINK = 3
};

int
main(int argc, char *argv[])
{
    if (argc < 3)
    {
        fprintf(stderr, "Incorrect number of arguments\n");
        return ERR_ARGS;
    }

    int s = !strcmp(argv[1], "-s");

    if (s && (argv[3] == NULL))
    {
        fprintf(stderr, "Incorrect number of arguments\n");
        return ERR_ARGS;
    }

    char *source, *link_file;
    if (s)
    {
        source = argv[2];
        link_file = argv[3];
    }
    else
    {
        source = argv[1];
        link_file = argv[2];
    }

    // printf("%d\n", s );
    
    if (s)
    {
        if (symlink(source, link_file) > 0)
        {
            fprintf(stderr, "Link error\n");
            return ERR_SYMLINK;
        }
    }
    else
    {
        if (link(source, link_file) > 0)
        {
            fprintf(stderr, "Link error\n");
            return ERR_LINK;
        }
    }
    
}