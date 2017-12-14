/**
  ******************************************************************************
  * @file    
  * @author  
  * @version V0.0.7
  * @date    11-Aug-2017
  * @brief    
  ******************************************************************************
*/
    #include "_core.h"
    #include "../hostx/facade.h"
    
    ///
    /// 
    /// 
    /// 00-00 00-00-00-00 00-00
    ///  ^           ^     ^
    int hostapi_MCU_MEMREAD(HOSTX_PACK* ptr_frame)
    {
        //_packRX+=0; uint8_t     _opcode   = *(uint8_t*)_packRX;
        //_packRX+=1; uint8_t     _dsize    = *_packRX;
        //_packRX+=1; uint32_t    _baseAddr = *(uint32_t*)_packRX;
        //_packRX+=4; uint8_t     _size     = *_packRX;
        
        //INTERCOM_Send( (uint32_t*)(_baseAddr), _size );
        
        return 8+1;
    }
    /// 
    /// 00-00 00-00-00-00 00-00
    ///  ^           ^     ^
    int hostapi_MCU_MEMWRITE(HOSTX_PACK *ptr_frame)
    {
        //memcpy(usart_TX_frame32, &usart_RX_frame32, 31);
        return 1;
    }
    
