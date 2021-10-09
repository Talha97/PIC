#include <33EP256MU810.h>

#FUSES NOWDT                    //No Watch Dog Timer
#FUSES CKSFSM                   //Clock Switching is enabled, fail Safe clock monitor is enabled
#FUSES NOBROWNOUT               //No brownout reset
#FUSES NOJTAG                   //JTAG disabled

#device ICSP=1
#use delay(clock=96MHz,crystal=24MHz)
#pin_select U1TX=PIN_D1
#pin_select U1RX=PIN_D13
#use rs232(UART1, baud=9600, stream=GPS)


int8 GPSValues[500];
int1 locationFound=0;
int8 GprMcArray[150];
int8 latitude[10];
int8 longitude[10];
int1 dataCameGPS=0;

#include "GPS.c"
