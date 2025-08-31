#include "LinkList.h"
LinkList<char> item(MemorySource::RAM);
LinkList<LinkList<char>> a(MemorySource::RAM);


Items<char> hell;

#define dddd sizeof(hell)

const char msg[] = "ABCBDBE";

/*
void findchar(char *data)
{
   if(*data == 'B')
      printf("Found %c in Item\n",*data);
}
   */

int main()
{
   //item.ForEach([](char *s){});

   for(auto s : msg)
   {
      item.Add(s);    
   }

   item.Find([](char *data){

      if(*data == 'B')
         printf("Found %c in Item\n",*data);   
   });

  // item.ForEach(findchar);

   item.Clear();

   

   //for(auto v = 0 ; v < item.Count() ; v++)
   //   printf("member[%d] : %c\n",(v+1),*item[v]);

   //item.Remove(0);

   return 0 ;
}