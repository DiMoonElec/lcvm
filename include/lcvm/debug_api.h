#ifndef __LCVM_DEBUG_API_H__
#define __LCVM_DEBUG_API_H__

#include <stdint.h>

//Регистра PC - счетчтк команд
uint32_t lcvm_core_get_reg_pc(void);

//Регистр FP - указатель на фрейм
uint32_t lcvm_core_get_reg_fp(void);

//Регистр OSP - указатель на стек операций
int16_t lcvm_core_get_reg_osp(void);

//Регистр OSP - указатель на стек возврата
int16_t lcvm_core_get_reg_rsp(void);

//Регистр Except - код исключения
uint8_t lcvm_core_get_reg_except(void);

// Получить размер стека
uint32_t lcvm_core_get_stack_size(uint8_t stackID);

//Получить указатель на начало буфера стека
uint32_t *lcvm_core_get_stack_pointer(uint8_t stackID);

//Получить размер памяти данных
uint32_t lcvm_core_get_ram_size(void);

//Получить указатель на начало области памяти данных
uint8_t *lcvm_core_get_ram_pointer(void);


#endif
