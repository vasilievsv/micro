#include "main.h"

#include "hostx/facade.h"
#include "hostx.api/_core.h"

void SystemClock_Config(void);

int main(void)
{
    SystemClock_Config();
    
    //HOSTX_ProcBind(MEMREAD          , hostapi_MCU_MEMREAD   , 1);
    //HOSTX_ProcBind(MEMWRITE         , hostapi_MCU_MEMWRITE  , 1);
    
    //HOSTX_ProcBind(PROTO_ECHO       , &hostapi_PROTO_ECHO   , 1);
    //HOSTX_ProcBind(PROTO_MODE       , &hostapi_PROTO_MODE   , 1);
    //HOSTX_ProcBind(PROTO_CONNECT    , &hostapi_PROTO_CONNECT, 1);

    //HOSTX_ProcBind(CG_INIT          , &hostapi_CG_INIT      , 1);
    //HOSTX_ProcBind(CG_INFO          , &hostapi_CG_INFO      , 1);
    //HOSTX_ProcBind(CG_BITBLT        , &hostapi_CG_BITBLT    , 1);
    //HOSTX_ProcBind(CG_CLEAR         , &hostapi_CG_CLEAR     , 1);
    //HOSTX_ProcBind(CG_FONT          , &hostapi_CG_FONT      , 1);

    //HOSTX_ProcBind(VM_PAUSE         , &sys_pause            , 13600);
    //HOSTX_ProcBind(VM_RESTART       , &sys_restart          , 1);
    //HOSTX_ProcBind(VM_TERMINATE     , &sys_terminate        , 1);
    
    INTERCOM_Setup();

    loop:while (1)
    {
        //_counter = RTC_GetCounter();
        if (!vm_check_end_programm())
        {
            if (vm_check_end_opcode()) vm_next_opcode();

            vm_execute();
        }
        //_counter = RTC_GetCounter() - _counter;
    }
}

/* ==============   BOARD SPECIFIC CONFIGURATION CODE BEGIN    ============== */
/**
  * @brief  System Clock Configuration
  *         The system Clock is configured as follow : 
  *            System Clock source            = PLL (HSE)
  *            SYSCLK(Hz)                     = 24000000
  *            HCLK(Hz)                       = 24000000
  *            AHB Prescaler                  = 1
  *            APB1 Prescaler                 = 1
  *            APB2 Prescaler                 = 1
  *            HSE Frequency(Hz)              = 8000000
  *            HSE PREDIV1                    = 2
  *            PLLMUL                         = 6
  *            Flash Latency(WS)              = 0
  * @param  None
  * @retval None
  */
void SystemClock_Config(void)
{
    /* Enable HSE oscillator */
    LL_RCC_HSE_Enable();
    while(LL_RCC_HSE_IsReady() != 1)
    {
    };

    /* Main PLL configuration and activation */
    LL_RCC_PLL_ConfigDomain_SYS(LL_RCC_PLLSOURCE_HSE_DIV_2, LL_RCC_PLL_MUL_6);
    LL_RCC_PLL_Enable();
    while(LL_RCC_PLL_IsReady() != 1)
    {
    };

    /* Sysclk activation on the main PLL */
    LL_RCC_SetAHBPrescaler(LL_RCC_SYSCLK_DIV_1);
    LL_RCC_SetSysClkSource(LL_RCC_SYS_CLKSOURCE_PLL);
    while(LL_RCC_GetSysClkSource() != LL_RCC_SYS_CLKSOURCE_STATUS_PLL)
    {
    };

    /* Set APB1 & APB2 prescaler */
    LL_RCC_SetAPB1Prescaler(LL_RCC_APB1_DIV_1);
    LL_RCC_SetAPB2Prescaler(LL_RCC_APB2_DIV_1);

    /* Set systick to 1ms */
    SysTick_Config(24000000 / 1000);

    /* Update CMSIS variable (which can be updated also through SystemCoreClockUpdate function) */
    SystemCoreClock = 24000000;
}
