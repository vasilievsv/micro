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
    
    void COOK_LL_SimpleDebug(COOK_RECEIPT* xres)
    {
        if (!(CoreDebug->DEMCR & CoreDebug_DEMCR_TRCENA_Msk)) 
        {
            CoreDebug->DEMCR |= CoreDebug_DEMCR_TRCENA_Msk;
            
            DWT->CYCCNT  = 0;
            DWT->CTRL   |= DWT_CTRL_CYCCNTENA_Msk;
        }
    }
    
    COOK_RECEIPT RECEIPT_SimpleDWT =
    {
         .cook       = &COOK_LL_SimpleDebug
        
        ,.use_usart  = 0
        ,.use_gpio   = 0
        ,.use_dma    = 0
        
        ,.dma_chTX   = 0
        ,.dma_chRX   = 0
        ,.gpio_pinTX = 0
        ,.gpio_pinRX = 0
    };
    