#include <33EP256MU810.h>

#FUSES NOWDT                    //No Watch Dog Timer
#FUSES CKSFSM                   //Clock Switching is enabled, fail Safe clock monitor is enabled
#FUSES NOBROWNOUT               //No brownout reset
#FUSES NOJTAG                   //JTAG disabled

#device ICSP=1
#use delay(clock=96MHz,crystal=24MHz)
#pin_select U1TX=PIN_D1
#pin_select U1RX=PIN_D13
#use rs232(UART1, baud=115200, stream=BT)

int1 BLDataCame=0;
int8 sendArray[64];
int8 BLTReceive[100];
#include "HM13.c"
