#ifndef __LCVM_CONFIG_H__
#define __LCVM_CONFIG_H__

//Размер стека операций, элементов
#define LCVM_OPERATION_STACK_SIZE 32

//Размер стека возврата, элементов
#define LCVM_RETURN_STACK_SIZE 256

//Размер ОЗУ, выделенной ВМ
#define LCVM_RAMBUFFER_SIZE 1024

//Кол-во инструкций, которое выполняет ВМ
//при вызове ее процесса lcvm_core_step()
#define LCVM_INSTR_PER_CALL 1024

//Значение по-умолчанию времени цикла программы
#define LCVM_DEFAULT_CYCLE_VALUE_MS 100

#endif
