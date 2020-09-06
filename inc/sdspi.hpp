#ifndef SDSPI
#define SDSPI

#include "stm32f4xx.h"

class SD
{
public:
    SD(){sd_spi_init();}
    void send_byte(uint8_t byte)
    {
        while(!(SPI2->SR&SPI_SR_TXE)){}        
        SPI2->DR=byte;
        //*(uint8_t*)SPI1->DR=data;
        while((SPI2->SR&SPI_SR_BSY)){}
    }
    uint16_t read_byte()
    {
        SPI2->DR = 0; //запускаем обмен
        while(!(SPI1->SR&SPI_SR_RXNE)) //ждем пока не появится новое значение в буффере приемника
        return SPI1->DR; //возвращаем значение из буффера приемника
    }
    uint16_t read_word()
    {
        SPI2->DR = 0; //запускаем обмен
        while(!(SPI1->SR&SPI_SR_RXNE)) //ждем пока не появится новое значение в буффере приемника
        return SPI1->DR; //возвращаем значение из буффера приемника
    }
    inline void cs_idle() __attribute ((always_inline))
    {GPIOB->BSRRH |= GPIO_BSRR_BS_12;}
    inline void cs_set() __attribute ((always_inline))
    {GPIOB->BSRRH |= GPIO_BSRR_BR_12;}
private:
    void sd_spi_init()
    {
        //------- SPI2 b12-NSS b13-SCK b14-MISO b15-MOSI ------------

        //--------PB12 - programm NSS push-pull output-----------
        GPIOB->MODER|=GPIO_MODER_MODER12_0;//
        GPIOB->MODER&=~GPIO_MODER_MODER12_1;// 0:1 output push-pull
        GPIOB->OSPEEDR|=GPIO_OSPEEDER_OSPEEDR12;
        //-------b13-SCK b14-MISO b15-MOSI - alt func SPI2 --------------------
        GPIOB->MODER|=(GPIO_MODER_MODER13_1|GPIO_MODER_MODER14_1|GPIO_MODER_MODER15_1);
        GPIOB->MODER&=~(GPIO_MODER_MODER13_0|GPIO_MODER_MODER14_1|GPIO_MODER_MODER15_1);
        //GPIOB->AFR[0]=0;
        GPIOB->AFR[1]|=(5<<20)|(5<<24)|(5<<28);//alt func 5 (SPI2)
        GPIOB->OSPEEDR|=GPIO_OSPEEDER_OSPEEDR3;//
        GPIOB->OSPEEDR|=GPIO_OSPEEDER_OSPEEDR5;//max speed on pins

        //------------- тактируем SPI-2  ---------------------------
        RCC->APB1ENR|=RCC_APB1ENR_SPI2EN; //clock on fast SPI-1
        //------------- предделитель SPI-1 -----------------------------
        SPI2->CR1|=SPI_CR1_BR; // (000=>psc=1) 1:1:1  => 42000000/256 = 164,0625 kHz - SPI-2 clk
        //------------- настройка SPI - 1 -----------------------------------------
        SPI2->CR1&=~SPI_CR1_BIDIMODE; // двухпроводной режим работы
        SPI2->CR1|=SPI_CR1_BIDIOE; //1: Output enabled (transmit-only mode)
        SPI2->CR1&=~SPI_CR1_CRCEN; // 0: CRC calculation disabled
        SPI2->CR1&=~SPI_CR1_CRCNEXT; //0: Data phase (no CRC phase)
        SPI2->CR1&=~SPI_CR1_DFF; //0: 8-bit data frame format is selected for transmission/reception
        SPI2->CR1&=~SPI_CR1_RXONLY; //0: Full duplex (Transmit and receive)
        SPI2->CR1|=SPI_CR1_SSM; // программное управление ведомым включено 
        SPI2->CR1|=SPI_CR1_SSI; // нужно чтобы эти два бита были в 1 для правильной инициализации мастера
        SPI2->CR1&=~SPI_CR1_LSBFIRST; //1: LSB first //0: MSB transmitted first
        SPI2->CR1|=SPI_CR1_MSTR; //1: Master configuration
        SPI2->CR1&=~SPI_CR1_CPOL; //1: CK to 1 when idle (смотреть в datasheet slave) 
        SPI2->CR1&=~SPI_CR1_CPHA; //1: The second clock transition is the first data capture edge (тоже)
        
        //NVIC_EnableIRQ(SPI1_IRQn);
        //----------- включаем SPI-1 --------------------------------------------
        SPI2->CR1|=SPI_CR1_SPE;
    }
    void sd_init()
    {

    }
};

#endif //SDSPI