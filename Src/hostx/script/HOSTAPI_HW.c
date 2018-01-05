/**
  ******************************************************************************
  * @file    
  * @author  
  * @version V0.0.7
  * @date    11-Aug-2017
  * @brief    
  ******************************************************************************
*/
    #include "../script.h"
    
    /// 
    /// 
    /// 
    /// 00-00 00-00-00-00 00-00
    ///  ^           ^     ^
    int hostapi_MCU_MEMREAD(VM_OPCODE* _cmd)
    { 
        uint32_t    _memAddr= *((uint32_t*)&_cmd->origin);    // откуда 
        uint8_t     _memCnt = *((uint8_t*)&_cmd->origin+4); // сколько
        uint8_t     _size   = _memCnt + 4;                  // общий размер
        
        
        INTERCOM_Write( &_cmd->code  , 1 );
        INTERCOM_Write( &_size       , 1 );
        INTERCOM_Write( &_cmd->origin, 4 );
        INTERCOM_Write( (uint32_t*)_memAddr     , _memCnt );
        
        return 1;
    }
    /// 
    /// 00-00 00-00-00-00 00-00
    ///  ^           ^     ^
    int hostapi_MCU_MEMWRITE(VM_OPCODE *_cmd)
    {
        uint32_t*       _addr = (uint32_t*)&_cmd->origin;
        uint8_t         _size = *((uint8_t*)&_cmd->origin+4);
        
        memcpy(_addr,&_cmd->origin,_size);
        
        INTERCOM_Write(&_cmd->code, 1);
        INTERCOM_Write(&_size, 1);
        INTERCOM_Write(&_cmd->origin, 4);
        
        return 1;
    }
    
