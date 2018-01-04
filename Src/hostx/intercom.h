#ifndef __HOSTX_INTERCOM
#define __HOSTX_INTERCOM
    
    #include "facade.h"
    #include "cookbook.h"
    
    extern void INTERCOM_Write(void *,uint16_t);
    extern void INTERCOM_Setup();
    
    typedef int(*IO_CALLBACK)(void);

    typedef struct STRUCT_IO_STREAM
    {
        uint32_t pack_crc;
        uint16_t pack_size;
        uint8_t  pack_cfg;
        uint8_t  origin;
    
    }IO_STREAM;
    
    
    typedef struct STRUCT_IO_CHANNEL
    {
        uint8_t  cfg;
        //XRESOURCE* cook;
        IO_CALLBACK Handler_TX;
        IO_CALLBACK Handler_RX;
        
    }IO_CHANNEL;
    
#endif
