#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "char_list.h"

int
main(void)
{
    Node *list = NULL;
    
    char *s = NULL, *p;
    char *word = NULL;
    char c = 32;
    // while (fscanf(stdin, "%s", s) != EOF)
    // {
    //     push_end(&list,s);
    // }
    int i = 0;
    int i_word_start = 0;
    long long l = 0;
    int i_start = 0, i_end = 0;  
    do
    {
        s = realloc(s, l + BUFF_SIZE);
        l += fread(s + l, sizeof(char), BUFF_SIZE, stdin);
        word = realloc(word, l + 1);
        p = s + i_word_start;
        // printf("i: %d l: %lld\n",i,l);
        for (; i < l; i++)
        {
            c = *p;
            switch (c)
            {
            case ' ':
            case '\t':
            case '\n':
                if (i_start - i_end == 0)
                    break;
                memmove(word, s + i_start, i_end - i_start);
                word[i_end - i_start] = '\0';
                // printf("start: %d end: %d\n",i_start, i_end);
                // printf("word: %s\n",word);
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
                // printf("i: %d\n",i);
                // printf("start: %d end: %d\n",i_start, i_end);
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

            default:
                ++i_end;
                break;
            }
            // printf("word start index: %d character: %c\n",i_word_start, *(s + i_word_start));
            ++p;
        }
        i = i_word_start;
        i_end = i_word_start;
        i_start = i_word_start;

    } while (!feof(stdin));
    free(s);
    free(word);
    printf("\n");
    printf("Before sorting: \n");
    printf("\n");
    print_size(list);
    printf("\n");
    print(list);
    printf("\n");
    s_sort(list,get_len(list));
    
    printf("After sorting: \n");
    printf("\n");
    print(list);
    printf("\n");

    most_recent_word(list);

    // printf("%s\n",(get_node(list,0))->data);

    detele_list(&list);
    
}