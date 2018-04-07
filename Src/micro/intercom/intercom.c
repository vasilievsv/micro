/**
  ******************************************************************************
  * @date    6/11/2017
  * @author  
  * @version 
  * @brief   
  ******************************************************************************
  
  
  
  
*/
    #include "../intercom.h"
    
    //TODO: Сильная связанность с IO_CHANNEL
    extern void IO_CHANNEL_DataIn (void* channel);
    extern void IO_CHANNEL_DataOut(void* channel);
    
    volatile IO_CHANNEL* _channels[4] = NULL;
    uint8_t              _countChannel= 0;
    
    ///
    ///
    ///
    IO_CHANNEL* INTERCOM_GetChannel(uint8_t index)
    {
        IO_CHANNEL* T = _channels[index];
        return  T;
    }
    
    ///
    ///
    ///
    IO_CHANNEL* INTERCOM_OpenChannel(uint8_t index, COOK_RECEIPT* _receipt)
    {
        _channels[index]         = (IO_CHANNEL*)malloc(sizeof(IO_CHANNEL));
        
        
        _channels[index]->flag   = 0xFF;
        _channels[index]->raw_IN = (uint8_t*)malloc(32*sizeof(uint8_t));
        _channels[index]->raw_OUT= (uint8_t*)malloc(32*sizeof(uint8_t));
        
        _channels[index]->Handler_RX= &IO_CHANNEL_DataIn;
        _channels[index]->Handler_TX= &IO_CHANNEL_DataOut;
        
        //TODO: Абстракция для инициализации перефирии
        _receipt->dma_p2m_dst = (uint32_t)&_channels[index]->raw_IN;
        _receipt->dma_p2m_src = (uint32_t)&_receipt->use_usart->DR;
        
        _receipt->dma_m2p_dst = (uint32_t)&_channels[index]->raw_OUT;
        _receipt->dma_m2p_src = (uint32_t)&_receipt->use_usart->DR;
        
        COOK_HW( _receipt );
    }
    
    ///
    ///
    ///
    IO_STREAM __frame32;
    void INTERCOM_Write(void *_myData, uint16_t _mySize)
    {
        memcpy( &__frame32.origin + __frame32.pack_size, _myData, _mySize);
        __frame32.pack_size += _mySize;
    }
    
    ///
    ///
    ///

    void INTERCOM_Flush()
    {
        LL_DMA_ClearFlag_TC4 ( DMA1);
        LL_DMA_SetDataLength ( DMA1, 4, 32 );
        LL_DMA_EnableChannel ( DMA1, 4);
    }
    