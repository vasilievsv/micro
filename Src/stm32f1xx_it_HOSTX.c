/**
  ******************************************************************************
  * @file    6/11/2017
  * @author  
  * @version 
  * @date    
  * @brief   
  ******************************************************************************

*/
    #include "hostx/facade.h"
    
    //
    // INTERCOM SEND MESSAGE
    //
    void DMA1_Channel4_IRQHandler(void)
    {
        if(_xdma->ISR & DMA_ISR_TCIF4) //.Если обмен завершен
        {
            LL_DMA_DisableChannel(_xdma, _xdma_chTX);
            LL_DMA_ClearFlag_TC4 (_xdma);
            
           //WRITE_REG(DMAx->IFCR, DMA_IFCR_CTCIF4);
            
            memset(&device_bufferTx,0,32);
        } 
        if(_xdma->ISR & DMA_ISR_HTIF4) //.Если передана половина буфера 
        { 
            LL_DMA_ClearFlag_HT4 (_xdma); 
        } 
        if(_xdma->ISR & DMA_ISR_TEIF4) { } //.Если произошла ошибка при обмене
         
    }
    //
    // INTERCOM RECIEVE MESSAGE
    //
    void DMA1_Channel5_IRQHandler (void)
    {
        if(_xdma->ISR & DMA_ISR_TCIF5) // Если обмен завершен 
        {
            if(device_use_CRC == 1) 
            {
                HOSTX_PACK *_pack = (HOSTX_PACK*)&device_bufferRx;
                
                uint32_t header_crc = _pack->pack_crc;
                uint8_t  header_cfg = _pack->pack_cfg;
                uint16_t header_size= _pack->pack_size;
                uint8_t* ptr_data   = &_pack->origin;
                
                //uint32_t  flag    = hxCRC32( ptr_data, 32 - 4) ^ _pack->pack_crc;
                //if( flag == 0 ) //0xFFFFFFFFul;
                //{
                    HOSTX_ProcRun(ptr_data, header_size);
                    INTERCOM_Flush();
                    
                //}
            }
            
            LL_DMA_ClearFlag_TC5 (_xdma);
        }
        
        if(_xdma->ISR & DMA_ISR_HTIF5) { }// Если передана половина буфера  
        if(_xdma->ISR & DMA_ISR_TEIF5) { }// Если произошла ошибка при обмене
    }
    