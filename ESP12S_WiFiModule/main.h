#include <33EP256MU810.h>

#FUSES NOWDT                    //No Watch Dog Timer
#FUSES CKSFSM                   //Clock Switching is enabled, fail Safe clock monitor is enabled
#FUSES NOBROWNOUT               //No brownout reset
#FUSES NOJTAG                   //JTAG disabled

#device ICSP=1
#use delay(clock=96MHz,crystal=24MHz)
#pin_select U1TX=PIN_D1
#pin_select U1RX=PIN_D13

#use rs232(UART1, baud=115200, stream=WiFi)


int1 wifiDataCame=0;

int8 timeOutWiFi=0;
int8 wifiData[2048][2];

char messageSend[2048];
char wifiID[50];
char wifiPassword[50];
#include "Wifi_ESP12.c"

