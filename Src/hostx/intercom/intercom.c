/**
  ******************************************************************************
  * @date    6/11/2017
  * @author  
  * @version 
  * @brief   
  ******************************************************************************

*/
    #include "../intercom.h"
    
    const uint16_t __SIZE_FRAME = sizeof(IO_STREAM);
    
///
/// DEVICE HARDWARE
///
    //IO_CHANNEL *_channels[4];
///
/// DEVICE ATTRIBUTEs
///
    uint8_t  device_use_CRC         = 1;
    
    uint8_t  device_bufferTx[__SIZE_FRAME+32*6];
    uint8_t  device_bufferRx[__SIZE_FRAME+32*6];
    
    IO_STREAM* tx = (IO_STREAM*)&device_bufferTx;
    IO_STREAM* rx = (IO_STREAM*)&device_bufferRx;
    

    /** 
      *
    */
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
    /** 
      * 
     */
    
    void INTERCOM_Write(void *_myData, uint16_t _mySize)
    {
        //memcpy( &tx->origin + tx->pack_size, _myData, _mySize);
        //tx->pack_size += _mySize;
    }
    