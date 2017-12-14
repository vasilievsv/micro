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

int hostapi_VM_PING(char *ptr_frame)
{
    //memset(usart_TX_frame32, 0, 31);

    //USART_DMA_Flush();
    
    return 1;
}


int hostapi_VM_TERMINATE(uint32_t *ptr_frame)
{
    return 1;
}

int hostapi_VM_RESTART(uint32_t *ptr_frame)
{
    return 1;
}

///
/// 00-00-00-00
///
int hostapi_VM_MEMREAD(uint32_t *ptr_frame)
{
    //usart_TX_frame32[0]= PROTO_CONNECT;
    return 1;
}

int hostapi_VM_MEMWRITE(uint32_t *ptr_frame)
{
    return 1;
}
