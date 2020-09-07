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
    //uint32_t x=0;
    SD sd;
    uint8_t sd_status = sd.sd_init();
    font.intToChar(sd_status);
    font.print(10,10,0x00ff,font.arr,3);
    while(1)
    {  
        //uint8_t temp = sd.send_command(0x40,0x00,0x00,0x00,0x00,0x95); //CMD0  
        //uint16_t temp = sd.send_cmd(0x00,0x00000000);
        //font.intToChar(temp);
        //font.print(100,10,0x00ff,font.arr,3);
        //temp = sd.send_cmd(0x08,0x00000000);
        //temp = sd.send_command(0x41,0x00,0x00,0x00,0x00,0x87); //CMD0  
        //font.intToChar(temp);
        //font.print(100,100,0x00ff,font.arr,3);
        //temp = sd.send_cmd(0x58,0x1AA);
        //font.intToChar(temp);
        //font.print(100,200,0x00ff,font.arr,3);
    
        ////led.led12_toggle();
        //uart.sendStr("\n opa\n");        
    }
    return 0;
}
