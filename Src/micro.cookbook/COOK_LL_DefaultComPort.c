/**
  ******************************************************************************
  * @file    
  * @author  
  * @version 
  * @date     4 jan 2018 
  * @brief   
  ******************************************************************************
  
    ..\doc\stm32f100rbt6b.pdf page 27

  */

#include "../micro/cook.h"


void COOK_LL_SimpleUSART(COOK_RECEIPT* xres)
{
    // GPIO
    LL_APB2_GRP1_EnableClock( LL_APB2_GRP1_PERIPH_AFIO );
    LL_APB2_GRP1_EnableClock( LL_APB2_GRP1_PERIPH_GPIOA );
    
    LL_GPIO_SetPinMode  (xres->use_gpio, xres->gpio_pinTX,  LL_GPIO_MODE_ALTERNATE );
    LL_GPIO_SetPinSpeed (xres->use_gpio, xres->gpio_pinTX,  LL_GPIO_SPEED_FREQ_LOW );
    //LL_GPIO_SetPinPull  (xres->use_gpio, xres->gpio_pinTX,  LL_GPIO_PULL_DOWN);
    
    LL_GPIO_SetPinMode  (xres->use_gpio, xres->gpio_pinRX,  LL_GPIO_MODE_FLOATING );
    LL_GPIO_SetPinSpeed (xres->use_gpio, xres->gpio_pinRX,  LL_GPIO_SPEED_FREQ_LOW );
    LL_GPIO_SetPinPull  (xres->use_gpio, xres->gpio_pinRX,  LL_GPIO_PULL_UP );
    
    // DMA
    // MEMORY TO PERIPH
    LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_DMA1);
    
    LL_DMA_Init (DMA1,LL_DMA_CHANNEL_4, &(LL_DMA_InitTypeDef)
    {
        .Priority                = LL_DMA_PRIORITY_LOW
                     
        ,.Mode                   = LL_DMA_MODE_NORMAL
        ,.Direction              = LL_DMA_DIRECTION_MEMORY_TO_PERIPH
                     
        ,.MemoryOrM2MDstAddress  = xres->dma_m2p_dst
        ,.MemoryOrM2MDstIncMode  = LL_DMA_MEMORY_INCREMENT
        ,.MemoryOrM2MDstDataSize = LL_DMA_MDATAALIGN_BYTE
        
        ,.PeriphOrM2MSrcAddress  = xres->dma_m2p_src
        ,.PeriphOrM2MSrcIncMode  = LL_DMA_PERIPH_NOINCREMENT
        ,.PeriphOrM2MSrcDataSize = LL_DMA_PDATAALIGN_BYTE
                     
        ,.NbData                 = 32
    });
    
    LL_DMA_EnableIT_TC  ( xres->use_dma, xres->dma_chTX );
    LL_DMA_EnableIT_HT  ( xres->use_dma, xres->dma_chTX );
    NVIC_EnableIRQ      (DMA1_Channel4_IRQn);
    
    // PERIH TO MEMORY
    LL_DMA_Init ( DMA1, LL_DMA_CHANNEL_5, &(LL_DMA_InitTypeDef)
    {
        .Priority               = LL_DMA_PRIORITY_LOW

        ,.Mode                   = LL_DMA_MODE_CIRCULAR
        ,.Direction              = LL_DMA_DIRECTION_PERIPH_TO_MEMORY

        ,.PeriphOrM2MSrcAddress  = xres->dma_p2m_src
        ,.PeriphOrM2MSrcIncMode  = LL_DMA_PERIPH_NOINCREMENT
        ,.PeriphOrM2MSrcDataSize = LL_DMA_PDATAALIGN_BYTE

        ,.MemoryOrM2MDstAddress  = xres->dma_p2m_dst
        ,.MemoryOrM2MDstIncMode  = LL_DMA_MEMORY_INCREMENT
        ,.MemoryOrM2MDstDataSize = LL_DMA_PDATAALIGN_BYTE

        ,.NbData                 = 32
    });
    
    LL_DMA_EnableIT_TC( xres->use_dma, xres->dma_chRX );
    LL_DMA_EnableIT_HT( xres->use_dma, xres->dma_chRX );
    NVIC_EnableIRQ( DMA1_Channel5_IRQn );
    
    LL_DMA_EnableChannel(xres->use_dma, xres->dma_chRX);
    
    // USART
    LL_APB2_GRP1_EnableClock( LL_APB2_GRP1_PERIPH_USART1 );
    
    LL_USART_Init(USART1, &(LL_USART_InitTypeDef)
    {
        .BaudRate             = 115200
        ,.DataWidth           = LL_USART_DATAWIDTH_8B
        ,.StopBits            = LL_USART_STOPBITS_1
        ,.Parity              = LL_USART_PARITY_NONE
        ,.HardwareFlowControl = LL_USART_HWCONTROL_NONE
        ,.TransferDirection   = LL_USART_DIRECTION_TX_RX
    });
    
    LL_USART_EnableDMAReq_RX    (xres->use_usart);
    LL_USART_EnableDMAReq_TX    (xres->use_usart);
    LL_USART_EnableDirectionTx  (xres->use_usart);
    LL_USART_EnableDirectionRx  (xres->use_usart);
    NVIC_EnableIRQ(USART1_IRQn);
    
    LL_USART_Enable(xres->use_usart);
}


COOK_RECEIPT receipt_USE_USART_1 = 
{
     .cook       = &COOK_LL_SimpleUSART
    
    ,.use_usart  = USART1
    ,.use_gpio   = GPIOA
    ,.use_dma    = DMA1
    
    ,.dma_chTX   = LL_DMA_CHANNEL_4
    ,.dma_chRX   = LL_DMA_CHANNEL_5
    
    ,.gpio_pinTX = LL_GPIO_PIN_9
    ,.gpio_pinRX = LL_GPIO_PIN_10
};

COOK_RECEIPT receipt_USE_USART_3 = 
{
    .cook           = &COOK_LL_SimpleUSART
    
    ,.use_usart     = USART3
    ,.use_gpio      = GPIOA
    ,.use_dma       = DMA1
    
    ,.dma_chTX      = LL_DMA_CHANNEL_4
    ,.dma_chRX      = LL_DMA_CHANNEL_5
    
    ,.gpio_pinTX    = LL_GPIO_PIN_10
    ,.gpio_pinRX    = LL_GPIO_PIN_9
};
