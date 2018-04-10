#include "stm32f10x.h"
#include "stm32f10x_spi.h"

#include "nrf24l01.h"

u8 TxBuf[32]={0};

unsigned int sta;
RCC_ClocksTypeDef   RCC_Clocks;
ErrorStatus         HSEStartUpStatus;

unsigned char TX_ADDRESS        [TX_ADR_WIDTH]  = {0xE7,0xE7,0xE7,0xE7,0xE7}; // Define a static TX address
unsigned char nrf_RX_frame32    [TX_PLOAD_WIDTH];
unsigned char nrfx_TX_buf       [TX_PLOAD_WIDTH];
unsigned char flag;
unsigned char rx_com_buffer[10];
unsigned char tx_com_buffer[10];
unsigned char accept_flag;

// SPI(nRF24L01) commands
    #define RF_READ_REG     0x00  // Define read command to register
    #define RF_WRITE_REG    0x20  // Define write command to register
    #define RD_RX_PLOAD     0x61  // Define RX payload register address
    #define WR_TX_PLOAD     0xA0  // Define TX payload register address
    #define FLUSH_TX        0xE1  // Define flush TX register command
    #define FLUSH_RX        0xE2  // Define flush RX register command
    #define REUSE_TX_PL     0xE3  // Define reuse TX payload register command
    #define NOP             0xFF  // Define No Operation, might be used to read status register


    #define  RX_DR  ((sta>>6)&0X01)
    #define  TX_DS  ((sta>>5)&0X01)
    #define  MAX_RT  ((sta>>4)&0X01)


    //Chip Enable Activates RX or TX mode
    #define CE_H()   GPIOC->BSRR =GPIO_BSRR_BS3 
    #define CE_L()   GPIOC->BSRR =GPIO_BSRR_BR3


    //SPI Chip Select
    #define CSN_H()  GPIOC->BSRR =GPIO_BSRR_BS2
    #define CSN_L()  GPIOC->BSRR =GPIO_BSRR_BR2


    //http://we.easyelectronics.ru/Radio/radiomodul-nrf24l01-bystryy-start.html
    #define Bit(bit)                (1<<(bit))
    #define ClearBit(reg, bit)      reg &= (~(1<<(bit)))
    #define SetBit(reg, bit)        reg |= (1<<(bit))
    #define BitIsClear(reg, bit)    ((reg & (1<<(bit))) == 0)
    #define BitIsSet(reg, bit)      ((reg & (1<<(bit))) != 0)
    #define InvBit(reg, bit)        reg ^= (1<<(bit))

    void Delay_us(unsigned int  n) 
    {
      u32 i;       
      while(n--){i=2; while(i--);} // WTF??? todo: rewrite this
    }


/*******************************************************************************
* Function Name   : SPI1_RW
* Description : Sends a byte through the SPI interface and return the byte
*                received from the SPI bus.
* Input       : byte : byte to send.
* Output       : None
* Return       : The value of the received byte.
*******************************************************************************/
    u8 SPI1_readWrite(u8 byte)
    {
        /* Loop while DR register in not emplty */
        while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);
        /* Send byte through the SPI1 peripheral */
        SPI_I2S_SendData(SPI1, byte);
        /* Wait to receive a byte */
        while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) == RESET);
        /* Return the byte read from the SPI bus */
        return SPI_I2S_ReceiveData(SPI1);
    }

    unsigned char SPI1_readWriteReg(unsigned char reg, unsigned char value)
    {
        unsigned char status;
        CSN_L();
        // select register 
        status = SPI1_readWrite(reg);
        // set value
        SPI1_readWrite(value);
        CSN_H();
        return(status);
    }

    void CE20 () {CE_H(); Delay_us(20); CE_L();}

    void spi_pin_init () 
    {
        RCC->APB2ENR    |=  RCC_APB2ENR_IOPCEN;  //
        GPIOC->CRL      |=  GPIO_CRL_MODE2_0;    // SCN is
        GPIOC->CRL      &= ~GPIO_CRL_CNF2;       // PC2 pin
        GPIOC->CRL      |=  GPIO_CRL_MODE3_0;    // CE is
        GPIOC->CRL      &= ~GPIO_CRL_CNF3;       // PC3 pin
    };

    void NRF_INIT_simple_Tx ()
    {
        spi_pin_init ();
        CE_H();
        SPI1_readWriteReg (NRF_WRITE_REG + CONFIG, 0x0e);
        Delay_us(150);
        SPI1_readWriteReg (NRF_WRITE_REG + RX_PW_P0, 0x20);
        CE20 ();
    }

    void NRF_INIT_simple_Rx ()
    {
        //int data;
        spi_pin_init ();
        CE_H();
        SPI1_readWriteReg (NRF_WRITE_REG + CONFIG, 0x0f);
        Delay_us(150);
        SPI1_readWriteReg (NRF_WRITE_REG + RX_PW_P0, 0x20);
        CE20 ();
        CE_H();
    }

    unsigned char SPI1_readReg(unsigned char reg)
    {
      unsigned char reg_val;
        CSN_L();
        SPI1_readWrite(reg);
        reg_val = SPI1_readWrite(0);
        CSN_H();
        return(reg_val);
    }


    unsigned char SPI1_readBuf(unsigned char reg,unsigned char *pBuf, unsigned char bytes)
    {
        unsigned char status,i;
        CSN_L();
        // Select register to write to and read status byte
        status = SPI1_readWrite(reg);
        for(i=0;i<bytes;i++)
            pBuf[i] = SPI1_readWrite(0);
        CSN_H();
        return(status);
    }


    unsigned char SPI1_writeBuf(unsigned char reg, unsigned char *pBuf, unsigned char bytes)
    {
        unsigned char status,i;
        CSN_L();
        // Select register to write to and read status byte
        status = SPI1_readWrite(reg);
        for(i=0; i<bytes; i++) // then write all byte in buffer(*pBuf)
        	SPI1_readWrite(*pBuf++);
        CSN_H();
        return(status);
    }

    //
    // nrf_simple_tx
    //
    void nrf_simple_tx () 
    {
        CSN_L();
        SPI1_readWriteReg(NRF_WRITE_REG + STATUS, 0x70);
        //nrfx_TX_buf[0]=0x4D;
        //nrfx_TX_buf[1]=0x52;
        //nrfx_TX_buf[2]=0x43;
        //nrfx_TX_buf[3]=0x55;
        SPI1_writeBuf (WR_TX_PLOAD, nrfx_TX_buf, TX_PLOAD_WIDTH);
        CSN_H();
        CE20();
    }


    void nrf_simple_rx () 
    {
    
        CE_H();
        Delay_us(1000);
        SPI1_readBuf(RD_RX_PLOAD, nrf_RX_frame32, 0x20);
    
    }


    void RX_Mode(void)
    {
        CE_L();
        SPI1_writeBuf(NRF_WRITE_REG + RX_ADDR_P0, TX_ADDRESS, TX_ADR_WIDTH);
        SPI1_readWriteReg(NRF_WRITE_REG + EN_AA, 0x01);
        // Enable Auto.Ack:Pipe0
        SPI1_readWriteReg(NRF_WRITE_REG + EN_RXADDR, 0x01); // Enable Pipe0
        SPI1_readWriteReg(NRF_WRITE_REG + RF_CH, 40);
        // Select RF channel 40
        SPI1_readWriteReg(NRF_WRITE_REG + RX_PW_P0, TX_PLOAD_WIDTH);
        SPI1_readWriteReg(NRF_WRITE_REG + RF_SETUP, 0x07);
        SPI1_readWriteReg(NRF_WRITE_REG + CONFIG, 0x0f);
        // Set PWR_UP bit, enable CRC(2 bytes)
        //& Prim:RX. RX_DR enabled..
        CE_H(); // Set CE pin high to enable RX device
        // This device is now ready to receive one packet of 16 bytes payload from a TX device
        //sending to address
        // '3443101001', with auto acknowledgment, retransmit count of 10, RF channel 40 and
        //datarate = 2Mbps.
    }


    void TX_Mode(unsigned char * BUF)
    {
        CE_L();  //GPIO_ResetBits(GPIOE,GPIO_Pin_1);//CE=0
        SPI1_writeBuf(NRF_WRITE_REG + TX_ADDR, TX_ADDRESS, TX_ADR_WIDTH);
        SPI1_writeBuf(NRF_WRITE_REG + RX_ADDR_P0, TX_ADDRESS, TX_ADR_WIDTH);
        SPI1_writeBuf(WR_TX_PLOAD, BUF, TX_PLOAD_WIDTH); // Writes data to TX payload
        SPI1_readWriteReg(NRF_WRITE_REG + EN_AA, 0x01);
        // Enable Auto.Ack:Pipe0
        SPI1_readWriteReg(NRF_WRITE_REG + EN_RXADDR, 0x01); // Enable Pipe0
        SPI1_readWriteReg(NRF_WRITE_REG + SETUP_RETR, 0x1a); // 500us + 86us, 10 retrans...
        SPI1_readWriteReg(NRF_WRITE_REG + RF_CH, 40);
        // Select RF channel 40
        SPI1_readWriteReg(NRF_WRITE_REG + RF_SETUP, 0x07);
        // TX_PWR:0dBm, Datarate:2Mbps,
//      LNA:HCURR
        SPI1_readWriteReg(NRF_WRITE_REG + CONFIG, 0x0e);
        // Set PWR_UP bit, enable CRC(2 bytes)
        //& Prim:TX. MAX_RT & TX_DS enabled..
        CE_H(); //GPIO_SetBits(GPIOE,GPIO_Pin_1); // Set CE pin high 
    }

    void INIT_NRF24L01(void)
    {
        u8 buf[5]={0};
        spi_pin_init ();
        
        Delay_us(100);
        CE_L();    // chip enable
        //CSN_H();   // Spi disable 
        SPI1_readBuf(TX_ADDR, buf, TX_ADR_WIDTH);
    }

    void init_io(void)
    {
        CE_L();
        CSN_H();
        RX_Mode();
    }
