#include <stdio.h>
#include <string.h>

/* эхо аргументов командной строки; версия 3 */
int
main(int argc, char* argv[]) 
{
    int e_flag = 0, n_flag = 0;

    if (argc == 1)
    {
        printf("\n");
        return 0;
    }
    
    if (!strcmp(argv[1], "-n"))
    {
        n_flag = 1;
    }

    if (!strcmp(argv[1], "-e"))
    {
        e_flag = 1;
    }

    if (argv[2] && !strcmp(argv[2], "-n"))
    {
        n_flag = 1;
    }

    if (argv[2] && !strcmp(argv[2], "-e"))
    {
        e_flag = 1;
    }

    // printf("flags: n %d e %d\n", n_flag, e_flag);

    for (int i = e_flag + n_flag; i < argc - 1; i++)
    {
        if (!e_flag)
            printf(argv[i + 2] ? "%s " : "%s", argv[i + 1]);
        else
        {   
            // printf("current char: %c\n", *(argv[i + 1]));
            // printf("length: %ld\n", strlen(argv[i + 1]));
            // str = *argv[i + 1]
            int len = strlen(argv[i + 1]);
            for (int j = 0; j < len; ++j, ++argv[i + 1])
            {
                // printf("len: %ld\n",strlen(argv[i + 1]));
                if (*argv[i+1] == '\\')
                {
                    if (*(argv[i+1] + 1) && *(argv[i+1] + 1) == 't')
                    {
                        printf("%c",'\t');
                        ++j;
                        ++argv[i + 1];
                    }
                    else if (*(argv[i+1] + 1) && *(argv[i+1] + 1) == 'n')
                    {
                        printf("%c",'\n');
                        ++j;
                        ++argv[i + 1];
                    }
                    else if (*(argv[i+1] + 1) && *(argv[i+1] + 1) == 'v')
                    {
                        printf("%c",'\v');
                        ++j;
                        ++argv[i + 1];
                    }
                    else if (*(argv[i+1] + 1) && *(argv[i+1] + 1) == 'b')
                    {
                        printf("%c",'\b');
                        ++j;
                        ++argv[i + 1];
                    }
                    else if (*(argv[i+1] + 1) && *(argv[i+1] + 1) == 'r')
                    {
                        printf("%c",'\r');
                        ++j;
                        ++argv[i + 1];
                    }
                    else if (*(argv[i+1] + 1) && *(argv[i+1] + 1) == 'a')
                    {
                        printf("%c",'\a');
                        ++j;
                        ++argv[i + 1];
                    }
                    else if (*(argv[i+1] + 1) && *(argv[i+1] + 1) == 'f')
                    {
                        printf("%c",'\f');
                        ++j;
                        ++argv[i + 1];
                    }
                    else
                    {
                        printf("%c",'\\');
                    }
                    // printf("j: %d\n",j);
                }
                else
                    printf("%c",(*argv[i+1]));
                
            }
            if(argv[i + 2])
                    printf(" ");
            
        }
        
    }
    
    if (!n_flag)
    {
        printf("\n");
    }
    
}