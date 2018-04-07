/**
  ******************************************************************************
  * @file    
  * @author  
  * @version 
  * @date     4 jan 2018 
  * @brief   
  ******************************************************************************
*/
    #include "../micro/cook.h"
    
    void COOK_LL_SimpleRadioPort(COOK_RECEIPT* xres)
    {
        __NOP();
        __NOP();
        __NOP();
    }
    
    COOK_RECEIPT receipt_ENABLE_NRF24L01 =
    {
         .cook       = &COOK_LL_SimpleRadioPort
        
        ,.use_usart  = 0
        ,.use_gpio   = 0
        ,.use_dma    = 0
        
        ,.dma_chTX   = 0
        ,.dma_chRX   = 0
        ,.gpio_pinTX = 0
        ,.gpio_pinRX = 0
    };
    