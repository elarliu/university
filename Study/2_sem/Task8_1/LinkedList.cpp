#include "Collection.cpp"
#include "LinkedListNode.h"
#include "Object.hpp"
template<typename T>
class LinkedList : public Collection, public Object{
  LinkedListNode<T> * head;
  LinkedListNode<T> * tail;
  size_t size;
public:
  LinkedList(){
    head = nullptr;
    tail = nullptr;
    size = (size_t)0;
  }
  ~LinkedList(){
    clear();
  }
  void add(void * data) override {
    T * d = (T *)data;
    if (head == nullptr) {
      head = new LinkedListNode<T>(*d);
      tail = head;
    } else {
      tail->next = new LinkedListNode<T>(*d);
      tail = tail->next;
    }
    ++size;
  }
  virtual void * remove(void * data) override {
    LinkedListNode<T>* temp = head;
    LinkedListNode<T>* temp2 = nullptr;
    T * d = (T *) data;
    while (temp!= nullptr) {
      if (temp->data == *d) {
        if (temp2 == nullptr) {
          head = temp->next;
        }
        else {
          temp2->next = temp->next;
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
  void clear() override {
    LinkedListNode<T>* temp = head;
    while (temp!= nullptr) {
      LinkedListNode<T>* temp2 = temp;
      temp = temp->next;
      delete temp2;
    }
    head = nullptr;
    tail = nullptr;
    size = 0;
  }
  bool contains(void * data) override {
    LinkedListNode<T>* temp = head;
    T * d = (T *) data;
    while (temp!= nullptr) {
      if(*d == temp->data)
        return true;
      temp = temp->next;
    }
    return false;
  }
  size_t getSize() override {
    return size;
  }
};