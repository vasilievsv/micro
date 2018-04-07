    #include "../intercom.h"

    ///
    ///
    ///
    #define _CAST(x)  ((IO_CHANNEL*)x)
    
    void IO_CHANNEL_DataOut(void* _io)
    {
        IO_CHANNEL* io = (IO_CHANNEL*)_io;
        DMA_TypeDef* DMAx = (DMA_TypeDef*)io->hw->use_dma;
        
        if( DMA1->ISR & DMA_ISR_TCIF4) 
        {
            LL_DMA_DisableChannel( DMA1, 4);
            
                        
           // memset(&io->stream_OUT, 0, 32);
        }//.Если обмен завершен
        
        if( DMAx->ISR & DMA_ISR_HTIF4) 
        {
            LL_DMA_ClearFlag_HT4 ( DMA1 );
            
        }//.Если передана половина буфера
        
        
        if( DMAx->ISR & DMA_ISR_TEIF4) 
        {
            
        }//.Если произошла ошибка при обмене 
        
    }
    ///
    ///
    ///
    void IO_CHANNEL_DataIn(void* _io)
    {
        IO_CHANNEL*  io     = (IO_CHANNEL*)_io;
        DMA_TypeDef* DMAx   = (DMA_TypeDef*)io->hw->use_dma;
        
        if( DMAx->ISR & DMA_ISR_TCIF5 ) // Если обмен завершен
        {
            IO_STREAM *_pack = (IO_STREAM*)&io->raw_IN;
            
            uint32_t header_crc = _pack->pack_crc;
            uint8_t  header_cfg = _pack->pack_cfg;
            uint16_t header_size= _pack->pack_size;
            uint8_t* ptr_data   = &_pack->origin;
            
            uint32_t  flag    = hxCRC32( ptr_data, 32 - 4) ^ _pack->pack_crc;
            if( flag == 0 ) //0xFFFFFFFFul;
            {
                
            }
            
            SCRIPT_VM_Run(ptr_data, header_size);
            
            INTERCOM_Flush();
            
            LL_DMA_ClearFlag_TC5 ( DMA1 );
            LL_DMA_SetDataLength ( DMA1, 5, 32 );
        }
        
        if( DMAx->ISR & DMA_ISR_HTIF5) 
        {
            LL_DMA_ClearFlag_HT5 ( DMA1 );
        }// Если передана половина буфера
        
        if( DMAx->ISR & DMA_ISR_TEIF5) 
        {
            
        }// Если произошла ошибка при обмене
        
    }
