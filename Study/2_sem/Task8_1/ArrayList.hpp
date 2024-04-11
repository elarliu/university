// #pragma once
#include "Collection.cpp"
#include <string.h>
#include <iostream>
template<typename T>
class ArrayList : public Collection{
  public:
  void add(void * data) override;
  void * remove(void * data) override;
  void clear() override;
  bool contains(void * data) override;
  size_t getSize() override;
};