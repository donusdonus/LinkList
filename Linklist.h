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

enum ListFlagMark
{
    /* 
        When never has event Free address value in list must not Free member value. !!! 
    */
    bit_user_manage_address = 0

};


#pragma pack(push,1)
template<typename T>
struct Items
{
    public:
    T *item;
    uint8_t flag;
    Items* _next;
    Items* _prev;
};
#pragma pack(pop)

#define sssss sizeof(Items<T>)

template<typename T>
class LinkList
{
private:
    /* data */
    MemorySource MemSource;
    typedef std::function<void (T*,size_t)> func_filter;
    size_t limit_member = 0;
    size_t total_member = 0;

    Items<T> *Lists = nullptr;

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
                 
        total_member += 1;
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

    LinkList(size_t size=0){SetMemory(MemorySource::RAM);}
    LinkList(MemorySource type = MemorySource::RAM,size_t size=0){SetMemory(type);limit_member = size;}
    ~LinkList(){ Clear(); }

    void SetMemory(MemorySource type)
    {
        MemSource = type;
    }

    bool Add(T data)
    {
        /* 
            insert data to lists by value.
            data will insert new address. 
        */
        Items<T>* tmp = nullptr;

        if((limit_member > 0) && (limit_member == total_member))
            return false;

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

    /* 
        insert data to lists by reference pointer.
        data is not copy value. 
        but reference pointer address.
    */
    bool Add(T *data)
    {
        Items<T>* tmp = nullptr;

        if((limit_member > 0) && (limit_member == total_member))
            return false;

        tmp = (Items<T>*)Allocator(MemSource,1,sizeof(Items<T>));
        if(tmp == nullptr)
            return false;

        tmp->item = data;

        tmp->flag |= (1<<ListFlagMark::bit_user_manage_address);
        return Add(tmp);
    }

    /* 
        count member of list
    */
    size_t Count()
    {
        return  total_member ; //count_member(&Lists);
    }

    /* 
        get size of memory in list
    */
    size_t Size(){ return Count()*sizeof(Items<T>);}

    /* 
        Remote member in lists by index
    */
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
            if(((*cur)->flag & (1<<ListFlagMark::bit_user_manage_address)) == 0)            
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
            if(((*cur)->flag & (1<<ListFlagMark::bit_user_manage_address)) == 0)
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
             if((Lists->flag & (1<<ListFlagMark::bit_user_manage_address)) == 0)
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

        total_member-=1;
        return true;
    }

    /*
       operator [] is not safety memory.
       exam in bad case assign value.
          *obj[10] = value ; when obj[10] = nullptr

       please check nullptr first before modify value.
       exam in good case assign value.
          if(*obj[10] != nullptr)
                obj[10] = value;
    */
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

    /*
       Find item in list by assign function pointer
       exam x[0]=2 , x[1]=100 , x[2]=14 
       assume filter data as 100.
       
       x.Find([](int *data,size_t index){     
            if(*data == 100)
                dosomething;
       });
    */
    void Find(func_filter filter = nullptr)
    {
        size_t index = 0;
        Items<T>** cur = &Lists;   
        while (available(cur))
        {
            if(filter != nullptr)
                filter((*cur)->item,index);
               // func((*cur)->item);
            cur = &(*cur)->_next;
            index+=1;
        }  
    }

    /* 
        Reject all member in list
    */
    void Clear()
    {
        Items<T>** cur = &Lists;
        Items<T>** del = nullptr;

        while (available(cur))
        {
            del = cur;
            cur = &(*cur)->_next;
            
            if(((*del)->flag & (1<<ListFlagMark::bit_user_manage_address)) == 0)
                Free((*del)->item);

            (*del)->item = nullptr;
            (*del)->_next = nullptr;
            (*del)->_prev = nullptr;
            Free(*del);
            *del = nullptr;     
            total_member-=1;
        } 
    }
    
};


#endif
