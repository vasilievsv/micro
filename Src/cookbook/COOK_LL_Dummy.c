/**
  ******************************************************************************
  * @file    
  * @author  
  * @version 
  * @date     4 jan 2018 
  * @brief   
  ******************************************************************************
*/
    #include "hostx/cooking.h"
    
    void COOK_LL_Dummy(COOK_RECEIPT* xres)
    {
        __NOP(); // 4 такта, жду...
        __NOP();
        __NOP();
    }
    
    COOK_RECEIPT RECEIPT_Dummy =
    {
         .cook       = &COOK_LL_Dummy
        
        ,.use_usart  = 0
        ,.use_gpio   = 0
        ,.use_dma    = 0
        
        ,.dma_chTX   = 0
        ,.dma_chRX   = 0
        ,.gpio_pinTX = 0
        ,.gpio_pinRX = 0
    };
    