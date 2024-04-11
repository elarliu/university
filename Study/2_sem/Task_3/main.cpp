#include <iostream>
#include "String.hpp"
// #include "String.cpp"
#include "List.hpp"
#include "List.cpp"

int
main()
{
    std::cout << "Список" << std::endl;

    IterableObject * lst_p = GetList<int>();

    int * num_p = new int;
    *num_p = 2;
    lst_p->add(num_p);
    *num_p = 3;
    lst_p->add(num_p);
    *num_p = 4;
    lst_p->add(num_p);

    std::cout << (lst_p->contains(num_p)) << std::endl;
    *num_p = 1;
    std::cout << (lst_p->contains(num_p)) << std::endl;

    std::cout << "List:" << std::endl;
    lst_p->print();

    // *num_p = 1;                      removing non-existent element
    // lst_p->remove(num_p);

    // *num_p = 2;                      removing first element
    // lst_p->remove(num_p);

    // *num_p = 3;                      removing middle element
    // lst_p->remove(num_p);

    *num_p = 4;                      // removing last element                    
    lst_p->remove(num_p);

    lst_p->print();

    *num_p = 5;
    
    // auto res = lst_p->swap(num_p, 10);
    auto res1 = lst_p->swap(num_p, 10);

    if (res1)
    {   
        // std::cout << "After swap" << std::endl;
        res1.value()->print();
    }
    else
    {
        std::cout << "Incorrect index" << std::endl;    
        lst_p->print();
    }    
    
    delete lst_p;
    delete num_p;

    
    std::cout << "Строки" << std::endl;


    IterableObject * str_p = GetString();

    char str[] = "aboba";
    str_p->add(str);

    str_p->print();
    std::cout << str_p->get_size() << std::endl;

    char c_p1[] = "boba";
    std::cout << str_p->contains(c_p1) << std::endl;
    char c_p2[] = "bebra";
    std::cout << str_p->contains(c_p2) << std::endl;
    char * c_p = new char;
    *c_p = 'b';

    str_p->remove(c_p);
    str_p->print();

    std::cout << str_p->get_size() << std::endl;
    *c_p = 'b';

    auto res2 = str_p->swap(c_p, 1);
    
    if (res2)
    {
        res2.value()->print();
    }
    else    
    {
        std::cout << "Incorrect index" << std::endl;    
        str_p->print();
    }

    // res2.value()->clear();
    // res2.reset();
    
    delete c_p;
    delete str_p;
}