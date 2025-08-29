#include <stdio.h>

template <typename T>
class Linklist
{
private:
    T _item;
    T *_next;
public:

    Linklist(/* args */);
    ~Linklist();

    T* add(T item);
    size_t count();
    T* remove(size_t index);
};

Linklist::Linklist(/* args */)
{
}

Linklist::~Linklist()
{
}
