#include "main.h"


//void * __dso_handle = 0;
//void * __cxa_guard_acquire = 0;

int main()
{
    //static const uint8_t flashBuff[500000]={0xAB};   
    PD_led led;
    Uart6 uart;
    SpiLcd lcd;
    Font_16x16 font;    
    font.fillScreen(0xff00);
    uint32_t x=0;
    while(1)
    {       
        x++;
        for(uint32_t i=0;i<1000000;i++);
        font.intToChar(x);
        font.print(10,10,0x00ff,font.arr,3);
        //led.led12_toggle();
        uart.sendStr("\n opa\n");        
    }
    return 0;
}
