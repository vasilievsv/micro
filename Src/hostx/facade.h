#ifndef __HOSTX_FACADE
#define __HOSTX_FACADE
    
    #include "stdio.h"
    #include "stdint.h"

    #include "stm32f1xx.h"
    #include "stm32f1xx_ll_bus.h"
    #include "stm32f1xx_ll_usart.h"
    #include "stm32f1xx_ll_rcc.h"
    #include "stm32f1xx_ll_gpio.h"
    #include "stm32f1xx_ll_dma.h"
    
    
    #include "_struct.h"

    extern uint32_t hxCRC32(uint8_t *Buf, uint32_t Len);

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

    extern void INTERCOM_Write(void *,uint16_t);
    extern void INTERCOM_Setup();
     
    extern uint8_t  device_bufferTx[];
    extern uint8_t  device_bufferRx[];
    extern uint8_t  device_use_CRC;
    
    extern USART_TypeDef*  _xusart;
    extern DMA_TypeDef*    _xdma;
    extern uint32_t        _xdma_chTX;
    extern uint32_t        _xdma_chRX;
    extern GPIO_TypeDef*   _xgpio;
    extern uint32_t        _xgpio_pinTX;
    extern uint32_t        _xgpio_pinRX;



///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

    extern unsigned char   vm_stream_0 [32];
    extern unsigned char   vm_stream_1 [32];
    extern unsigned char   vm_stream_2 [32];
    
    extern inline void HOSTX_VM_Update();
    extern void HOSTX_CMD  ( uint8_t, API_PtrFunc, uint32_t );
    extern void HOSTX_ProcClear ();
    extern void HOSTX_ProcRun   ( uint8_t* ,uint16_t);
    

    extern int  HOSTX_ProcCall  ( uint8_t ,void*);
    extern int  vm_check_end_programm();
    extern int  vm_check_end_opcode();
    
    extern void vm_execute();
    extern void vm_set_stream(char*);
    extern void vm_next_opcode();
    extern void vm_read_opcode();
    
    extern void sys_goto();
    extern void sys_pause();
    extern void sys_stop();
    extern void sys_restart();
    extern void sys_terminate();
    
#endif
