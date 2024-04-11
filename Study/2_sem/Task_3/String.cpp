#include "String.hpp"
#include "IterableObject.hpp"
#include <cstring>

String::String(): size_{1}
{
    str_ = new char[1]{'\0'};
}

String::String(const char * str)
{
    // std::cout << "str size: " << strlen(str) << std::endl;
    size_ = strlen(str) + 1;
    str_ = new char[size_];
    strcpy(str_, str);
    str_[size_ - 1] = '\0';
}

String::String(const String & str): size_{str.size_}
{
    str_ = new char[str.size_];
    strcpy(str_, str.str_);
}

// void String::swap(String & str)
// {
//     std::swap(str_, str.str_);
//     std::swap(size_, str.size_);
// }

int String::get_size()
{
    return size_;
}

void String::add(void * data)
{
    char * d = (char *) data;

    char * res = new char[strlen(d) + size_];
    strcpy(res, str_);
    strcpy(res + size_ - 1, d);

    delete[] str_;
    str_ = new char[strlen(d) + size_];
    strcpy(str_,res);
    delete[] res;
    size_ += strlen(d);
    str_[size_ - 1] = '\0';

}

bool String::contains(void * data)
{
    char * d = (char *) data;
    std::string str((*this).c_str());

    return str.contains(d);
}

char & String::operator [] (int i)
{
    if (i < 0 || i > size_)
        throw "Index out of range";
    return str_[i];
}

char * String::c_str()
{
    return str_;
}

char & String::front()
{
    return str_[0];
}

char & String::back()
{
    return str_[size_ - 1];
}

bool String::empty()
{
    return ((size_ == 0) && (str_[0] == '\0'));
}

void String::clear()
{
    delete[] str_;
    size_ = 0;
}

String String::operator = (const String & str)
{
    delete[] str_;
    size_ = str.size_;

    str_ = new char[str.size_];
    strcpy(str_, str.str_);
    return *this;
}

String String::operator + (const String & str)
{
    String s(*this);
    s.add(str.str_);
    return s;
}

const String & String::operator += (const String & str)
{
    (*this).add(str.str_);
    return *this;
}

std::ostream & operator << (std::ostream & out, const String & str)
{
    std::cout << str.str_;
    return out;
}

bool operator == (const String & str1, const String & str2)
{
    return (str1.size_ == str2.size_) && (!strcmp(str1.str_, str2.str_));
}

void String::print()
{
    std::cout << (*this) << std::endl;
}

void * String::remove(void * data)
{
    char * d = (char *) data;
    // if (strlen(d) != 1)
    //     throw "String::remove : argument should be single character";
    
    char res[size_];
    int j = 0;
    for (int i = 0; i < size_; i++)
    {
        if (str_[i] != (*d))
        {
            res[j] = str_[i];
            ++j;
        }
    }
    res[j] = '\0';
    strcpy(str_, res);
    size_ = strlen(res) + 1;

    return d;
}

void * String::get_data()
{
    return str_;
}

// void String::set_size(int size)
// {
//     size_ = size;
// }

// void String::set_data()
// {
//     delete str_[];

// }

IterableObject * GetString()
{
    return new String;
}

std::optional<IterableObject *> String::swap(void * data, int i)
{
    char * d = (char *) data;

    IterableObject * res_p = GetString();

    // std::cout << "In string swap" << std::endl;


    char str_swap[size_];
    // std::cout << "size: " << size_ << std::endl;
    strcpy(str_swap, str_);
    // str_swap[size_ + 1] = '\0';

    if ( i>= 0 && i <= size_)
    {
        
        str_swap[i] = (*d);
        res_p->add(str_swap);
        // std::cout << "res data: ";
        // res_p->print();
        // std::cout << "res size: " << res_p->get_size() << std::endl;
        // strcpy(str_swap);
        // str_[i] = *d;
        return res_p;
    }
    else
    {
        delete res_p;
        return {};
    }
    
}