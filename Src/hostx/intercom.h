#ifndef __HOSTX_INTERCOM
#define __HOSTX_INTERCOM
    
    #include "facade.h"
    #include "cookbook.h"
    
    
    typedef int(*IO_CALLBACK)( void* );

    typedef struct 
    {
        uint32_t pack_crc;
        uint16_t pack_size;
        uint8_t  pack_cfg;
        uint8_t  origin;
    }IO_STREAM;
    
    typedef struct 
    {
        uint8_t  flag;
        uint8_t* stream_IN;
        uint8_t* stream_OUT;
        
        COOK_RECEIPT*   hw_init_rules;
        
        IO_CALLBACK     Handler_TX;
        IO_CALLBACK     Handler_RX;
        
    }IO_CHANNEL;
    
    extern IO_CHANNEL* INTERCOM_GetChannel   (uint8_t index);
    extern IO_CHANNEL* INTERCOM_CreateChannel(uint8_t , COOK_RECEIPT*);
    
    extern void INTERCOM_Write(void *,uint16_t);
    extern void INTERCOM_Setup();
#endif
