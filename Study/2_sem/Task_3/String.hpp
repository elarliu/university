#include "IterableObject.hpp"
#include <cstring>
#include <iostream>

#ifndef STRING_HPP
#define STRING_HPP

class String: virtual public IterableObject
{
    public:
    String();

    String(const char * str);

    String(const String & str);

    String operator = (const String & str);

    void swap(String & str);
        
    void add(void * data) override;         

    void clear() override;                  

    int get_size() override;                

    void print() override;
        
    bool contains(void * data) override;
    
    void * remove(void * data) override;

    void * get_data() override;

    // void set_data() override;

    // void set_size(int size);

    std::optional<IterableObject *> swap(void * data, int i) override;

    char & operator [] (int i);

    String operator + (const String & str);
    const String & operator += (const String & str);

    char * c_str();

    char & front();

    char & back();

    bool empty();

    friend bool operator == (const String & str1, const String & str2);

    friend std::ostream & operator << (std::ostream & out, const String & str);

    ~String()
    {
        clear();
    }

    private:
        int size_;
        char * str_;
        
};

IterableObject * GetString();

#endif 
