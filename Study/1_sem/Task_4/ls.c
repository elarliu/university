#include <stdio.h>
#include <dirent.h>
#include <errno.h>
#include <string.h>
#include <limits.h>
#include <sys/stat.h>                                                  
#include <sys/types.h>                                                 
#include <unistd.h>       
#include <stdlib.h>
#include <pwd.h>
#include <grp.h>
#include <fcntl.h>

enum
{
    INCORRECT_FLAG = 1,
    OPEN_DIR_ERROR = 2,
    CLOSE_DIR_ERROR = 3,
    LSTAT_ERROR = 4,
    ERR_FILE_TYPE = 5,
    ERR_PSWD = 6
};

typedef char * Data;
typedef struct Node Node;

struct Node 
{
    Data data;
    Node *next;
};

// void push(Node **list, Data x);

int is_empty(Node * list) 
{
    return list == NULL;
}

Data pop(Node **plist)
{
    Node *p = *plist;
    Data res = p->data;
    *plist = p->next;

    free(p);
    return res;
}   


void push_end(Node **plist, Data d)
{
    Node *p = calloc(1,sizeof(Node));
    // Node *q = calloc(1,sizeof(Node));
    Node *q = *plist;
    // Node *q = calloc(1,sizeof(Node));
    p->data = strdup(d);
	p->next = NULL;
    
    
    if (*plist == NULL)
    {
        *plist = p;
    }
    else
    {
        while ((q->next)!=NULL)
        {
            q = q->next;
        }
        (q->next) = p;
    }
    
}

void print(Node *list)
{
    printf("List: ");
    
    for(Node *p = list ; p!=NULL ; p = p->next)
    {
        printf("%s ",p->data);
     
    }
    putchar('\n');
}

void detele_list(Node **plist)
{
    while (!is_empty(*plist))
    {
        free(pop(plist));
        // pop(plist);
        
    }   
}

char *
get_type(mode_t mode)
{
    if (S_ISFIFO(mode))
        return "FIFO";

    if (S_ISCHR(mode))
        return "Character special";

    if (S_ISDIR(mode))
        return "Directory";
    
    if (S_ISBLK(mode))
        return "Block special";
    
    if (S_ISREG(mode))
        return "Regular";
    
    if (S_ISLNK(mode))
        return "Link";
    
    if (S_ISSOCK(mode))
        return "Socket";

    fprintf(stderr, "Can't define the type\n");
    return (char *) ERR_FILE_TYPE;
    

}   

void 
get_permissions(mode_t mode)
{
    if (mode & S_IRUSR)
        printf("r");
    else
        printf("-");

    if (mode & S_IWUSR)
        printf("w");
    else
        printf("-");

    if (mode & S_IXUSR)
        printf("x");
    else
        printf("-");


    if (mode & S_IRGRP)
        printf("r");
    else
        printf("-");

    if (mode & S_IWGRP)
        printf("w");
    else
        printf("-");

    if (mode & S_IXGRP)
        printf("x");
    else
        printf("-");


    if (mode & S_IROTH)
        printf("r");
    else
        printf("-");

    if (mode & S_IWOTH)
        printf("w");
    else
        printf("-");

    if (mode & S_IXOTH)
        printf("x");
    else
        printf("-");

    printf("   ");
}

int 
see_dir_rec(const char *directory, int l_flag, int g_flag, int R_flag)
{
    
    DIR *d = opendir(directory);

    if (d == NULL) 
    {
        fprintf(stderr, "Error: %s\n", strerror(errno));
        return OPEN_DIR_ERROR;
    }

    struct dirent *dd;
    char path[PATH_MAX];

    Node *list = NULL;
    Node *looking;

    while ((dd = readdir(d))) //может быть ошибка
    {   
        char *CurrentName = dd->d_name;

        if (!strcmp(CurrentName, ".") || !strcmp(CurrentName, "..")) //strncmp лучше
            continue;   
        
        int len = snprintf(path,sizeof(path),"%s/%s",directory,CurrentName); //ошибка может быть

        if (len + 1 > sizeof(path))
            continue;
        
        struct stat st;
        
        // printf("Curr name %s\n",path);

        if(lstat(path, &st) < 0)
        {
            fprintf(stderr, "Stat error: %s\n", strerror(errno));                 
            return LSTAT_ERROR; 
        }

        push_end(&list,path);
        
        
        // int access = st.st_mode & S_IRWXO + st.st_mode & S_IRWXG + st.st_mode & S_IRWXU;
        if (l_flag || g_flag)
        {
            
            printf("Type: %-11s Access: ", get_type(st.st_mode));

            get_permissions(st.st_mode);

            printf("Size: %-7ld ", st.st_size);

            if (l_flag && g_flag)
            {
                printf("UID: %-19s", getpwuid(st.st_uid)->pw_name);
                printf("GUI: %-19s", getgrgid(st.st_gid)->gr_name);
            }
            else if (l_flag)
                printf("UID: %-19s ", getpwuid(st.st_uid)->pw_name);
            else
                printf("GUI: %-19s ", getgrgid(st.st_gid)->gr_name);
            
            if (S_ISLNK(st.st_mode))
            {

                char *unlinked = calloc(PATH_MAX, sizeof(char));

                readlink(path, unlinked, PATH_MAX);
                printf("%-20s -> ",path + 2);
                printf("%-20s",unlinked);
                free(unlinked);
            }
            else
                printf("%-20s",path + 2);
        }
        else 
            printf("%-20s",path + 2);



        printf("\n");

        if (R_flag)
        {
            if (S_ISDIR(st.st_mode))
            {
            printf("\n");
            closedir(d);    //не проверили

            see_dir_rec(path, l_flag, g_flag, R_flag);
            
            d = opendir(directory);
            looking = list;
            while ((dd = readdir(d)) && (looking != NULL) &&(strcmp(looking->data, dd->d_name) != 0))
            {
                looking = looking->next;
            }
            dd = readdir(d);
            printf("\n");
            }
        }
        
    }

    if (closedir(d)<0)
    {
        fprintf(stderr, "Error: %s\n", strerror(errno));
        return CLOSE_DIR_ERROR;
    }

    detele_list(&list);
}

int
main(int argc, char *argv[])
{
    
    int fd = open("access.txt", O_CREAT | O_TRUNC, 0666);
    close(fd);
    
    int R_flag = 0, l_flag = 0, g_flag = 0;
    
    for (int i = 1; i < argc; i++)
    {
        // printf("argv %s\n",argv[i]);
        if (!strcmp(argv[i], "-R"))
            R_flag = 1;
        else if (!strcmp(argv[i], "-l"))
            l_flag = 1;
        else if (!strcmp(argv[i], "-g"))
            g_flag = 2;
        else
        {
            fprintf(stderr, "Incorrect flag\n");
            return INCORRECT_FLAG;
        }
    }
    
        // printf("flags: l %d g %d R %d\n", l_flag, g_flag, R_flag);    
    see_dir_rec(".", l_flag, g_flag, R_flag);


    
}