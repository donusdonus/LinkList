#ifndef LINKLIST_H
#define LINKLIST_H

#include <stdio.h>
#include <functional>

using namespace std;

/* Edit Memory Source Area */
/* RAM TYPE */
#define _TYPE_RAM 0 
#define _RAM(size,numberElements) calloc(numberElements,size)
/* PSRAM TYPE */
#define _TYPE_PSRAM 1
#define _PSRAM(size,numberElements) calloc(numberElements,size)
/* Free memory function */
#define _Free(src) free(src)

enum MemorySource
{
    RAM=_TYPE_RAM,PSRAM=_TYPE_PSRAM
};

template<typename T>
struct Items
{
    T item;
    T* _next;
    T* _prev;
};

template<typename T>
class LinkList
{
private:
    /* data */
    MemorySource MemSource;
    Items<T> *src;

public:
    typedef std::function<T*(T*)> FilterHandler_func;

    LinkList(MemorySource type = MemorySource::RAM){SetMemory(type);}
    ~LinkList(){}

    void SetMemory(MemorySource type)
    {
        MemSource = type;
    }

    bool Add(T data)
    {
        return false;
    }

    bool  Add(T* data) 
    {
        return false;
    }

    size_t Count()
    {
    return 0;
    }

    int Remove(size_t index)
    {
    return 0;
    }

    T* Filter(FilterHandler_func func)
    {
        if (func)
        {
            return func(nullptr);
        }
        return nullptr;
    }

};


#endif
