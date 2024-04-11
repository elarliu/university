#pragma once
#include <cstddef>
class Collection {
public:
  virtual ~Collection() = default;
  virtual void add(void * data) = 0;
  virtual void * remove(void * data) = 0;
  virtual void clear() = 0;
  virtual bool contains(void * data) = 0;
  virtual size_t getSize() = 0;
};