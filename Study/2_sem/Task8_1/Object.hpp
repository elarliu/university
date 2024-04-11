#pragma once
#include <string>
class Object{
public:
  virtual std::string toString() const {
    return "<Object at " + std::to_string(reinterpret_cast<unsigned long>(this)) + '>';
  }
};