#include "main.h"

#include "micro/cook.h"
#include "micro/intercom.h"
#include "micro/script.h"

extern COOK_RECEIPT  receipt_ENABLE_DWT;
extern COOK_RECEIPT  receipt_ENABLE_USART1;
extern COOK_RECEIPT  receipt_ENABLE_NRF24L01;
extern COOK_RECEIPT  receipt_ENABLE_CRC32;
extern COOK_RECEIPT  receipt_ENABLE_WS2812B;
extern COOK_RECEIPT  receipt_SystemClock;

int main(void)
{
    COOK_HW( &receipt_SystemClock);
    COOK_HW( &receipt_ENABLE_CRC32);
    COOK_HW( &receipt_ENABLE_DWT);
    COOK_HW( &receipt_ENABLE_WS2812B);
    
    SCRIPT_BindAPI( VM_PAUSE        , &sys_pause       , 150600);
    SCRIPT_BindAPI( VM_RESTART      , &sys_restart     , 1);
    SCRIPT_BindAPI( VM_TERMINATE    , &sys_terminate   , 1);
    
    //INTERCOM_OpenChannel( 0, &receipt_ENABLE_USART1 );
    //INTERCOM_OpenChannel( 1, &receipt_ENABLE_NRF24L01 );
    //INTERCOM_OpenChannel( 2, &receipt_DUMMY );
    
    loop:while(1)
    {
        //SCRIPT_DoTick();
    }
}

void DMA1_Channel4_IRQHandler(void)
{ 
    IO_CHANNEL *temp = INTERCOM_GetChannel(0);
    //temp->Handler_TX(temp);
}

void DMA1_Channel5_IRQHandler(void)
{ 
    IO_CHANNEL *T = INTERCOM_GetChannel(0);
    
    T->Handler_RX(T);
}
