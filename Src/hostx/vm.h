#ifndef __HOSTX_VM
#define __HOSTX_VM

    #include "facade.h"
    #include "vm/_core.h"

    typedef int(*API_NativeFunc)(char *);

    typedef struct STRUCT_VM_API
    {
        API_NativeFunc func;
        uint32_t    tick;
        
    }VM_API;
    
    typedef struct STRUCT_VM_OPCODE
    {
        uint8_t  code;
        uint8_t  size;
        uint8_t  origin;
        
    }VM_OPCODE;


    extern unsigned char   vm_stream_0 [32];
    extern unsigned char   vm_stream_1 [32];
    extern unsigned char   vm_stream_2 [32];

    extern inline void VM_Update();
    extern void VM_BindAPI  ( uint8_t, API_NativeFunc, uint32_t );
    extern void HOSTX_ProcClear ();
    extern void HOSTX_ProcRun   ( uint8_t* ,uint16_t);


    extern int  VM_Call  ( uint8_t ,void*);
    extern int  VM_CHECK_end_program();
    extern int  VM_CHECK_end_opcode();
    extern void VM_execute();
    extern void VM_set_stream(char*);
    extern void VM_next_opcode();
    extern void VM_read_opcode();

    extern void sys_goto();
    extern void sys_pause();
    extern void sys_stop();
    extern void sys_restart();
    extern void sys_terminate();

#endif