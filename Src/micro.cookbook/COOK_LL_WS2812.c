/**
  ******************************************************************************
  * @file    
  * @author  Kargapolcev M. E.
  * @version V0.0.0
  * @date    001.12.2016
  * @brief    s2812 stripe rgb leds
  ******************************************************************************
    
    PB6 - as DIN for WS2812
    
    https://geektimes.ru/post/255548/
    https://github.com/Silencer2K/stm32f10x-ws2812b-lib/blob/master/src/ws2812b.c
*/

#include "../micro/cook.h"
#include "../micro/cg/bitmap.h"

    #include "ws2812.h"
    
    char led_buf [NUMDI];   // One chip - three doides[R,G,B]
    int n;
    
    struct __attribute__((packed)) PWM
    {
        uint16_t g[8], r[8], b[8];
    };
    
    #define MIN(a, b)   ((a) < (b)) ? (a) : (b)
    
    typedef struct PWM PWM_t;
    typedef void (SrcFilter_t)(void **, PWM_t **, unsigned *, unsigned);
    
    static volatile int DMABusy;
    static PWM_t        DMABuffer[WS2812B_BUFFER_SIZE];
    static void        *DMASrc;
    static SrcFilter_t *DMAFilter;
    static unsigned     DMACount;
    
    static void RGB2PWM(Color24_t *rgb, PWM_t *pwm)
    {
        /*
        uint8_t r = rgb->r;
        uint8_t g = rgb->g;
        uint8_t b = rgb->b;
        
        uint8_t mask = 128;
        
        int i;
        for (i = 0; i < 8; i++)
        {
            pwm->r[i] = r & mask ? WS2812B_PULSE_HIGH : WS2812B_PULSE_LOW;
            pwm->g[i] = g & mask ? WS2812B_PULSE_HIGH : WS2812B_PULSE_LOW;
            pwm->b[i] = b & mask ? WS2812B_PULSE_HIGH : WS2812B_PULSE_LOW;
            
            mask >>= 1;
        }
        */
    }
    
    static void SrcFilterNull(void **src, PWM_t **pwm, unsigned *count, unsigned size)
    {
        memset(*pwm, 0, size * sizeof(PWM_t));
        *pwm += size;
    }
    
    static void SrcFilterRGB(void **src, PWM_t **pwm, unsigned *count, unsigned size)
    {
        /*
        Color24_t *rgb  = *src;
        PWM_t *p    = *pwm;
        
        *count -= size;
        
        while (size--)
        {
            RGB2PWM(rgb++, p++);
        }
        
        *src = rgb;
        *pwm = p;
        */
    }
    
    static void DMASend(SrcFilter_t *filter, void *src, unsigned count)
    {
        
        if (!DMABusy)
        {
            DMABusy     = 1;
            DMAFilter   = filter;
            DMASrc      = src;
            DMACount    = count;
            
            PWM_t *pwm = DMABuffer;
            PWM_t *end = &DMABuffer[WS2812B_BUFFER_SIZE];
            
            // Start sequence
            SrcFilterNull(NULL, &pwm, NULL, WS2812B_START_SIZE);
            
            // RGB PWM data
            DMAFilter(&DMASrc, &pwm, &DMACount, MIN(DMACount, end - pwm));
            
            // Rest of buffer
            if (pwm < end)
                SrcFilterNull(NULL, &pwm, NULL, end - pwm);
            
            // Start transfer
            
            LL_TIM_EnableCounter(TIM4);
            LL_DMA_SetDataLength(DMA1,1,sizeof(DMABuffer) / sizeof(uint16_t));
            LL_DMA_EnableChannel(DMA1,1);
        }
        
    }
    
    static void DMASendNext(PWM_t *pwm, PWM_t *end)
    {
        if (!DMAFilter)
        {
            // Stop transfer
            LL_TIM_DisableCounter(TIM4);
            LL_DMA_DisableChannel(DMA1,1);
            
            DMABusy = 0;
        }
        else if (!DMACount)
        {
            // Rest of buffer
            SrcFilterNull(NULL, &pwm, NULL, end - pwm);
            
            DMAFilter = NULL;
        }
        else
        {
            // RGB PWM data
            DMAFilter(&DMASrc, &pwm, &DMACount, MIN(DMACount, end - pwm));
            
            // Rest of buffer
            if (pwm < end)
                SrcFilterNull(NULL, &pwm, NULL, end - pwm);
        }
        
    }
    

    
    ///
    ///
    ///
    void COOK_LL_WS2812(COOK_RECEIPT* xres)
    {
        LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_TIM4);
        LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_DMA1);
        LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_GPIOB);
//
// GPIO
//
        LL_GPIO_AF_DisableRemap_TIM4();
        LL_GPIO_SetPinMode (GPIOB, LL_GPIO_PIN_6, LL_GPIO_MODE_ALTERNATE);
        LL_GPIO_SetPinSpeed(GPIOB, LL_GPIO_PIN_6, LL_GPIO_SPEED_FREQ_HIGH);
        LL_GPIO_SetPinPull (GPIOB, LL_GPIO_PIN_6, LL_GPIO_PULL_DOWN);
        
//
// TIMER - Initialize clock
//
    LL_TIM_Init(TIM4, &(LL_TIM_InitTypeDef)
    {
         .Prescaler         = (SystemCoreClock / WS2812B_FREQUENCY) - 1
        ,.CounterMode       = LL_TIM_COUNTERMODE_UP
        //,.RepetitionCounter = 30 - 1                        //autoreload ???
        ,.ClockDivision     = LL_TIM_CLOCKDIVISION_DIV1
    });
    
    // TIMER - Init Output Channel
    LL_TIM_OC_Init(TIM4, 1, &(LL_TIM_OC_InitTypeDef) 
    {
        .OCMode     = LL_TIM_OCMODE_PWM1
        ,.OCState   = LL_TIM_OCSTATE_ENABLE
        ,.OCPolarity= LL_TIM_OCPOLARITY_HIGH
    });
    
    LL_TIM_EnableDMAReq_CC1 (TIM4);
    LL_TIM_OC_EnablePreload (TIM4, 1);
    LL_TIM_OC_SetCompareCH1 (TIM4, 3000); // Register.RCC
    LL_TIM_SetAutoReload    (TIM4, 6000); // Register.ARR
    
    
    LL_TIM_EnableCounter    (TIM4);       // Register SR.EN
    
//
// DMA Initialize channel
//
    LL_DMA_Init(DMA1, LL_DMA_CHANNEL_1, &(LL_DMA_InitTypeDef)
    {
        .Priority                = LL_DMA_PRIORITY_HIGH
        
        ,.Mode                   = LL_DMA_MODE_CIRCULAR
        ,.Direction              = LL_DMA_DIRECTION_MEMORY_TO_PERIPH
        
        ,.PeriphOrM2MSrcAddress  = (uint32_t)&TIM4->CCR1
        ,.PeriphOrM2MSrcIncMode  = LL_DMA_PERIPH_NOINCREMENT
        ,.PeriphOrM2MSrcDataSize = LL_DMA_PDATAALIGN_HALFWORD
        
        ,.MemoryOrM2MDstAddress  = (uint32_t)&DMABuffer
        ,.MemoryOrM2MDstIncMode  = LL_DMA_MEMORY_INCREMENT
        ,.MemoryOrM2MDstDataSize = LL_DMA_PDATAALIGN_HALFWORD
        
        ,.NbData                 = sizeof(DMABuffer) / sizeof(uint16_t)
    });
    
    NVIC_EnableIRQ  (DMA1_Channel1_IRQn);
    NVIC_SetPriority(DMA1_Channel1_IRQn,0);
    
    LL_DMA_EnableChannel(DMA1, 1);
    LL_DMA_EnableIT_HT  (DMA1, 1);
    LL_DMA_EnableIT_TC  (DMA1, 1);
}

int ws2812b_IsReady(void)
{
    return !DMABusy;
}

void ws2812b_SendRGB(Color24_t *rgb, unsigned count)
{
    //DMASend(&SrcFilterRGB, rgb, count);
}

COOK_RECEIPT receipt_ENABLE_WS2812B = 
{
     .cook       = &COOK_LL_WS2812
    
    ,.use_usart  = USART1
    ,.use_gpio   = GPIOA
    ,.use_dma    = DMA1
    
};