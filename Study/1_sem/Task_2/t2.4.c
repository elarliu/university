#include <stdio.h>
#include <string.h>
#include <math.h>
#include <errno.h>

#define MAXLINE 10 /* максимальное число символов в записи вещественного числа */

enum
{
    ERROR_CODE_FOR_INPUT = 0,
};

double 
str_double(char str[], int MAX,int e);

int 
errors(char str[], int *MAX);

int
getlen(char str[]);

int
main(void)
{
    char line[MAXLINE]; /* строка для считывания из stdin*/
    int len,e; /* длина строковой записи текущего вещесвенного числа, переменная для обработок ошибок*/
    e = 1;

    double result;
    // double d;
    // scanf("%lf",&d);

    // printf("%lf",d);
    
    while (e && (scanf("%s",line)!=EOF))
    {
        len = getlen(line);
        // printf("%s %d\n",line,len);
        e = errors(line,&len);
        // printf("%s %d\n",line,len);
        if (e)
        {
            result = str_double(line,len,e);
            printf("%lf\n",result);
        }
        else
        {
            fprintf(stderr, "There is an error in input: %d\n", ERROR_CODE_FOR_INPUT);
            return ERROR_CODE_FOR_INPUT;
        }
    }

    return 0;
}

int
getlen(char s[])
{
    int i;
    for (i = 0; s[i]!='\0'; i++)
        ;
    return i;
    
}

int
errors(char s[],int *MAX)
{
    int dot_count,e_count;
    dot_count = 0;
    e_count = 0;
    for (int i = 0; (i< *MAX); i++)
    {
        // printf("%d\n",dot_count);
        if (s[i]=='.')
        {
            if (dot_count==1)
            {
                return ERROR_CODE_FOR_INPUT;
            }
            else
            {
                if (*MAX==1)
                    return ERROR_CODE_FOR_INPUT;
                ++dot_count;
            }
        }
        else if (s[i]=='-')
        {
            return 10;
        }
        else if (s[i]<'0' || s[i]>'9')
        {
            if ((s[i]=='e' || s[i]=='E') && i!=0 && s[i+1]!='\0' &&
                (s[i+1]=='+' || s[i+1]=='-' || (s[i+1]>='0' && s[i+1]<='9')))
            {
                if (e_count==1)
                {
                    return ERROR_CODE_FOR_INPUT;
                }
                else
                {
                    ++e_count;
                }
            }
            else if((s[i]=='f' || s[i]=='F') && i==(*MAX-1))
            {
                --*MAX;
            }
            else if (e_count)
            {
                ;
            }
            else
            {
                return ERROR_CODE_FOR_INPUT;
            }
        }
        
    }
    if (e_count)
    {
        return 2;
    }
    else
    {
        return 1;
    }
    
}

double 
str_double(char s[], int MAX, int e)
{
    double result,d;
    int f,f_e,sign;
    result = 0;
    d = 10;
    f = 0;
    int i = (e == 10);
    
        for (; i < MAX && (f_e = (s[i]!='e')); i++)
        {
        // printf("%d %lf\n",f,result);
            if(s[i]=='.')
            {
                ++f;
            }

            if (f==0)
            {
                result = result*d + s[i]-'0';
            }
            else
            {
                if (s[i]!='.')
                {
                    result = result + (s[i]-'0')/d;
                    d*=10;
                }
            }
        }
    // printf("%lf\n",result);

    if (f_e)
    {
        if (e==10)
            return -result; 
        return result;   
    }
    else
    {
        i+=1;
        if (s[i]=='+' || s[i]=='-')
        {
            sign = s[i];
            ++i;
        }
        else
        {
            sign = '+';
        }
        d = 0;
        // printf("%d\n",i);
        for (; i < MAX; i++)
        {
            d = d*10 + s[i]-'0';
        }
        // printf("%lf\n",d);
        d = pow(10,d);
        if (sign == '+')
        {
            result*=d;
        }
        else
        {
            result/=d;
        }
        if (e==10)
            return -result;    
        return result;
    }
    
}

    
    