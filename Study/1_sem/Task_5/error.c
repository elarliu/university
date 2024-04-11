#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include "list.h"
#include "error.h"

int 
check_error(Node *list)
{
    Node *p = list;

    if (list != NULL && is_special(list))
        return ERR_SPCL_SYM;
    // int open_brck = 0;
    // int close_brck = 0;

    int qtn_mrk_1 = 0;
    int qtn_mrk_2 = 0;
    while (p != NULL)
    {
        // проверка скобок для subshell
        // printf("%s\n", p->data);
        if(!strcmp(p->data, "("))
        {
            // ++open_brck;
            // if(is_special(p->next))
            return ERR_BRCKT;
        }

        if(!strcmp(p->data, ")"))
        {
            // ++close_brck;
            return ERR_BRCKT;
        }
        
        // if(open_brck - close_brck < 0)
        // {
        //     return ERR_BRCKT;
        // }
        
        // основная проверка на повторяющиеся специальные символы и незакрытие кавычек
        if((!strcmp(p->data, ";")))
        {
            if(is_special(p->next))
                return ERR_SMCLN;
            // else if (p->next == NULL)
            //     return ERR_NEXT;
        }
        else if((!strcmp(p->data, ">")))
        {
            if(is_special(p->next))
                return ERR_OUTPT;
            // else if (p->next == NULL)
            //     return ERR_OUTPT_FILE;
        }
        else if((!strcmp(p->data, "<")))
        {
            if(is_special(p->next))
                return ERR_INP;
            // else if (p->next == NULL)
            //     return ERR_INP_FILE;
        }
        else if((!strcmp(p->data, "&")))
        {
            if(is_special(p->next))
                return ERR_APSND;
        }
        else if((!strcmp(p->data, "|")))
        {
            if(is_special(p->next))
                return ERR_VRTCL_BR;
            // else if (p->next == NULL)
            //     return ERR_PIPE;
        }
        // else if((!strcmp(p->data, "\"")))
        // {
        //     ++qtn_mrk;
        //     if((p->next != NULL) && (!strcmp(p->next->data, "\"")))
        //         return ERR_QTN_MRK;
        // }
        else if((!strcmp(p->data, ">>")))
        {
            if(is_special(p->next))
                return ERR_DBL_OUTPT;
            // else if (p->next == NULL)
            //     return ERR_OUTPT_FILE;
        }
        else if((!strcmp(p->data, "||")))
        {
            if(is_special(p->next))
                return ERR_DBL_VRTCL_BR;
            // else if (p->next == NULL)
            //     return ERR_OR_PR;
        }
        else if((!strcmp(p->data, "&&")))
        {
            if(is_special(p->next))
                return ERR_DBL_APSND;
            // else if (p->next == NULL)
            //     return ERR_AND_PR;
        }
        else if((!strcmp(p->data, "\'")))
        {
            if(is_special(p->next))
                return ERR_QTN_MRK;
            ++qtn_mrk_2;
            // else if (p->next == NULL)
            //     return ERR_AND_PR;
        }
        else if((!strcmp(p->data, "\"")))
        {
            if(is_special(p->next))
                return ERR_QTN_MRK;
            ++qtn_mrk_2;
            // else if (p->next == NULL)
            //     return ERR_AND_PR;
        }
        p = p->next;
    }
    
    // if (open_brck != close_brck)
    // {
    //     return ERR_BRCKT;
    // }

    if (qtn_mrk_1 % 2 != 0)
    {
        return ERR_QTN_MRK;
    }
    
    if (qtn_mrk_2 % 2 != 0)
    {
        return ERR_QTN_MRK;
    }

    return 0;

}

int
print_error(int err)
{
    switch (err)
    {
    case ERR_BRCKT:
        printf("my_shell: error near ()\n");
        return 1;
        break;

    case ERR_QTN_MRK:
        printf("my_shell: error in quotation marks placement\n");
        return 1;
        break;

    case ERR_SMCLN:
        printf("my_shell: error near ;\n");
        return 1;
        break;    
    
    case ERR_APSND:
        printf("my_shell: error near &\n");
        return 1;
        break;    
    
    case ERR_DBL_APSND:
        printf("my_shell: error near &&\n");
        return 1;
        break;   
    
    case ERR_OUTPT:
        printf("my_shell: error near >\n");
        return 1;
        break;   

    case ERR_DBL_OUTPT:
        printf("my_shell: error near >>\n");
        return 1;
        break;   

    case ERR_INP:
        printf("my_shell: error near <\n");
        return 1;
        break;   
    
    case ERR_VRTCL_BR:
        printf("my_shell: error near |\n");
        return 1;
        break;   

    case ERR_DBL_VRTCL_BR:
        printf("my_shell: error near ||\n");
        return 1;
        break;   
        
    case ERR_SPCL_SYM:
        printf("my_shell: unexpected special lexeme\n");
        return 1;
        break;   

    // case ERR_INP_FILE:
    //     printf("Inmy_shell: error\n");
    //     return 1;
    //     break;   

    // case ERR_OUTPT_FILE:
    //     printf("my_shell: error file error\n");
    //     return 1;
    //     break;   
    
    // case ERR_PIPE:
    //     printf("my_shell: error error\n");
    //     return 1;
    //     break;  
    
    // case ERR_AND_PR:
    //     printf("my_shell: AND process execution error\n");
    //     return 1;
    //     break; 

    // case ERR_OR_PR:
    //     printf("my_shell: OR process execution error\n");
    //     return 1;
    //     break; 
    
    // case ERR_NEXT:
    //     printf("my_shell: NEXT process execution error\n");
    //     return 1;
    //     break; 
    // case ERR_BRCKT:
    //     printf("my_shell: error nead ()\n");
    //     return 1;
    //     break; 

    default:
        return 0;
        break;
    }
}