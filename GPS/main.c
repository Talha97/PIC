#include <main.h>

#INT_RDA
void  rda_isr(void) 
{
  disable_interrupts(INT_RDA);
  int32 countCycle=0;
  int16 count=0;
  do
  {
  
   if(kbhit(GPS))
   {
      GPSValues[count++]=getc(GPS);
      countCycle++;
   }
  
  }while(count<500 && countCycle<64435);
  
  dataCameGPS=1;
  enable_interrupts(INT_RDA);
  
}



void main()
{


   enable_interrupts(INT_RDA);
   enable_interrupts(INTR_GLOBAL);

   while(TRUE)
   {
     if(dataCameGPS)
     { 
       dataCameGPS=0;
       if(TakeGpsGPGGA())
       {
          GPSLatitGGA();
          GPSLongitudeGGA();
             
       
       }
     
     }
   }

}
