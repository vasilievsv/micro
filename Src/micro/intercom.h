#ifndef __HOSTX_INTERCOM
#define __HOSTX_INTERCOM
    
    
    #include "facade.h"
    #include "cook.h"
        
    typedef void(*IO_CALLBACK)( void* );

    typedef struct 
    {
        uint32_t pack_crc;
        uint16_t pack_size;
        uint8_t  pack_cfg;
        uint8_t  origin;
    }IO_STREAM;
    
    #pragma anon_unions
    typedef struct 
    {
        uint8_t         flag;
        COOK_RECEIPT*   hw;
        IO_CALLBACK     Handler_TX;
        IO_CALLBACK     Handler_RX;
        
        union
        {
            uint8_t*    raw_IN;
            IO_STREAM*  stream_IN;
        };
        
        union
        {
            uint8_t*    raw_OUT;
            IO_STREAM*  stream_OUT;
        };
        
        
    }IO_CHANNEL;
    
    extern IO_CHANNEL* INTERCOM_GetChannel (uint8_t index);
    extern IO_CHANNEL* INTERCOM_OpenChannel(uint8_t , COOK_RECEIPT*);
    
    extern void INTERCOM_Write(void *,uint16_t);
    extern void INTERCOM_Setup();
#endif
