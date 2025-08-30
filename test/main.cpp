#include "LinkList.h"
LinkList<char> item(MemorySource::RAM);
LinkList<LinkList<char>> a(MemorySource::RAM);


const char msg[] = "ABCDE";

int main()
{

   for(auto s : msg)
   {
      item.Add(s);    
   }

   for(auto v = 0 ; v < item.Count() ; v++)
      printf("member[%d] : %c\n",(v+1),*item[v]);

   item.Remove(2);

   return 0 ;
}