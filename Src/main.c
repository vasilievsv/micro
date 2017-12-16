#include "main.h"

#include "hostx/facade.h"
#include "hostx.api/_core.h"

void SystemClock_Config(void);


uint8_t foo[] = {0xAA,0xBB,0xCC,0xFF,0xFF,0xFF,0xFF,0xFF};

void _echo()
{
    INTERCOM_Write(&"test",7);
    INTERCOM_Flush();
}


int main(void)
{
    uint32_t T = (uint32_t)&foo;
    SystemClock_Config();
    
    HOSTX_CMD( MEMREAD          , hostapi_MCU_MEMREAD   , 1);
    HOSTX_CMD( MEMWRITE         , hostapi_MCU_MEMWRITE  , 1);
    
    HOSTX_CMD(__USER+3, _echo,1);
    HOSTX_CMD( VM_PAUSE         , &sys_pause            , 150600);
    HOSTX_CMD( VM_RESTART       , &sys_restart          , 1);
    HOSTX_CMD( VM_TERMINATE     , &sys_terminate        , 1);
    
    INTERCOM_Setup();
    
    //vm_set_stream((char[]){__USER+3,VM_PAUSE,VM_RESTART,0});

    loop:while (1)
    {
        HOSTX_VM_Update();
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
