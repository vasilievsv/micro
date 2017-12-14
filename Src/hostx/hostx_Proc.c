/**
  ******************************************************************************
  * @file    
  * @author  
  * @version V0.0.0
  * @date    11-Aug-2017
  * @brief    
  ******************************************************************************
*/

#include "facade.h"


////////
// VM регистры
////////
    HOSTX_CMD_FUNC*  vm_tableFunction[255];
    HOSTX_CMD_FUNC*  r_o_0;  // @object{ ep,func,tick }
    CMD_PtrFunc            r_f_0;  // @ep - enter point
    void*                  t_0;    // временный

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
    void vm_set_stream(char *ptr_frame)
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

        vm_next_opcode();
    }
    
    void sys_pause	 (){ }
    void sys_stop	 (){ }

    ///
    ///
    ///
    void vm_next_opcode()
    {
        r_0++; 	// индекс следующего опкода
        r_1=0;	// сбрасываем счетчик

        vm_read_opcode();
    }
    ///
    ///
    ///
    void vm_execute()
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
    void vm_read_opcode()
    {
        if(r_0 < r_3)
        {
            r_o_0   = vm_tableFunction[ vm_stream_0[r_0] ];

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
    int vm_check_end_opcode()
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
    int vm_check_end_programm()
    {
        return (r_0 >= r_3)? 1 : 0 ;
    }

    
    
    
    
/// 
/// 
/// 
void HOSTX_ProcWipe()
{
    for (register uint8_t i = 0; i != 255; i++)
        vm_tableFunction[i] = 0;
}

/// 
/// 
/// 
void HOSTX_ProcBind(uint8_t cmd, CMD_PtrFunc ptr, uint32_t time)
{
    // Создаем структуры и сохраняем указатель в таблице    
    // TODO: освобождение памяти free(ptr);
    vm_tableFunction[cmd] = (HOSTX_CMD_FUNC*)malloc(sizeof(HOSTX_CMD_FUNC));
    vm_tableFunction[cmd]->func = ptr;
    vm_tableFunction[cmd]->tick = time;
}

///
/// Парсер
///
void HOSTX_ProcRun(uint8_t* _ptr)
{
    uint8_t _cursor = 0;
    uint8_t _opcode = 0;

    while (_cursor < 32 - 4)
    {
        _opcode = *(_ptr + _cursor);

        _cursor = _cursor + HOSTX_ProcCall( _opcode, _ptr );
    }

}

///
///
///
int HOSTX_ProcCall(uint8_t cmd, uint8_t* ptr_frame) // ...arg
{
    if (cmd <= 255 && vm_tableFunction[cmd] != 0 && vm_tableFunction[cmd]->func != 0)
    {
        return vm_tableFunction[cmd]->func(ptr_frame);
    }

    return 1; // hack for frame32 cursor
}
    