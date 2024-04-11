#ifndef ITERABLE_OBJECT_HPP
#define ITERABLE_OBJECT_HPP
#include <optional>
class IterableObject
{
    public:
        virtual void add(void * data) = 0;
        virtual void * remove(void * data) = 0;
        virtual void clear() = 0;
        virtual bool contains(void * data) = 0;
        virtual int get_size() = 0;
        virtual void print() = 0;
        virtual void * get_data() = 0;
        // virtual void set_data(void * data) = 0;
        // virtual void set_size(int size) = 0;
        virtual ~IterableObject() = default;
        virtual std::optional<IterableObject *> swap(void * data, int i) = 0;
    // private:
    //     int size_;
};
#endif 