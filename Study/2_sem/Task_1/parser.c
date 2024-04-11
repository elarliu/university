#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <limits.h>
#include "parser.h"
// #define BUFF_SIZE 30

// typedef char * Data;
// typedef struct Node Node;

// struct Node 
// {
//     Data data;
//     Node *next;
// };

// enum
// {
//     ORDINARY_WORK = 0,
//     END_OF_LINE = 1,
//     END_OF_FILE = 2
// };

Data 
pop(Node **plist)
{
    Node *p = *plist;
    Data res = p->data;
    *plist = p->next;

    free(p);
    return res;
}   

void
print_size(Node *list)
{
    int size = 0;

    for(Node *p = list ; p!=NULL ; p = p->next)
    {
        ++size;
    }

    printf("List length: %d\n",size);
}

void 
print_list(Node *list)
{
    printf("List:\n");

    for(Node *p = list ; p!=NULL ; p = p->next)
    {
        printf("%s ",p->data);
        printf("\n");
    }

}

int 
is_empty(Node * list) 
{
    return list == NULL;
}

void push_frwrd(Node **plist, Data d)
{
    Node *p = calloc(1,sizeof(Node));
    // char * const ptr = d;
    if (d != NULL)
    {
        p->data = strdup(d);
        p->next = *plist;

        *plist = p;
    }
}

void 
push_end(Node **plist, Data d)
{
    Node *p = calloc(1,sizeof(Node));
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

int
get_len(Node *list)
{
    int size = 0;

    for(Node *p = list ; p!=NULL ; p = p->next)
    {
        ++size;
    }
    return size;
}

void 
detele_list(Node **plist)
{
    while (!is_empty(*plist))
    {
        free(pop(plist));
    }
}

Node *
get_node(Node *list, int index)
{
    int i = 0;
    for(Node *p = list ; (i <= index) && p!=NULL ; p = p->next, ++i)
    {
        if (i == index)
            return p;
        
    }
    return NULL;
}

void 
s_sort(Node *list, int n)
{
    if (list == NULL || n == 1)
        return;

    int min_index,i,j;
    char *s_exch = NULL;
    
    Data data_exch = NULL;

    i = 0;
	
	while (i < n - 1) {
		min_index = i;
		j = i+1;
        // if (arr[i].inode == -1)
        //     printf("popaa");
		while (j<n) 
        {
            // printf("j: %d\n",j);
            // printf("min_index: %d\n",min_index);
            //printf("%s\n",get_node(list,j)->data);
            //printf("%s\n",get_node(list,min_index)->data);
            if (strcmp(get_node(list,j)->data, get_node(list,min_index)->data) < 0)
            {
				min_index = j;
            }
			++j;
		}
        if (strcmp(get_node(list,i)->data, get_node(list,min_index)->data) > 0)
        {
            data_exch = get_node(list,min_index)->data;
            get_node(list,min_index)->data = get_node(list,i)->data;
            get_node(list,i)->data = data_exch;
        }
        
		++i;
	}

}

int 
count_word(Node *list, char *word)
{
    Node *p = list;
    int res = 0;
    while (p != NULL)
    {
        if (!strcmp(p->data, word))
            ++res;
        p = p->next;
    }
    return res;
    // printf("%d\n",res);
}

void 
most_recent_word(Node *list)
{
    int count = 0, max = 0;
    Node *most_recent_node;
    Node *p = list;

    while (p != NULL)
    {
        if ((count = count_word(list, p->data)) > max)
        {
            max = count;
            most_recent_node = p;
        }
        // printf("Times: %d\n",count);
        // printf("Word: %s\n",p->data);
        p = p->next;
    }
    
    printf("Most recent word: %s\n", most_recent_node->data);
    printf("Amount: %d\n", max);

}

void 
replase(Node *list)
{
    Node *p = list;

    char home[] = "/Users/nadezdabelousova";
    char shell[] = "/Users/nadezdabelousova/C/Programming/Studying/2023_belousova215/Task_5";
    char who[] = "nadezdabelousova";
    // printf("user: %s\n", who);
    // char euid[] =  geteuid();

    while (p != NULL)
    {
        // if ((!strcmp(p->data, "$")) && (p->next != NULL))
        // {
        //     // printf("%s\n", p->data);
        if (!strcmp(p->data, "HOME"))
        {
            free(p->data);
            p->data = calloc(1, sizeof(home));
            memmove(p->data, home, strlen(home));
        }
        else if (!strcmp(p->data, "SHELL"))
        {
            free(p->data);
            p->data = calloc(1, sizeof(shell));
            memmove(p->data, shell, strlen(shell));
        }
        else if (!strcmp(p->data, "USER"))
        {
            free(p->data);
            p->data = calloc(1, sizeof(who));
            memmove(p->data, who, strlen(who));
        }
            
        // }
        // else
        p = p->next;
        // printf("Times: %d\n",count);
        // printf("Word: %s\n",p->data);
    }
    
    // free(who);

}

Node *
get_cls_brckt(Node *list)
{
    Node *p = list;
    while ((p != NULL) && (strcmp(p->data, ")")))
    {
        p = p->next;
    }
    return p->next;
    
}

// modification
// Node *
// get_list(void)
// {
//     Node *list = NULL;
    
//     char s_line = 0;
//     char s_eof = 1;

//     char *s = NULL, *p = NULL;
//     char *word = NULL;
//     char c = 32;
//     // while (fscanf(stdin, "%s", s) != EOF)
//     // {
//     //     push_end(&list,s);
//     // }
//     int i = 0;
//     // int j = 0;
//     int i_word_start = 0;
//     long long l = 0;
//     int i_start = 0, i_end = 0;  
        
//     int flag = 0;
//     s = calloc(BUFF_SIZE, sizeof(char));
//     // fflush(stdin);
//     // fscanf(stdin, "%s", s);
//     // l = fread(s, sizeof(char), BUFF_SIZE, stdin);

//     while ((c = getc(stdin)) != EOF)
//     {
//         s[l] = c;
//         if (s[l] == '\n')
//         {
//             ++l;
//             break;
//         }
//         ++l;
//     }
//     // s[l] = '\0';
//     // s[l + 1] = '\0';
//     // ++l;
//     // printf("%s", s);
//     // printf("len: %lld\n", l);
//     // l += strlen(s);
//     // s[l] = '\n';
//     // s[l+1] = '\0';
//     word = realloc(word, l);
    
//     p = s;
//     // printf("i: %d l: %lld\n",i,l);
//     for (; i < l; i++)
//     {
//         c = *p;
//         // printf("%c\n", c);
//         switch (c)
//         {
//         // case '\n':
//         case ' ':
//         case '\t':
//         case '\n':
//             // printf("start: %d end: %d\n",i_start, i_end);
//             // printf("word: %s\n",word);
//             if (i_start - i_end == 0)
//             {
//                 i_start = i + 1;
//                 i_end = i + 1;
//                 i_word_start = i + 1;
//                 break;
//             }
            
//             /*
//             if ((s + 1) != NULL && (*(s + 1)==' ' || *(s + 1)=='\n' || *(s + 1)=='\t'))
//             {
//                 i_start = i + 1;
//                 i_end = i + 1;
//                 i_word_start = i + 1;
//                 break;
//             }
//             */
//             memmove(word, s + i_start, i_end - i_start);
//             word[i_end - i_start] = '\0';
//             i_start = i + 1;
//             i_end = i + 1;
//             i_word_start = i + 1;
//             push_end(&list, word);
//             break;
        
//         case '|':
//         case '&':
//         case ';':
//         case '>':
//         case '<':
//         case '(':
//         case ')':
//         // case '\"':
//             // printf("i: %d\n",i);
//             // printf("start: %d end: %d\n",i_start, i_end);
//             // printf("char: %c\n",c);
    
//             if (i_start != i_end)
//             {
//                 memmove(word, s + i_start, i_end - i_start);
//                 word[i_end - i_start] = '\0';
//                 // printf("start: %d end: %d\n",i_start, i_end);
//                 // printf("word: %s\n",word);
//                 // printf("popsik\n");
//                 i_start = i + 1;
//                 i_end = i + 1;
//                 i_word_start = i + 1;
//                 push_end(&list, word);
//             }
//             if ((i + 1 < l) && (c == *(p+1)))
//             {   
//                 memmove(word, s + i, 2);
//                 word[2] = '\0';
//                 push_end(&list, word);
//                 i += 1;
//                 ++p;
//                 i_start = i + 1;
//                 i_end = i + 1;
//                 i_word_start = i + 1;
//             }
//             else if ((i + 1 < l) && c != *(p+1))
//             {
//                 memmove(word, s + i, 1);
//                 word[1] = '\0';
//                 // printf("word: %s\n",word);
//                 push_end(&list, word);
//                 i_start = i + 1;
//                 i_end = i + 1;
//                 i_word_start = i + 1;
//             }
//             // printf("word: %s\n",word);
            
//             break;
//         default:
//             ++i_end;
//             break;
//         }
//         // printf("word start index: %d character: %c\n",i_word_start, *(s + i_word_start));
//         ++p;
//     }
    

//     // printf("EOF flag: %d\n", s_eof);
//     // printf("EOL flag: %d\n", s_line);

//     free(s);
//     free(word);
//     // free(p);
    
//     // print_list(list);
//     return(list);
    
// }

int 
is_special(Node *list)
{
    if (list == NULL)
        return 0;

    char c = list->data[0];
    switch (c)
    {
    case '|':
    case '\"':
    case '\'':
    case '&':
    case ';':
    case '>':
    case '<':
    case '(':
    case ')':
    case '#':
    case '\\':
        return 1;
        break;
    default:
        return 0;
        break;
    }
}

Node *
get_list(void)
{
    Node *list = NULL;

    char *s = NULL, *p = NULL;
    char *word = NULL;
    char c = 32;
    
    int q_flag = 0;
    int q_one_flag = 0;
    int comm_flag = 1;
    int break_flag = 1;
    
    int i = 0;
    int i_word_start = 0;
    long long l = 0;
    int i_start = 0, i_end = 0;  
    // do
    // {
        // fflush(stdin);
        s = realloc(s, l + BUFF_SIZE);
        fflush(stdin);
        // l += fread(s + l, sizeof(char), BUFF_SIZE, stdin);
        if (fgets(s, l + BUFF_SIZE,stdin) == NULL)
        {
            // printf("popsik\n");
            free(s);
            return NULL;
        }
        else
        {
            l = strlen(s);
            
            // fflush(stdin);
            word = realloc(word, l + 1);
            p = s + i_word_start;
            // printf("i: %d l: %lld\n",i,l);
            for (; comm_flag && break_flag && (i < l); i++)
            {
                c = *p;
                // printf("%c\n", c);
                switch (c)
                {
                case '\"':
                    // if (slh_flag)
                    //     break;
                    if (!q_flag)
                        ++q_flag;
                    
                    if (i_start != i_end )
                    {
                        // printf("start: %d end: %d\n",i_start, i_end);
                        // printf("i: %d\n",i);
                        if (q_flag == 1)
                        {
                            memmove(word, s + i_start, i_end - i_start);
                            word[i_end - i_start] = '\0';
                            ++q_flag;
                            // i_start = i_end;
                            // break;
                        }
                        else
                        {
                            memmove(word, s + i_start, i_end - i_start);
                            word[i_end - i_start] = '\0';
                        }
                        // printf("word: %s\n",word);
                        // printf("popsik\n");
                        push_end(&list, word);
                        // ++i;
                        // ++p;
                        // i_start = i + 1;
                        // i_end = i + 1;
                        // i_word_start = i + 1;
                    }
                    if (q_flag == 2)
                        q_flag = 0;

                    i_start = i + 1;
                    i_end = i + 1;
                    i_word_start = i + 1;

                    break;
                case '\'':
                    // if (slh_flag)
                    //     break;
                    if (!q_one_flag)
                        ++q_one_flag;
                    
                    if (i_start != i_end )
                    {
                        // printf("start: %d end: %d\n",i_start, i_end);
                        // printf("i: %d\n",i);
                        if (q_one_flag == 1)
                        {
                            memmove(word, s + i_start, i_end - i_start);
                            word[i_end - i_start] = '\0';
                            ++q_one_flag;
                            // i_start = i_end;
                            // break;
                        }
                        else
                        {
                            memmove(word, s + i_start, i_end - i_start);
                            word[i_end - i_start] = '\0';
                        }
                        // printf("word: %s\n",word);
                        // printf("popsik\n");
                        push_end(&list, word);
                        // ++i;
                        // ++p;
                        // i_start = i + 1;
                        // i_end = i + 1;
                        // i_word_start = i + 1;
                    }
                    if (q_flag == 2)
                        q_flag = 0;

                    i_start = i + 1;
                    i_end = i + 1;
                    i_word_start = i + 1;

                    break;
                case ' ':
                case '\t':
                case '\n':
                case '\v':
                case '\b':
                case '\r':
                case '\f':
                    // if (slh_flag)
                    //     break;
                    // printf("start: %d end: %d\n",i_start, i_end);
                    // printf("qfag: %d\n",q_flag);

                    if (q_flag || q_one_flag)
                    {
                        // i_start = i + 1;
                        // c == '\n';
                        // break_flag = 0;
                        i_end = i + 1;
                        // printf("my_shell: error in quotation marks placement\n");
                        // i_word_start = i + 1;
                        break;
                    }

                    if (i_start == i_end)
                    {
                        i_start = i + 1;
                        i_end = i + 1;
                        i_word_start = i + 1;
                        break;
                    }

                    memmove(word, s + i_start, i_end - i_start);
                    word[i_end - i_start] = '\0';
                    i_start = i + 1;
                    i_end = i + 1;
                    i_word_start = i + 1;
                    push_end(&list, word);
                    break;
                
                case '|':
                case '&':
                case ';':
                case '>':
                case '<':
                case '(':
                case ')':
                case '#':
                    if (q_flag || q_one_flag)
                    {
                        i_end = i + 1;
                        break;
                    }
                    // printf("i: %d\n",i);
                    // printf("start: %d end: %d\n",i_start, i_end);
                    // printf("char: %c\n",c);
                    if (i_start != i_end )
                    {
                        memmove(word, s + i_start, i_end - i_start);
                        word[i_end - i_start] = '\0';
                        // printf("start: %d end: %d\n",i_start, i_end);
                        // printf("word: %s\n",word);
                        // printf("popsik\n");
                        i_start = i + 1;
                        i_end = i + 1;
                        i_word_start = i + 1;
                        push_end(&list, word);
                    }

                    if (c == '#')
                    {
                        comm_flag = 0;
                        break;
                    }

                    if ((i + 1 < l) && (c == *(p+1)))
                    {   
                        memmove(word, s + i, 2);
                        word[2] = '\0';
                        push_end(&list, word);
                        i += 1;
                        ++p;
                        i_start = i + 1;
                        i_end = i + 1;
                        i_word_start = i + 1;
                    }
                    else if ((i + 1 < l) && c != *(p+1))
                    {
                        memmove(word, s + i, 1);
                        word[1] = '\0';
                        // printf("word: %s\n",word);
                        push_end(&list, word);
                        i_start = i + 1;
                        i_end = i + 1;
                        i_word_start = i + 1;
                    }
                    break;
                case '\\':
                        if (q_flag || q_one_flag)
                            ++i_end;
                        // slh_flag = 1;
                        // printf("start: %d end: %d\n",i_start, i_end);
                        // printf("i: %d c: %c\n", i, c);
                        // printf("l: %lld\n",l);
                        // printf("next char: %c\n", *(p + 1));
                        // printf("\n");
                        if ((i + 2 < l) && (*(p+1) == '\\') && (*(p+2) == 'b'))
                        {
                            memmove(word, s + i + 1, 2);
                            word[2] = '\0';
                            // printf("word: %s\n",word);
                            push_end(&list, word);
                            i += 3;
                            p += 3;
                            i_start = i + 1;
                            i_end = i + 1;
                            i_word_start = i + 1;
                        }
                        else if ((i + 2 < l) && (*(p+1) == '\\') && (*(p+2) == 'r'))
                        {
                            memmove(word, s + i + 1, 2);
                            word[2] = '\0';
                            // printf("word: %s\n",word);
                            push_end(&list, word);
                            i += 3;
                            p += 3;
                            i_start = i + 1;
                            i_end = i + 1;
                            i_word_start = i + 1;
                        }
                        else if ((i + 2 < l) && (*(p+1) == '\\') && (*(p+2) == 'n'))
                        {
                            memmove(word, s + i + 1, 2);
                            word[2] = '\0';
                            // printf("word: %s\n",word);
                            push_end(&list, word);
                            i += 3;
                            p += 3;
                            i_start = i + 1;
                            i_end = i + 1;
                            i_word_start = i + 1;
                        }
                        else if ((i + 2 < l) && (*(p+1) == '\\') && (*(p+2) == 't'))
                        {
                            memmove(word, s + i + 1, 2);
                            word[2] = '\0';
                            // printf("word: %s\n",word);
                            push_end(&list, word);
                            i += 3;
                            p += 3;
                            i_start = i + 1;
                            i_end = i + 1;
                            i_word_start = i + 1;
                        }
                        else if ((i + 2 < l) && (*(p+1) == '\\') && (*(p+2) == 'f'))
                        {
                            memmove(word, s + i + 1, 2);
                            word[2] = '\0';
                            // printf("word: %s\n",word);
                            push_end(&list, word);
                            i += 3;
                            p += 3;
                            i_start = i + 1;
                            i_end = i + 1;
                            i_word_start = i + 1;
                        }
                        else if ((i + 2 < l) && (*(p+1) == '\\') && (*(p+1) == 'v'))
                        {
                            memmove(word, s + i + 1, 2);
                            word[2] = '\0';
                            // printf("word: %s\n",word);
                            push_end(&list, word);
                            i += 3;
                            p += 3;
                            i_start = i + 1;
                            i_end = i + 1;
                            i_word_start = i + 1;
                        }
                        else if ((i + 1 < l) && (*(p+1) == '\"'))
                        {
                            memmove(word, s + i + 1, 1);
                            word[1] = '\0';
                            // printf("word: %s\n",word);
                            push_end(&list, word);
                            i += 2;
                            p += 2;
                            i_start = i + 1;
                            i_end = i + 1;
                            i_word_start = i + 1;
                        }
                        else if ((i + 1 < l) && (*(p+1) == '\''))
                        {
                            memmove(word, s + i + 1, 1);
                            word[1] = '\0';
                            // printf("word: %s\n",word);
                            // printf("aboba\n");
                            push_end(&list, word);
                            i += 2;
                            p += 2;
                            i_start = i + 1;
                            i_end = i + 1;
                            i_word_start = i + 1;
                        }
                        // printf("word: %s\n",word);
                            // i_start = i + 1;
                            // i_end = i + 1;
                            // i_word_start = i + 1;
                        
                        break;
                default:
                    ++i_end;
                    break;
                }
                // printf("word start index: %d character: %c\n",i_word_start, *(s + i_word_start));
                ++p;
            }

        // c = fgetc(stdin);
        // fseek(stdin, -1, SEEK_CUR);
   
        // if (c == EOF)
        // {
        //     *flag = END_OF_FILE;
        //     // printf("met end of line\n");
        //     s_eof = 0;
        //     break;
        // }  
        // fputc(EOF, stdin);
        // fseek(stdin, -1, SEEK_CUR);
    // } while (!feof(stdin));
    // } while (s_line && s_eof);
            free(word);
        }
    free(s);
    // free(p);
    
    // print_list(list);
    return(list);
    // printf("\n");
    // printf("Before sorting: \n");
    // printf("\n");
    // print_size(list);
    // printf("\n");
    // print(list);
    // printf("\n");
    // s_sort(list,get_len(list));
    
    // printf("After sorting: \n");
    // printf("\n");
    // print(list);
    // printf("\n");

    // most_recent_word(list);

    // printf("%s\n",(get_node(list,0))->data);

    // detele_list(&list);
    
}

void
dollar_handler(Node *list)
{
    Node *p = list;
    while (p != NULL)
    {
        if (!strcmp(p->data, "$HOME")) 
        {
            p->data = realloc(p->data, PATH_MAX);
            strcpy(p->data, getenv("HOME"));
        } 
        else if (!strcmp(p->data, "$SHELL")) 
        {
            p->data = realloc(p->data, PATH_MAX);
            getcwd(p->data, PATH_MAX);
        }
        else if (!strcmp(p->data, "$USER")) 
        {
            p->data = realloc(p->data, PATH_MAX);
            strcpy(p->data, getenv("LOGNAME"));
        }
        else if (!strcmp(p->data, "$EUID")) 
        {
            p->data = realloc(p->data, PATH_MAX);
            sprintf(p->data, "%d", getuid());
        }
        p = p->next;
    }
    
}

// int
// count_word(Node *list, char *word)
// {
//     int count = 0;
//     Node *p = list;

//     while (p != NULL)
//     {
//         if (!strcmp(p->data, word))
//             ++count;
//         // printf("Times: %d\n",count);
//         // printf("Word: %s\n",p->data);
//         p = p->next;
//     }
    
//     return count;
// }
