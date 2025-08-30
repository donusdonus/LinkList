#ifndef LINKLIST_H
#define LINKLIST_H

#include <stdio.h>
#include <stdlib.h>



/* Edit Memory Source Area */
/* RAM TYPE */
#define _TYPE_RAM 0 
/* PSRAM TYPE */
#define _TYPE_PSRAM 1


enum MemorySource
{
    RAM=_TYPE_RAM,PSRAM=_TYPE_PSRAM
};

template<typename T>
struct Items
{
    T item;
    Items* _next;
    Items* _prev;
};

template<typename T>
class LinkList
{
private:
    /* data */
    MemorySource MemSource;
    Items<T> *src;
    Items<T>** cur;
    bool monitor = false;

    /* private function */
    void * Allocator(MemorySource type,size_t numberElements,size_t size)
    {
          switch (type)
        {
        case _TYPE_RAM:
            return calloc(numberElements,size);
            break;
        case _TYPE_PSRAM:
            return calloc(numberElements,size);
            break;
        default:
            return calloc(numberElements,size);
            break;
        }
        
        return nullptr;
    }

    void Free(void *src){ free(src);  }

public:
   

    LinkList(){SetMemory(MemorySource::RAM);}
    LinkList(MemorySource type = MemorySource::RAM){SetMemory(type);}
    ~LinkList(){}

    void SetMemory(MemorySource type)
    {
        MemSource = type;
    }

    bool Add(T data)
    {
        T* tmp = nullptr;
        tmp = (T*)Allocator(MemSource,1,sizeof(T));
        if(tmp == nullptr)
            return false;

        return Add(tmp);
    }

    bool  Add(T* data) 
    {
        if(data == nullptr)
            return false;

        cur = &src;

        while((cur != nullptr) && (*cur != nullptr))
            cur = &(*cur)->_next;
        
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


    T* next()
    {
        return src->_next ;
    }

    T* prev()
    {
        return src->_prev ;
    }

    T* last()
    {
        return nullptr;
    }

};


#endif
