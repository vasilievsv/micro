#ifndef STM32_MOD_WS2812
#define STM32_MOD_WS2812

#include "../micro/facade.h"


#define WS2812B_BUFFER_SIZE     60
#define WS2812B_START_SIZE      2

#define WS2812B_APB1_RCC        RCC_APB1Periph_TIM4
#define WS2812B_APB2_RCC        RCC_APB2Periph_GPIOB

#define WS2812B_AHB_RCC         RCC_AHBPeriph_DMA1

#define WS2812B_GPIO            GPIOB
#define WS2812B_GPIO_PIN        GPIO_Pin_6

#define WS2812B_TIM             TIM4
#define WS2812B_TIM_OCINIT      TIM_OC1Init
#define WS2812B_TIM_OCPRELOAD   TIM_OC1PreloadConfig
#define WS2812B_TIM_DMA_CC      TIM_DMA_CC1
#define WS2812B_TIM_DMA_CCR     (WS2812B_TIM->CCR1)

#define WS2812B_DMA             DMA1
#define WS2812B_DMA_CHANNEL     DMA1_Channel1
#define WS2812B_DMA_IRQ         DMA1_Channel1_IRQn

#define WS2812B_DMA_HANDLER     DMA1_Channel1_IRQHandler
#define WS2812B_DMA_IT_TC       DMA1_IT_TC1
#define WS2812B_DMA_IT_HT       DMA1_IT_HT1

#define WS2812B_IRQ_PRIO        0
#define WS2812B_IRQ_SUBPRIO     0

#define WS2812B_FREQUENCY       24000000
#define WS2812B_PERIOD          30

#define WS2812B_PULSE_HIGH      21
#define WS2812B_PULSE_LOW       9


void ws2812b_SendRGB();
int ws2812b_IsReady();


#define dpinon  GPIOC->BSRR =GPIO_BSRR_BS7
#define dpinoff GPIOC->BSRR =GPIO_BSRR_BR7

void load_empty_buffer();
void testws         (void);
void striprefresh   (void);                     // This function is invoked periodically
void stripset       (int, char, char, char );   // offset  r g b 
void stripall       (char, char, char );        // allstrip on  (r, g, b)
void delay          (int);
void INIT_WS2812    (void);
void sendbyte       (int byte);

#define STRIPLEN        64*3                    // lenght of strop
#define NUMDI           STRIPLEN * 3            // the number of diodes
#define T0H             1                       // time in uS*10
#define T1H             1
#define T0L             1
#define T1L             1
#define RES             50*7
#define TCORR           0
#define FRQCORR         1                       // delay calirate constant

extern char led_buf [];

    
    //
    #define B8(b) ((unsigned char)B8__(HEX__(b)))
    #define HEX__(n) 0x##n##UL
    #define B8__(x)    (((x&0xf0000000UL)?0x01:0) |\
                        ((x&0x0f000000UL)?0x02:0) |\
                        ((x&0x00f00000UL)?0x04:0) |\
                        ((x&0x000f0000UL)?0x08:0) |\
                        ((x&0x0000f000UL)?0x10:0) |\
                        ((x&0x00000f00UL)?0x20:0) |\
                        ((x&0x000000f0UL)?0x40:0) |\
                        ((x&0x0000000fUL)?0x80:0))
                
#endif
