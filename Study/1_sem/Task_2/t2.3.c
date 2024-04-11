#include <stdio.h>
#include <errno.h>

enum
{
    ERROR_CODE_FOR_INPUT = 0,
};

int 
fbn_i(int i);
int 
fbn_r(int i);

int
main(void)
{
    int i,s;

    while((s = scanf("%d",&i))!=EOF && s!=0)
    {
        printf("Iteration technic %d\n",fbn_i(i));
        printf("Recursion technic %d\n",fbn_r(i));
        putchar('\n');
    }

    if(s==0)
    {
        fprintf(stderr, "There is an error in number input: %d\n", ERROR_CODE_FOR_INPUT);
        return ERROR_CODE_FOR_INPUT;
    }
    return 0;
}

int
fbn_i(int i)
{
    int n1,n2,p;
    n1 = 1;
    n2 = 1;

    if (i==1 || i==2)
    {
        return n1;
    }
    else
    {
        for(int j=3;j<=i;++j)
        {
            p = n1;
            n1 = n2;
            n2 = p+n2;
        }
        return(n2);
    }
}

int
fbn_r(int i)
{
    if (i==1 || i==2)
    {
        return 1;
    }
    else
    {
        return (fbn_i(i-1) + fbn_r(i-2));
    }
}