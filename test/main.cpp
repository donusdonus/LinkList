#include "LinkList.h"
LinkList<char> item(MemorySource::RAM,2);


Items<char> hell;

#define dddd sizeof(hell)

const char msg[] = "ABCDEFGHIJKLMONPQRSTUVWXYZ";

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
      printf("Push Data Return : %d \n",item.Add(s));     
   }


   *item[0] = 2;

   item.Find([](char *data,size_t index){

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