#include <main.h>


#INT_TIMER1
void  timer1_isr(void) 
{
    ms256++;
    if(ms256 == 4)
    {    
        timeOutWiFi++;
        ms256=0;
    
    }
}

#INT_RDA
void  rda_isr(void) 
{
    int32 countCycle=0;
    int16 dataCount=0;
    disable_interrupts(INT_RDA);
    do
    {
       if(kbhit(WiFi))
       {
       
         wifiData[dataCount++][0]=getc(WiFi);
         countCycle++;
         
       }
     
    }while(countCycle<65000 && dataCount<2048);
  
    wifiDataCame=1;
    enable_interrupts(INT_RDA);
}



void main()
{

   setup_timer1(TMR_INTERNAL | TMR_DIV_BY_256, 47999);
   enable_interrupts(INT_RDA);
   enable_interrupts(INT_TIMER1);
   enable_interrupts(INTR_GLOBAL);

   connectESP();  //Configuration function. You have to change this settings according to your settings.
   messageSend="WiFi ESP12S Library...";
   while(TRUE)
   {
      sendDataviaESP(messageSend,0,50);
      if(wifiDataCame)
      {
         wifiDataCame=0;
         //Do what you want after data received via ESP.
      
      }
      delay_ms(1000);
   }

}
