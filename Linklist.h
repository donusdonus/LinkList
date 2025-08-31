#ifndef LINKLIST_H
#define LINKLIST_H

#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>
#include<functional>

using namespace std;

//#define ARCH_16Bit
#define ARCH_32Bit


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
    public:
    T *item;
    Items* _next;
    Items* _prev;
};


template<typename T>
class LinkList
{
private:
    /* data */
    MemorySource MemSource;
    typedef void (*filter)(T*);
    typedef std::function<void (T*)> func_filter;


    /* private function */

    bool available(Items<T>** src = nullptr)
    {
        if((src != nullptr) && (*src != nullptr))
          return  true;
        return false ;
    }

    bool  Add(Items<T>* data) 
    {
        
        Items<T> **prev = nullptr;
        Items<T> **next = nullptr;
        
        next = &Lists;

        if(data == nullptr)
            return false;

        while(available(next))
        {
            prev = next;
            next = &(*next)->_next;
        }    

        *next = data;
        if(available(prev))
            (*next)->_prev = *prev;
                 
        return true;
    }

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

    size_t count_member(Items<T>** src = nullptr)
    {
        size_t cnt = 0;

        while (available(src))
        {
            src = &(*src)->_next;
            cnt+=1;
        }   

        return cnt;
    }

    Items<T>** last(Items<T>** src = nullptr)
    {
        while (has_next(src))
        {
            src = &(*src)->_next;
        }
        return src;
    }

    void cpy(void *des ,void *src,size_t size)
    {
        uint8_t *s = (uint8_t*)src;
        uint8_t *d = (uint8_t*)des;

        #ifdef ARCH_32Bit
        while(size >= 4)
        { 
            *(uint32_t*)d = *(uint32_t*)s ;
            s+=4;
            d+=4;
            size-=4;
        }
        #endif

        #ifdef ARCH_32Bit
            while(size >= 2)
            { 
                *(uint16_t*)d = *(uint16_t*)s ;
                s+=2;
                d+=2;
                size-=2;
            }
        #elif ARCH_16Bit
            while(size >= 2)
            { 
                *(uint16_t*)d = *(uint16_t*)s ;
                s+=2;
                d+=2;
                size-=2;
            }
        #endif

        while(size >= 1)
        { 
            *(uint8_t*)d = *(uint8_t*)s ;
            s+=1;
            d+=1;
            size-=1;
        }

    }

public:
    Items<T> *Lists = nullptr;

    LinkList(){SetMemory(MemorySource::RAM);}
    LinkList(MemorySource type = MemorySource::RAM){SetMemory(type);}
    ~LinkList(){ Clear(); }

    void SetMemory(MemorySource type)
    {
        MemSource = type;
    }

    bool Add(T data)
    {
        Items<T>* tmp = nullptr;


        tmp = (Items<T>*)Allocator(MemSource,1,sizeof(Items<T>));
        if(tmp == nullptr)
            return false;

        tmp->item = nullptr;
        tmp->item = (T*)Allocator(MemSource,1,sizeof(T));
        if(tmp->item == nullptr)
            return false;
        

        cpy(tmp->item,&data,sizeof(T));        

        return Add(tmp);
    }

    bool Add(T *data)
    {
        Items<T>* tmp = nullptr;
        tmp = (Items<T>*)Allocator(MemSource,1,sizeof(Items<T>));
        if(tmp == nullptr)
            return false;

        tmp->item = data;

        return Add(tmp);
    }

    size_t Count()
    {
        return count_member(&Lists);
    }

    size_t Size(){ return Count()*sizeof(Items<T>);}

    bool Remove(size_t index)
    {
        Items<T>** cur = &Lists;
        Items<T>* prev = nullptr;
        Items<T>* next = nullptr;

        size_t cnt = 0;  
        bool   found = false;

        while ((cnt <= index) || (found == false))
        {
            /* code */
            if(available(cur))
            {
                if(index == cnt)
                {
                    found = true;
                }
                else 
                {
                    cur = &(*cur)->_next;
                }
            }
            else 
            {
                return false;
            }
            cnt+=1;
        }

        prev = available(&(*cur)->_prev)? (*cur)->_prev : nullptr;
        next = available(&(*cur)->_next)? (*cur)->_next : nullptr;

        // case last
        if(available(&prev) && !available(&next))
        {
               Free((*cur)->item);
               (*cur)->item = nullptr;
               (*cur)->_next = nullptr;
               (*cur)->_prev = nullptr;
               Free(*cur);
               *cur = nullptr;

               prev->_next = nullptr;
        }
        // case mid
        else if(available(&prev) && available(&next))
        {
               Free((*cur)->item);
               (*cur)->item = nullptr;
               (*cur)->_next = nullptr;
               (*cur)->_prev = nullptr;
               Free(*cur);
               *cur = nullptr;

               prev->_next = next;
               next->_prev = prev;
        }
        // case first
        else if(!available(&prev) && available(&next))
        {
               Free(&Lists->item);
               Lists->item = nullptr;
               Lists->_next = nullptr;
               Lists->_prev = nullptr;
               Free(Lists);
               Lists = nullptr;
               Lists = next;
        }
        else 
        {
            return false;
        }

        return true;
    }

    T* operator[](size_t index) 
    {
        Items<T>** tmp = &Lists; 
        size_t cnt = 0;  
        while (cnt <= index)
        {
            /* code */
            if(available(tmp))
            {
                if(index == cnt)
                    return (*tmp)->item;
                tmp = &(*tmp)->_next;
            }
            else 
            {
                return nullptr;
            }
            cnt+=1;
        }
        return nullptr;
    }

    void Find(func_filter filter = nullptr)
    {
        Items<T>** cur = &Lists;   
        while (available(cur))
        {
            if(filter != nullptr)
                filter((*cur)->item);
               // func((*cur)->item);
            cur = &(*cur)->_next;
        }  
    }

    void Clear()
    {
        Items<T>** cur = &Lists;
        Items<T>** del = nullptr;

        while (available(cur))
        {
            del = cur;
            cur = &(*cur)->_next;
            
            Free((*del)->item);
            (*del)->item = nullptr;
            (*del)->_next = nullptr;
            (*del)->_prev = nullptr;
            Free(*del);
            *del = nullptr;     
        } 
    }
    
};


#endif
