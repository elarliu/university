#include <stdio.h>
#include <setjmp.h>
#include <math.h>


jmp_buf begin; /* точка начала диалога с пользователем */

char curlex; /* текущая лексема */

void 
getlex(void); /* выделяет из входного потока очередную лексему */

int
expr(void); /* распознает выражение и вычисляет его значение */

int 
add(void); /* распознает слагаемое и вычисляет его значение */

int
mult(void); /* распознает множитель и вычисляет его значение */

int
poww(void);

void
error(); /* сообщает об ошибке в выржаении и передает управление в начало функции main (точка gegin) */

int 
main(void)
{

    int result;
    setjmp(begin);
    printf("==>");

    getlex();
    result = expr();
    if (curlex != '\n')
        error();
    printf("\n%d\n",result);
    return 0;


}

void
getlex()
{
    while ((curlex = getchar()) == ' ');    
}

void 
error(void)
{
    printf("\nERROR\n");
    while (getchar() != '\n');
    longjmp(begin,1);
}

int 
expr()
{
    int e = add();
    while (curlex == '+')
    {  
        getlex();
        e+=add();
    }    
    while (curlex == '-')
    {  
        getlex();
        e-=add();
    }    
    return e;
}

int 
add()
{
    
    int a = poww();
    while (curlex == '*')
    {
        getlex();
        a*=mult();
    }
    while (curlex == '/')
    {
        getlex();
        a/=mult();
    }
    return a;
}

int
poww()
{
    int a = mult();

    while (curlex == '^')
    {
        getlex();
        // if (a<0)
        //     error();
        a=(int)pow(a,poww());
        if (a==0)
            error();
    }
    return a;
}


// int
// sub()
// {
//     int a = mult();
//     while (curlex == '*')
//     {
//         getlex();
//         a*=mult();
//     }
//     return a;
// }

int 
mult()
{
    int m;
    switch (curlex)
    {
    case '0': case '1': case '2': case '3': case '4': case '5':
    case '6': case '7': case '8': case '9': m = curlex - '0'; break;
    
    case '-': getlex(); m = mult(); return -m; break;
    
    case '(': getlex(); m = expr();
        if (curlex == ')') 
            break;
    
    /* иначе ошибка нет закрывающей скобки */
    
    default:
        error();
    }
    getlex();
    return m;
}
