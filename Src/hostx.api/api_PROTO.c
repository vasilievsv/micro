/**
  ******************************************************************************
  * @file    
  * @author  
  * @version V0.0.0
  * @date    11-Aug-2017
  * @brief    
  ******************************************************************************
    
// The MIT License (MIT)
//
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

*/

#include "../hostx/facade.h"
    
    
    /// PROTO_SYNC
    /// size: 00-00-00-00
    ///
    int hostapi_PROTO_SYNC(char *ptr_frame)
    {
        //memcpy(usart_TX_frame32, &usart_RX_frame32, 31);
        return 1;
    }
    /// 
    /// 00-00-00-00
    ///
    int hostapi_PROTO_ECHO(char *ptr_frame)
    {
        //memcpy(usart_TX_frame32, &usart_RX_frame32, 31);
        return 1;
    }
    
    ///
    /// 00-00-00-00
    ///
    int hostapi_PROTO_CONNECT(char *ptr_frame)
    {
        //usart_TX_frame32[0]= PROTO_CONNECT;
        
        return 255;
    }
    
    ///
    /// AB-01
    ///
    int hostapi_PROTO_MODE(char *ptr_frame)
    {
        char T = (char)*(ptr_frame+1);
        
        //_radio = T;
        //switch(_radio)
        //{
        //    case RADIO_TRANSMITER : NRF_INIT_simple_Tx (); break;
        //    case RADIO_RECIVIER   : NRF_INIT_simple_Rx (); break;
        //}
        
        return 2;
    }
    ///
    /// 00-00-00-00
    ///
    void get_uid(void)
    {
        int i = 0;
        extern  volatile uint32_t Unique_ID_Low;
        extern  volatile uint32_t Unique_ID_Mid;
        extern  volatile uint32_t Unique_ID_Hig;
        
        //usart_TX_buff(i++, Unique_ID_Low>>24);
        //usart_TX_buff(i++, Unique_ID_Low>>16);
        //usart_TX_buff(i++, Unique_ID_Low>>8);
        //usart_TX_buff(i++, Unique_ID_Low>>0);
        //usart_TX_buff(i++, Unique_ID_Mid>>24);
        //usart_TX_buff(i++, Unique_ID_Mid>>16);
        //usart_TX_buff(i++, Unique_ID_Mid>>8);
        //usart_TX_buff(i++, Unique_ID_Mid>>0);
        //usart_TX_buff(i++, Unique_ID_Hig>>24);
        //usart_TX_buff(i++, Unique_ID_Hig>>16);
        //usart_TX_buff(i++, Unique_ID_Hig>>8);
        //usart_TX_buff(i++, Unique_ID_Hig>>0);
        //usart_TX_buff(i++, END);
    }
