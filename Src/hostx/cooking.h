#ifndef __HOSTX_COOKBOOK
#define __HOSTX_COOKBOOK
    
    #include "facade.h"
    
    typedef void (*COOK_FUNCTION)(void*);
    
    typedef struct XRESOURCE
    {
        COOK_FUNCTION   cook;
        
        USART_TypeDef*  use_usart;
        GPIO_TypeDef*   use_gpio;
        DMA_TypeDef*    use_dma;
        
        uint32_t        dma_chTX;
        uint32_t        dma_chRX;
        
        uint32_t        gpio_pinTX;
        uint32_t        gpio_pinRX;
        
    }COOK_RECEIPT;
        
    extern void COOK_HW(COOK_RECEIPT* xres);
    
    
#endif
