/*
   AUTHOR: TALHA SEVİNÇ
*/

char Hours[11];

int gprmc=0;
int cntGprMc=0;
int satelliteNum=0;

float altitudeValue=0.0;
char satellite[2];
char altitude[6];

int1 valid=false;
int1 findValue=false;

void GPSInit()
{
   enable_interrupts(INT_RDA);
   enable_interrupts(INTR_GLOBAL);
   
}

void GPSDeInit()
{
   disable_interrupts(INT_RDA);

}

int1 TakeGpsGPGGA(void)
{

     locationFound=0;
     valid=false;
     int count=0;
     int1 gprmcbool=false;
     cntGprMc=0;
     findValue=false;
     memset(GprMcArray,'\0',150);
  

     while(!findValue){

     for(int i=0;i<495;i++)
     {
                if(GpsValues[i]=='G' &&GpsValues[i+1]=='P' &&GpsValues[i+2]=='R' && GpsValues[i+3]=='M' && GpsValues[i+4]=='C')
                {
                       gprmc=i+6;

                       while(GpsValues[i] !='\r')
                       {

                               i++;
                               if(i==500)
                               {
                                 return false;
                               }


                       }

                        findValue=true;
                        gprmcbool=true;
                        break;

                }
    }

     findValue=true;

     }

     count=gprmc;

     if(gprmcbool)
     {

        while(GpsValues[count] != '\r')
        {
   
           GprMcArray[cntGprMc]=GpsValues[count];
   
           ++count;
           ++cntGprMc;
   
        }
     }


         int commaCount=0;
         int i=0;

         while(i<cntGprMc-1)
          {

           if(GprMcArray[i]==',')
           {
                commaCount++;
                i++;

                if(commaCount==1)
                {
                   if(GprMcArray[i]=='A')
                   {
                      valid=true;
                      break;

                   }

                   else if(GprMcArray[i]=='V')
                   {

                      valid=false;
                      break;
                   }
                   ++i;

                }
           }

           else
              i++;
          }

         return valid;

}


int1 GPSLatitGGA(void)
{
   
    int commaCount=0;
    int i=0;
    int cntLong=0;
    char indicator;

    while(commaCount<4)
    {

      if(GprMcArray[i]==',')
      {
           commaCount++;
           i++;


            if(commaCount==2)
            {

               while(GprMcArray[i] != ',')
               {
                 if(GprMcArray[i] !='.')
                 { 
                   latitude[cntLong+1]=GprMcArray[i];
                   cntLong++;
                 }
                 
                 i++;

                }

           }
           
           else if(commaCount==3)
           {
                 indicator=  GprMcArray[i];
                 latitude[0]=indicator;
                 break;
           
           }
      }

      else
          i++;

    }

    int1 founded=false;

    if(cntLong >= 6)
    {
      

       founded=true;
    }

    if(founded)
       return 1;

    return 0;

  

}

int1 GPSLongitudeGGA(void)
{
   
    int commaCount=0;
    int i=0;
    int cntLong=0;
    char indicator;
    
    while(commaCount<6)
    {

      if(GprMcArray[i]==',')
      {
           commaCount++;
           i++;

           if(commaCount==4)
           {          
               while(GprMcArray[i] != ',')
               {
                  if(GprMcArray[i] !='.')
                  {  
                    longitude[cntLong+1]=GprMcArray[i];
                    cntLong++;
                  }
                  i++;

              }

           }
           else if(commaCount==5)
           {
                 indicator=  GprMcArray[i];
                 longitude[0]=indicator;
                 break;
           
           }
      }

      else
          i++;

    }
    
    int1 founded=false;

    if(cntLong >= 6)
    {

       founded=true;
    }

    if(founded)
       return 1;

    return 0;

   }



void GpsHoursGGA(void)
{

    int i=0;
    int cntLong=0;

        while(GprMcArray[cntLong] != ',')
       {

           if(GprMcArray[cntLong] != '.')
               hours[i]=GprMcArray[cntLong];

           else
                  hours[i]='0';


          if(cntLong % 2 == 1 && cntLong != 7)
          {
             i++;
             hours[i]=':';
          }
          i++;
          cntLong++;

        }

        for(i=0;i<11;i++)
         {

            Hours[i]=hours[i];

         }

        Hours[11]='\n';

}


int GpsSatellite(void)
{

  
    int commaCount=0;
    int i=0;
    int cntLong=0;

    while(commaCount<7)
    {

      if(GprMcArray[i]==',')
      {
         commaCount++;
           i++;


            if(commaCount==6)
            {

               while(GprMcArray[i] != ',')
            {
                  satellite[cntLong]=GprMcArray[i];

                  cntLong++;

                  i++;

            }
               commaCount++;


           }
      }

      else
          i++;

    }

    int1 founded=false;

    if(cntLong == 2)
    {

       satelliteNum=(int)((satellite[0]-48)*10 + (satellite[1]-48)) ;
                     

       founded=true;
    }

    if(founded)
       return satelliteNum;

    return 0;



}

float GpsAltitude(void)
{


   int commaCount=0;
    int i=0;
    int cntLong=0;

    while(commaCount<9)
   {

      if(GprMcArray[i]==',')
      {
         commaCount++;
           i++;


            if(commaCount==8)
            {

               while(GprMcArray[i] != ',')
            {
                  altitude[cntLong]=GprMcArray[i];

                  cntLong++;

                  i++;

            }
               commaCount++;


           }
      }

      else
          i++;

    }

    int1 founded=false;

    if(cntLong == 6)
    {

       altitudeValue=(float)((altitude[0]-48)*1000 + (altitude[1]-48)*100 + (altitude[2]-48)*10 + (altitude[3]-48) +(float)(altitude[5]-48)/10)  ;
                     

       founded=true;
    }

    if(founded)
       return altitudeValue;

    return 0;


}



