// #include "ArrayList.hpp"
#include "Collection.cpp"
#include "Object.hpp"
#include <string.h>
#include <sstream>
#include <iostream>
template<typename T>
class ArrayList : public Collection, public Object{
  T ** data{};
  size_t size{};
public:
  ArrayList(T * array, size_t size) : size(size) {
    data = new T[size];
    memcpy(data, array, size * sizeof(T));
  }
  ArrayList(){}
  void add(void * value) override {
    std::cout<<__PRETTY_FUNCTION__<<std::endl;
    if (size == 0) {
            data = new T*[1];
            data[0] = (T *)value;
            size = 1;
            return;
        }
        T ** newData = new T*[size + 1];
        for (size_t i = 0; i < size; i++) {
            newData[i] = data[i];
        }
        newData[size] = (T *)value;
        size++;
        delete[] data;
        data = newData;
  }
  void * remove(void * value) override {
    for (size_t i = 0; i < size; i++) {
        if (value == data[i]) {
            T ** newData = new T*[size - 1];
            for (size_t j = i; j < size; j++) {
                newData[j] = (T *)data[j + 1];
            }
            size--;
            delete[] data;
            data = newData;
            return data;
        }
    }
    return nullptr;
  }
  void clear() override {
    for (size_t i = 0; i < size; i++) {
        delete data[i];
    }
    delete[] data;
    data = nullptr;
    size = 0;
  }
  bool contains(void * value) override {
    for (size_t i = 0; i < size; i++) {
        if (value == data[i]) {
            return true;
        }
    }
    return false;
  }
  size_t getSize() override {
    return size;
  }
  ~ArrayList() {
    clear();
  }
  std::string toString() const override {
    std::stringstream ss;
    ss << "[";
    for (size_t i = 0; i < size; i++) {
      ss << data[i];
      if (i < size - 1) {
        ss << ", ";
      }
    }
    ss << "]";
    return ss.str();
  }

};