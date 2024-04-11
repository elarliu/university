#include "IterableObject.hpp"
#include "List.hpp"
#include <iostream>

template<typename T>
List<T>::List()
{
    head = nullptr;
    tail = nullptr;
    size = 0;
}

template<typename T>
List<T>::List(const List<T> &)
{
    ListNode<T> * temp = head;
    while (temp != nullptr)
    {
        (*this).add(temp->data);
        temp = temp->next;
    }
}

template<typename T>
void List<T>::add(void * data) 
{
    T * d = (T *) data;
    if (head == nullptr) 
    {
        head = new ListNode<T>(*d);
        tail = head;
    } 
    else 
    {
        tail->next = new ListNode<T>(*d);
        tail = tail->next;
    }
    ++size;
}

template<typename T>
void * List<T>::remove(void * data) 
{
    ListNode<T>* temp = head;
    ListNode<T>* temp2 = nullptr;
    T * d = (T *) data;
    while (temp != nullptr) 
    {
        if (temp->data == *d) 
        {
            if (temp2 == nullptr) 
            {
                ListNode<T>* temp_del = head;
                head = temp->next;
                delete temp_del;
            }
            else 
            {
                ListNode<T>* temp_del = temp2->next;
                temp2->next = temp->next;
                delete temp_del;
            }
          // delete temp;
            size--;
            return data;
        }
        temp2 = temp;
        temp = temp->next;
    }
    return data;
}

template<typename T>
void List<T>::clear() 
{
    ListNode<T>* temp = head;
    while (temp != nullptr) 
    {
      ListNode<T>* temp2 = temp;
      temp = temp->next;
      delete temp2;
    }
    head = nullptr;
    tail = nullptr;
    size = 0;
}

template<typename T>
bool List<T>::contains(void * data) 
{
    ListNode<T>* temp = head;
    T * d = (T *) data;
    while (temp != nullptr) 
    {
      if(*d == temp->data)
        return true;
      temp = temp->next;
    }
    return false;
}

template<typename T>
int List<T>::get_size() 
{
    return size;
}

template<typename T>
IterableObject * GetList()
{
    return new List<T>;
}

template<typename T>
void List<T>::print()
{
    std::cout << (*this) << std::endl;
}

// template<typename T>
// void List<T>::set_size(int i)
// {
//     size = i;
// }

template<typename T>
void * List<T>::get_data()
{
    return head;
}

template<typename T>
std::optional<IterableObject *> List<T>::swap(void * data, int i)
{
    IterableObject * res_p = GetList<T>();

    if (i >= 0 && i <= size)
    {
        ListNode<T>* temp2 = head;
        T * ptr = new T;
        int j = 0;
        while (temp2 != nullptr)
        {
            *ptr = temp2->data;
            if(i == j)
            {
                res_p->add(data);
            }
            else
            {
                res_p->add(ptr);
            }
            temp2 = temp2->next;
            ++j;
        }
        
        delete ptr;
        return res_p;
    }
    else
    {
        delete res_p;
        return {};
    }
}