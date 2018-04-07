/**
  ******************************************************************************
  * @file    
  * @author  
  * @version V0.0.0
  * @date    11-Aug-2017
  * @brief    
  ******************************************************************************
*/

#include "../script.h"


////////
// VM регистры
////////
    VM_API*         vm_tableAPI[255];
    VM_API*         r_o_0;  // @object{ ep,func,tick }
    API_NativeFunc  r_f_0;  // @ep - enter point
    void*           t_0;    // временный

    int r_0 = 0;    // Текущий индекс комманды
    int r_1 = 0;    // Счетчик выполнения комманд
    int r_2 = 0;    // Время за которое выполняется комманда
    int r_3 = 0;    // Длинна Потока (колличество комманд)

    unsigned char   vm_stream_0 [32];
    
    
    ///
    ///
    ///
    void stream_execute()
    {
        
    }

    ///
    ///
    ///
    void VM_set_stream(char *ptr_frame)
    {
        //_frame32_cursor = 0;
         memset(&vm_stream_0,0,31);
         memcpy(&vm_stream_0, ptr_frame,31);
        //if(value)
        //{
            r_0 = -1;
            r_3 = 31;

        //}//else Debug.INFO(name+' CgProcStream wrong input data')
    }

    void sys_goto()
    {

    }
    ///
    ///
    ///
    void sys_terminate()
    {
        r_o_0   = 0;
        r_f_0   = 0;
        t_0     = 0;

        r_0 = r_1 = r_2 = r_3 = 0;
        
        memset(&vm_stream_0,0,31);

        //Debug.INFO('terminate')
    }
    ///
    ///
    ///
    void sys_restart()
    {
        r_0 = -1;
        r_1 = 0;

        VM_next_opcode();
    }
    
    void sys_pause  (){ }
    void sys_stop   (){ }

    ///
    ///
    ///
    void VM_next_opcode()
    {
        r_0++; 	// индекс следующего опкода
        r_1=0;	// сбрасываем счетчик

        VM_read_opcode();
    }
    ///
    ///
    ///
    void VM_execute()
    {
        r_1++;
        if(r_f_0 != 0)
            r_f_0(&vm_stream_0[r_0]);

        //
        // PHASE_MOVE_2
        //
        //if(CgProcOpcode.isMoveCommand(t_0))
        //{
            //vm.hostAPI_exec(CgProcOpcode.PHASE_MOVE_2)
        //}
    }
    ///
    ///
    ///
    void VM_read_opcode()
    {
        if(r_0 < r_3)
        {
            r_o_0   = vm_tableAPI[ vm_stream_0[r_0] ];

            if(r_o_0 != 0)
            {
                r_f_0   = r_o_0->func;
                r_2     = r_o_0->tick;

                //
                // +PHASE_MOVE_1
                //
                //if(CgProcOpcode.isMoveCommand(t_0))
                //{
                //    var dir:uint = CgProcOpcode.moveUnpackDir(t_0)

                 //   vm.hostAPI_exec(CgProcOpcode.PHASE_MOVE_1,dir)
                //}


            }//else Debug.ERROR(name+' '+T_WRONG_OPCODE)
        }
    }
///////////////////////////////////////////////////////////////////////////////
/// Обработка завершение выполнения опкода
///////////////////////////////////////////////////////////////////////////////
    int VM_CHECK_end_opcode()
    {
        //если счетчик выполнения >= время выполнения
        if((r_1 >= r_2))
        {
            //
            // PHASE_MOVE_3
            //
            //if(CgProcOpcode.isMoveCommand(t_0))
            //{
            //    vm.hostAPI_exec(CgProcOpcode.PHASE_MOVE_3)
            //}

            return 1;
        }

        return 0;
    }
    ///
    /// Смещение(r_0) равно длинне программы(r_3).
    /// программа закончена
    ///
    int VM_CHECK_end_programm()
    {
        return (r_0 >= r_3)? 1 : 0 ;
    }
    
/// 
/// 
/// 
void HOSTX_ProcWipe()
{
    for (register uint8_t i = 0; i != 255; i++)
        vm_tableAPI[i] = 0;
}

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


inline void SCRIPT_Tick()
{
    if (!VM_CHECK_end_programm())
    {
        if (VM_CHECK_end_opcode()) VM_next_opcode();
        
        VM_execute();
    }
}


///
/// 
///
void HOSTX_ProcRun(uint8_t* _ptr,uint16_t _size)
{
    uint8_t      _cursor = 0;
    VM_OPCODE*   vm_cmd;
    
    uint8_t _flag = 0;
    
    while (_cursor < _size)
    {
        vm_cmd = (VM_OPCODE*)(_ptr + _cursor);
        
        _flag = VM_Call( vm_cmd->code, vm_cmd );
        
        _cursor += (_flag == 1)?vm_cmd->size+2:1;
    }
}

///
///
///
int VM_Call(uint8_t cmd, void* ptr_frame) // ...arg
{
    if (cmd <= 255 && vm_tableAPI[cmd] != 0 && vm_tableAPI[cmd]->func != 0)
    {
        vm_tableAPI[cmd]->func(ptr_frame);
        
        return 1;
    }

    return 0; // hack for frame32 cursor
}
    