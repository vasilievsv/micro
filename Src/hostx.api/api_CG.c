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

#include "tiny.h"
#include "tiny_opcode.h"
#include "../tiny.CG/video.h"

//  
// FA-08-24-00
//    ^   ^  ^
//    W   H  MODE
//  
int hostapi_CG_INIT(char *ptr_frame)
{
    return 4;
}

//
// FB-00
//     ^ 
//     reserved
//
int hostapi_CG_INFO(char *ptr_frame)
{
    return 2;
}

//
// 00-00-00-00
//
inline char hostapi_CG_FONT(uint32_t *ptr_frame)
{
    Color24_t ColorPixelON =  {0x40,0x40,0x40};
    Color24_t ColorPixelOff = {0x00,0x00,0x00};

    // двигаем на данные
    ptr_frame = (ptr_frame+ 1);

    int _a = (int)ptr_frame;
    int _b1 = get_number(0,_a);
    int _b2 = get_number(1,_a);
    int _b3 = get_number(2,_a);

    //bitmap_to_screen (ColorPixelON, ColorPixelOff, VIDEO_DrawFont(_b1),2);
    //bitmap_to_screen (ColorPixelON, ColorPixelOff, VIDEO_DrawFont(_b2),1);
    //bitmap_to_screen (ColorPixelON, ColorPixelOff, VIDEO_DrawFont(_b3),0);
    
    //striprefresh();
    return 4;
}
    
///
/// HEX: C3-52-80-47-80-42-80
/// 			   ^  ^  ^  ^  ^  ^
///					 t  v  t  v  t  v
inline int hostapi_CG_CLEAR(char *ptr_frame)
{
    // двигаем на данные
    ptr_frame = ptr_frame+( 1 * sizeof(*ptr_frame));
    
    char r  = (char)*(ptr_frame+5);
    char g  = (char)*(ptr_frame+3);
    char b  = (char)*(ptr_frame+1);
    
    for(int i =0; i!=192;i++)
    {
        video_buff_0[i].r = r;
        video_buff_0[i].g = g;
        video_buff_0[i].b = b;
    }
    
    while (!ws2812b_IsReady()); // wait
    ws2812b_SendRGB(video_buff_0,192);
        
    return 6;
}
    
///
/// HEX: 00-C3-[24..0]
/// 			^   ^                                
/// 		 cnt pocode                     
///
inline char hostapi_CG_BITBLT(char *ptr_frame)
{
    char frame_num   = (char)*(ptr_frame+(0 * sizeof(*ptr_frame)));
    
    char r      = 0;
    char g      = 0;
    char b      = 0;
    
    char offset = 0;
    // двигаем на данные
    ptr_frame = (ptr_frame+( 2 * sizeof(*ptr_frame)));
   
    for(int i = 0; i !=8;i++)
    {
        r = (char)*(ptr_frame+2)/8;
        g = (char)*(ptr_frame+1)/8;
        b = (char)*(ptr_frame+0)/8;
        
        ptr_frame = (ptr_frame+3);// двигаем указатель            
        offset = video_mapping_XY(i,frame_num/3) +(frame_num % 3)*64;
        video_buff_0[offset].r = r;
        video_buff_0[offset].g = g;
        video_buff_0[offset].b = b;
    }
    
    //while (!ws2812b_IsReady()); // wait
    ws2812b_SendRGB(video_buff_0,192);
    
    return 255;
}
