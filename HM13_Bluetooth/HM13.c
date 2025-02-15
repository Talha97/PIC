/*

    AUTHOR: TALHA SEV�N�
 

*/


#include<HM13.h>

char transienBuffer[20];

void writeAT(char *command)
{

     fprintf(BT,"%s",command);
     memset(transienBuffer,'\0',20);

}

void testModule()
{
   sprintf(transienBuffer,"AT\r\n");
   writeAT(transienBuffer);
}

void queryEDRAddress()
{
   sprintf(transienBuffer,"AT+ADDE?\r\n");
   writeAT(transienBuffer);

}

void queryBLEAddress()
{
   sprintf(transienBuffer,"AT+ADDB?\r\n");
   writeAT(transienBuffer);

}

/*
Auth 0 ===> Allow every module
Auth 1===> every connection must with authentication.
*/
void QuerySet_Authentication(int1 query,int1 Auth)
{
  if(query)
    sprintf(transienBuffer,"AT+AUTH?\r\n");
  else
    sprintf(transienBuffer,"AT+AUTH%d\r\n",Auth);   
    
   writeAT(transienBuffer);

}

/*
Baud- Baud Rate
1   - 4800
2   � 9600
3   � 19200
4   � 38400
5   � 57600
6   � 115200
7   - 230400
*/
void QuerySet_BaudRate(int1 query,int Baud)
{
  if(query)
    sprintf(transienBuffer,"AT+BAUD?\r\n");
  else
    sprintf(transienBuffer,"AT+BAUD%d\r\n",Baud);   
    
   writeAT(transienBuffer);

}

/*This functions delete last module from memory. */
void clearLastEDRDevice()
{
  sprintf(transienBuffer,"AT+CLEAE\r\n");    
  writeAT(transienBuffer);
}

void clearBLEDevice()
{
  sprintf(transienBuffer,"AT+CLEAB\r\n");    
  writeAT(transienBuffer);
}

/*
P1: 0, 1,(Default: 0)
0: Balance mode
1: High speed mode 
*/
void QuerySet_DataTransferSpeed(int1 query,int1 Speed)
{
  if(query)
    sprintf(transienBuffer,"AT+HIGH?\r\n");
  else
    sprintf(transienBuffer,"AT+HIGH%d\r\n",Speed);   
    
   writeAT(transienBuffer);
}

/*
P1: 0, 1,?, (Default: 0)
0: Loaded notify 0ff
1: Loaded notify on 
When "AT+INIT1" is setup, after module loaded, module will output
"OK+INIT" string through UART. 
*/
void QuerySet_LoadedNotify(int1 query,int1 On)
{
  if(query)
    sprintf(transienBuffer,"AT+INIT?\r\n");
  else
    sprintf(transienBuffer,"AT+INIT%d\r\n",On);   
    
   writeAT(transienBuffer);

}


/*
**AT+MODE0: Only transfer data when connection establishment.
**AT+MODE1: Transfer data and response AT commands. 
*/
void QuerySet_WorkMode(int1 query,int1 mode) 
{
  if(query)
    sprintf(transienBuffer,"AT+MODE?\r\n");
  else
    sprintf(transienBuffer,"AT+MODE%d\r\n",mode);   
    
   writeAT(transienBuffer);
}


/*
After AT+NOTI1, module will send connect or disconnect string through
UART when module state is change:
OK+CONE ======== EDR connect
OK+LSTE ========= EDR disconnect
OK+CONB========= BLE connect
OK+LSTB ========= BLE disconnect 

OK+LSTA ========= except disconnect, module will reset after 500 ms. 
*/
void QuerySet_NotifyInformation(int1 query,int1 on) 
{
  if(query)
    sprintf(transienBuffer,"AT+NOTI?\r\n");
  else
    sprintf(transienBuffer,"AT+NOTI%d\r\n",on);   
    
   writeAT(transienBuffer);

}

void QuerySet_NameEDRDevice(int1 query,char *name)
{
  if(query)
    sprintf(transienBuffer,"AT+NAME?\r\n");
  else
    sprintf(transienBuffer,"AT+NAME%s",name);
   writeAT(transienBuffer);
}

void QuerySet_NameBLEDevice(int1 query,char *name)
{
  if(query)
    sprintf(transienBuffer,"AT+NAMB?\r\n");
  else
    sprintf(transienBuffer,"AT+NAMB%s",name);  
   writeAT(transienBuffer);

}

/*
P1: module EDR Code
Max length: 6
Default: 1234 
*/
void QuerySet_EDRPinCode(int1 query,char *password)
{
  if(query)
    sprintf(transienBuffer,"AT+PINE?\r\n");
  else
    sprintf(transienBuffer,"AT+PINE%s",password);  
    
   writeAT(transienBuffer);

}

/*
P1: module BLE Code
000000~999999
Default: 000000 
*/
void QuerySet_BLEPinCode(int1 query,char *password)
{
  if(query)
    sprintf(transienBuffer,"AT+PINB?\r\n");
  else
    sprintf(transienBuffer,"AT+PINB%s",password);  
    
   writeAT(transienBuffer);

}

/*
Update fabrica configuration to now config.
*/
void SetupValuetoFabricaSetup()
{
   sprintf(transienBuffer,"AT+RENEW\r\n");     
   writeAT(transienBuffer);
}

/*Device MAC address query*/
void QueryLastEDRDevice()
{
   sprintf(transienBuffer,"AT+RADE?\r\n");     
   writeAT(transienBuffer);
}

void QueryLastBLEDevice()
{
   sprintf(transienBuffer,"AT+RADB?\r\n");     
   writeAT(transienBuffer);
}

/*
Master1 ===> Master device set
*/
void QuerySet_MasterSlave(int1 query,int1 master)
{
  if(query)
    sprintf(transienBuffer,"AT+ROLB?\r\n");
  else
    sprintf(transienBuffer,"AT+ROLB%d\r\n",master);  
    
   writeAT(transienBuffer);
}

void initBluetooth()
{
   char BLBufferF[7];char BLBufferS[7];
   char BLBufferBLEF[7];
   BLBufferF="MyBL\r\n"; BLBufferS="Talha\r\n";
   BLBufferBLEF="MyBL_BLE\r\n";
   memset(transienBuffer,'\0',20);


   QuerySet_Authentication(0,0);delay_ms(200);  
   QuerySet_WorkMode(0,1); delay_ms(200);
   QuerySet_NameEDRDevice(0,BLBufferF);delay_ms(200);
   QuerySet_NameBLEDevice(0,BLBufferBLEF);delay_ms(200);
   QuerySet_EDRPinCode(0,BLBufferS);delay_ms(200);
   QuerySet_BLEPinCode(0,BLBufferS);delay_ms(200);

   enable_interrupts(INT_RDA3);
   enable_interrupts(INTR_GLOBAL);  

}
void sendData(int8 *message,int8 length)
{

  for(int k=0;k<length;k++)
  {
                              
     fprintf(BT,"%c",message[k]);
                                                           
  }

}

