#include <main.h>

void main()
{

    for(int i=0;i<128;i++)
       rawArray[i]=i;
       
   AESEncrypt(rawArray, 128,encryptedArray);          //For encrypte rawArray **(rawDatas,size,destinationDatas)
   AESDecrypte(encryptedArray,128,decryptedArray);    //For decrypte rawArray **(encryptedDatas,size,destinationDatas)
   
   while(TRUE)
   {
     
   }

}
