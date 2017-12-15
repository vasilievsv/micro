#ifndef __STRUCT
#define __STRUCT

    typedef int(*API_PtrFunc)(char *);

    typedef struct HOSTX_STRUCT_API_FUNC
    {
        API_PtrFunc func; //execute point
        uint32_t    tick;
        
    }HOSTX_CMD_FUNC;
    
    typedef struct HOSTX_STRUCT_PROC_OPCODE
    {
        uint8_t  code;
        uint8_t  size;
        uint8_t  origin;
        
    }HOSTX_VM_CMD;

    typedef struct HOSTX_STRUCT_PACK
    {
        uint32_t pack_crc;
        uint16_t pack_size;
        uint8_t  pack_cfg;
        uint8_t  origin; //pointer
        
    }HOSTX_PACK;

#endif