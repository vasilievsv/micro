/**
  ******************************************************************************
  * @file    
  * @author  
  * @version V0.0.0
  * @date    7-Apr-2018
  * @brief    
  ******************************************************************************
*/
#include "../script.h"

  
/// 
/// 
/// 
void SCRIPT_BindAPI(uint8_t cmd, API_NativeFunc ptr, uint32_t time)
{
    // Создаем структуры и сохраняем указатель в таблице    
    // TODO: освобождение памяти free(ptr);
    vm_tableAPI[cmd] = (VM_API*)malloc(sizeof(VM_API));
    vm_tableAPI[cmd]->func = ptr;
    vm_tableAPI[cmd]->tick = time;
}

inline void SCRIPT_DoTick()
{
    if (!VM_is_stream_end())
    {
        if (VM_is_opcode_end()) VM_next_opcode();
        
        VM_execute();
    }
}