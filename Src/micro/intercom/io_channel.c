    #include "../intercom.h"

    ///
    ///
    ///
    #define _CAST(x)  ((IO_CHANNEL*)x)
    
    void IO_CHANNEL_StreamOut(void* _io)
    {
        IO_CHANNEL* io = (IO_CHANNEL*)_io;
        
        if( io->hw->use_dma->ISR & DMA_ISR_TCIF4) 
        {
            LL_DMA_DisableChannel( io->hw->use_dma, io->hw->dma_chTX);
            LL_DMA_ClearFlag_TC4 ( io->hw->use_dma);
            
            memset(&io->stream_OUT,0,32);
        }//.Если обмен завершен
        
        if( io->hw->use_dma->ISR & DMA_ISR_HTIF4) 
        {
            LL_DMA_ClearFlag_HT4 ( io->hw->use_dma);
        }//.Если передана половина буфера
        
        
        if( io->hw->use_dma->ISR & DMA_ISR_TEIF4) 
        {
            
        }//.Если произошла ошибка при обмене 
        
    }
    ///
    ///
    ///
    void IO_CHANNEL_StreamIn(void* _io)
    {
        IO_CHANNEL*  io     = (IO_CHANNEL*)_io;
        DMA_TypeDef* DMAx   = (DMA_TypeDef*)io->hw->use_dma;
        
        if( DMAx->ISR & DMA_ISR_TCIF5) // Если обмен завершен
        {
            //HOSTX_PACK *_pack = (HOSTX_PACK*)&device_bufferRx;
            
            //uint32_t header_crc = _pack->pack_crc;
            //uint8_t  header_cfg = _pack->pack_cfg;
            //uint16_t header_size= _pack->pack_size;
            //uint8_t* ptr_data   = &_pack->origin;
            
            //uint32_t  flag    = hxCRC32( ptr_data, 32 - 4) ^ _pack->pack_crc;
            //if( flag == 0 ) //0xFFFFFFFFul;
            //{
            //HOSTX_ProcRun(ptr_data, header_size);
            //INTERCOM_Flush();
            //}
            
            LL_DMA_ClearFlag_TC5 ( DMAx );
        }
        
        if( DMAx->ISR & DMA_ISR_HTIF5) 
        {
            
        }// Если передана половина буфера
        
        if( DMAx->ISR & DMA_ISR_TEIF5) 
        {
            
        }// Если произошла ошибка при обмене
        
    }
