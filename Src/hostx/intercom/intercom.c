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
    extern void IO_CHANNEL_StreamIn (IO_CHANNEL* channel);
    extern void IO_CHANNEL_StreamOut(IO_CHANNEL* channel);
    
    IO_CHANNEL* _channels[4] = NULL;
    uint8_t     _countChannel= 0;
    
    IO_CHANNEL* INTERCOM_GetChannel(uint8_t index)
    {
        return _channels[index];
    }
    ///
    ///
    ///
    IO_CHANNEL* INTERCOM_CreateChannel(uint8_t index, COOK_RECEIPT* _receipt)
    {
        _channels[index] = (IO_CHANNEL*)malloc(sizeof(IO_CHANNEL));
        
        _channels[index]->flag      = 0xFF;
        _channels[index]->stream_IN = (uint8_t*)malloc(32*sizeof(uint8_t));
        _channels[index]->stream_OUT= (uint8_t*)malloc(32*sizeof(uint8_t));
        
        _channels[index]->Handler_RX=&IO_CHANNEL_StreamIn;
        _channels[index]->Handler_TX=&IO_CHANNEL_StreamIn;
        
        COOK_HW( _receipt );
        
        return _channels[index];
    }
    ///
    ///
    ///
    void INTERCOM_Flush()
    {
        /*
        tx->pack_crc    = hxCRC32( &tx->origin, tx->pack_size);
        tx->pack_cfg    = 0xFF;
        tx->pack_size  += sizeof(HOSTX_PACK)-1; // size of frame
        
        LL_DMA_SetDataLength (_xdma, _xdma_chTX, tx->pack_size );
        LL_DMA_EnableChannel (_xdma, _xdma_chTX);
    */
    }
    ///
    ///
    ///
    void INTERCOM_Write(void *_myData, uint16_t _mySize)
    {
        //memcpy( &tx->origin + tx->pack_size, _myData, _mySize);
        //tx->pack_size += _mySize;
    }
    