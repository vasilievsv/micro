typedef int(*CMD_PtrFunc)(char *);

typedef struct  STRUCT_HOSTX_CMD_FUNCTION
{
    CMD_PtrFunc func; //execute point
    uint32_t    tick;
}HOSTX_CMD_FUNC;

typedef struct STRUCT_HOSTX_COMMAND
{
    uint8_t  opcode;
    uint8_t  size;
    uint8_t  origin;
}HOSTX_COMMAND;

typedef struct STRUCT_HOSTX_PACK
{
    uint32_t pack_crc;
    uint8_t  pack_cfg;
    uint16_t pack_size;
    uint8_t  origin; //pointer
}HOSTX_PACK;
