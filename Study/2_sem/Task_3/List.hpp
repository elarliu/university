#include "IterableObject.hpp"
#include <iostream>
#ifndef LIST_HPP
#define LIST_HPP

template <typename T>
struct ListNode
{
    T data;
    ListNode<T> * next;
    ListNode(T data): data{data}, next{nullptr} {}
};

template<typename T>
class List : public IterableObject
{
    public:
        List();

        List(const List<T> & lst);
        
        void add(void * data) override;

        void * remove(void * data) override;

        void clear() override;

        bool contains(void * data) override;

        int get_size() override;

        void * get_data() override;

        std::optional<IterableObject *> swap(void * data, int i) override;

        // void set_size(int size) override;

        friend std::ostream & operator << (std::ostream & out, const List<T> & lst)
        {
            ListNode<T> * temp = lst.head;
            while (temp != nullptr)
            {
                std::cout << temp->data << " ";
                temp = temp->next;
            }
            std::cout << std::endl;
            return out;
        }

        void print() override;

        ~List()
        {
            clear();
        }
    private:
        ListNode<T> * head;
        ListNode<T> * tail;
        int size;
};

#endif