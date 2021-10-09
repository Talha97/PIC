#include <main.h>

#INT_RDA
void  rda_isr(void) 
{
   disable_interrupts(INT_RDA);
   int32 count=0;
   int32 countCycle=0;
   
   do
   {
      if(kbhit(BT))
      {
         
         BLTReceive[count++]=getc(BT);
      
      }
   
   }while(count<100 && countCycle<65000);
   
   BLDataCame=1;
}



void main()
{


   enable_interrupts(INT_RDA);
   enable_interrupts(INTR_GLOBAL);
   
   initBluetooth();
   for(int i=0;i<64;i++)
      sendArray[i]=i;
      
   while(TRUE)
   {
     sendData(sendArray,64);
     if(BLDataCame)
     {
        BLDataCame=0;
        //Do whatever you want after data received via Bluetooth.
     
     }
     delay_ms(100);
   }

}
