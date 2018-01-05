/**
  ******************************************************************************
  * @file    
  * @author  
  * @version 
  * @date     4 jan 2018 
  * @brief   
  ******************************************************************************
*/
    #include "../hostx/cooking.h"
    
    void COOK_LL_SimpleCRC32(COOK_RECEIPT* xres)
    {
        RCC->AHBENR |= RCC_AHBENR_CRCEN; //Разрешить тактирование CRC-юнита
        
        CRC->CR = 1;
        __NOP(); //Аппаратная готовность за 4 такта, жду...
        __NOP();
        __NOP();
    }
    
    COOK_RECEIPT RECEIPT_CRC32 =
    {
         .cook       = &COOK_LL_SimpleCRC32
        
        ,.use_usart  = 0
        ,.use_gpio   = 0
        ,.use_dma    = 0
        
        ,.dma_chTX   = 0
        ,.dma_chRX   = 0
        ,.gpio_pinTX = 0
        ,.gpio_pinRX = 0
    };

    
    
    uint32_t  revbit(uint32_t  Data)
    {
        __RBIT(Data);
        //asm("rbit r0,r0");
        return Data;
    }
    
    uint32_t hxCRC32(uint8_t *Buf, uint32_t Len)
    {
        unsigned int i;
        unsigned int Temp;
        
        // Аппаратный CRC-расчёт работает с 32-битными словами. Т.е. сразу по 4 байта из входной последовательности
        i = Len >> 2;
        while(i--)
        {
            Temp = *((unsigned int*)Buf);
            Temp = revbit(Temp); // Переставить биты во входных данных
            CRC->DR = Temp;
            
            Buf += 4;
        }
        
        Temp = CRC->DR;
        //Temp = revbit(Temp); //Переставить биты в выходных данных
        //Temp ^= 0xFFFFFFFFul;
        return Temp;
    }
    
    