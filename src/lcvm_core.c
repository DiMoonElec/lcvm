#include <stdint.h>
#include "lcvm/debug_api.h"
#include "lcvm/internal_api.h"
#include "inc/lcvm_core.h"
#include "inc/lcvm_core_exceptions.h"
#include "inc/lcvm_opcode.h"
#include "inc/lcvm_core_macros.h"
//#include "inc/lcvm_core_memory_access.h"
#include "lcvm_config.h"

typedef struct
{
  union
  {
    uint8_t bytes[4];
    int32_t s32;
    uint32_t u32;
  };
} lcvm_int_element_t;

typedef union
{
  uint8_t bytes[2];
  int16_t s16;
  uint16_t u16;
} lcvm_short_element_t;

typedef struct
{
  union
  {
    uint32_t dwords[2];
    uint64_t u64;
    int64_t s64;
    double d;
  };
} lcvm_long_element_t;

typedef struct
{
  union
  {
    uint8_t bytes[4];
    uint32_t u32;
    int32_t s32;
    uint16_t u16;
    int16_t s16;
    uint8_t u8;
    int8_t s8;
    float f;
  };
} lcvm_dstack_t;

// Стек операций
static lcvm_dstack_t lcvm_OperationStack[LCVM_OPERATION_STACK_SIZE];

// Стек возврата
static uint32_t lcvm_ReturnStack[LCVM_RETURN_STACK_SIZE];

// Исполняемая программа
static const uint8_t *lcvm_ProgramBuffer;

// Память переменных. Тут хранятся обычные и retain-переменные
static uint8_t lcvm_RAMBuffer[LCVM_RAMBUFFER_SIZE];

// Programm counter
static uint32_t lcvm_RegPC;

static uint32_t lcvm_CurrentOpcodeAdr;

// Указатель на начало текущего фрейма
static uint32_t lcvm_RegFP;

// Указатель на вершину стека операций
static int16_t lcvm_sp_op;

// Указатель на вершину стека возврата
static int16_t lcvm_sp_ret;

// Размер программы
static uint32_t lcvm_ProgramBufferSize;

// Код исключения при работе виртуальной машины
static uint8_t lcvm_Exception;

static uint8_t lcvm_State;

//static uint8_t lcvm_debug;

static uint32_t lcvm_instruction_counter;

// Останов виртуальной машины
void lcvm_core_stop(void)
{
  lcvm_Exception = LCVM_EXCEPTION_HALT;
}

// Запуск виртуальной машины
void lcvm_core_run(void)
{
  lcvm_Exception = LCVM_EXCEPTION_NONE;
}

void lcvm_core_load(lcvm_application_t *app)
{
  lcvm_ProgramBuffer = app->Program;
  lcvm_ProgramBufferSize = app->ProgramSize;
}

// Сброс контекста виртуальной машины
void lcvm_core_reset(void)
{
  lcvm_Exception = LCVM_EXCEPTION_NONE;
  lcvm_State = LCVM_CORE_STATUS_RUN;

  lcvm_RegPC = 0; // Счетчик команд
  lcvm_CurrentOpcodeAdr = 0;
  lcvm_RegFP = 0; // Указатель фрейма

  lcvm_sp_op = -1;  // стек операций
  lcvm_sp_ret = -1; // стек возврата

  lcvm_instruction_counter = 0;

  for (int i = 0; i < LCVM_RAMBUFFER_SIZE; i++)
    lcvm_RAMBuffer[i] = 0;
}

void lcvm_core_set_function(uint32_t adr)
{
  lcvm_RegPC = adr;
  lcvm_State = LCVM_CORE_STATUS_RUN;
}

uint32_t lcvm_core_get_instruction_counter(void)
{
  return lcvm_instruction_counter;
}

void lcvm_core_reset_instruction_counter(void)
{
  lcvm_instruction_counter = 0;
}

// Функция записи int8_t в RAM
int8_t lcvm_core_ram_set_int8(uint32_t adr, int8_t value)
{
  if (adr >= LCVM_RAMBUFFER_SIZE) // Проверка на выход за пределы массива
    return -1;

  lcvm_RAMBuffer[adr] = (uint8_t)value;
  return 0;
}

// Функция чтения int8_t из RAM
int8_t lcvm_core_ram_get_int8(uint32_t adr, int8_t *value)
{
  if (adr >= LCVM_RAMBUFFER_SIZE) // Проверка на выход за пределы массива
    return -1;

  *value = (int8_t)lcvm_RAMBuffer[adr];
  return 0;
}

// Функция записи uint8_t в RAM
int8_t lcvm_core_ram_set_uint8(uint32_t adr, uint8_t value)
{
  if (adr >= LCVM_RAMBUFFER_SIZE) // Проверка на выход за пределы массива
    return -1;

  lcvm_RAMBuffer[adr] = value;
  return 0;
}

// Функция чтения uint8_t из RAM
int8_t lcvm_core_ram_get_uint8(uint32_t adr, uint8_t *value)
{
  if (adr >= LCVM_RAMBUFFER_SIZE) // Проверка на выход за пределы массива
    return -1;

  *value = lcvm_RAMBuffer[adr];
  return 0;
}

// Функция записи int16_t в RAM
int8_t lcvm_core_ram_set_int16(uint32_t adr, int16_t value)
{
  if (adr >= (LCVM_RAMBUFFER_SIZE - 1)) // Проверка на выход за пределы массива
    return -1;

  lcvm_RAMBuffer[adr] = (uint8_t)(value & 0xFF);
  lcvm_RAMBuffer[adr + 1] = (uint8_t)((value >> 8) & 0xFF);
  return 0;
}

// Функция чтения int16_t из RAM
int8_t lcvm_core_ram_get_int16(uint32_t adr, int16_t *value)
{
  if (adr >= (LCVM_RAMBUFFER_SIZE - 1)) // Проверка на выход за пределы массива
    return -1;

  *value = (int16_t)(lcvm_RAMBuffer[adr] | (lcvm_RAMBuffer[adr + 1] << 8));
  return 0;
}

// Функция записи uint16_t в RAM
int8_t lcvm_core_ram_set_uint16(uint32_t adr, uint16_t value)
{
  if (adr >= (LCVM_RAMBUFFER_SIZE - 1)) // Проверка на выход за пределы массива
    return -1;

  lcvm_RAMBuffer[adr] = (uint8_t)(value & 0xFF);
  lcvm_RAMBuffer[adr + 1] = (uint8_t)((value >> 8) & 0xFF);
  return 0;
}

// Функция чтения uint16_t из RAM
int8_t lcvm_core_ram_get_uint16(uint32_t adr, uint16_t *value)
{
  if (adr >= (LCVM_RAMBUFFER_SIZE - 1)) // Проверка на выход за пределы массива
    return -1;

  *value = (uint16_t)(lcvm_RAMBuffer[adr] | (lcvm_RAMBuffer[adr + 1] << 8));
  return 0;
}

int8_t lcvm_core_get_local_data(void *buffer, int16_t offset, uint8_t size)
{
  uint32_t index = lcvm_RegFP + offset;

  // Проверка на выход за границы массива lcvm_RAMBuffer
  if (index >= LCVM_RAMBUFFER_SIZE || (index + size) > LCVM_RAMBUFFER_SIZE)
    return -1; // Возврат ошибки при выходе за границы

  // Копирование данных из lcvm_RAMBuffer в buffer
  for (int i = 0; i < size; i++)
    ((uint8_t *)buffer)[i] = lcvm_RAMBuffer[index++];

  return 0; // Успешное выполнение
}

uint8_t *lcvm_core_get_ram_pointer(void)
{
  return lcvm_RAMBuffer;
}

uint32_t lcvm_core_get_ram_size(void)
{
  return LCVM_RAMBUFFER_SIZE;
}

uint32_t *lcvm_core_get_stack_pointer(uint8_t stackID)
{
  switch (stackID)
  {
  case 0:
    return &lcvm_OperationStack[0].u32;

  case 1:
    return lcvm_ReturnStack;

  default:
    return 0;
  }
}

uint32_t lcvm_core_get_stack_size(uint8_t stackID)
{
  switch (stackID)
  {
  case 0:
    return LCVM_OPERATION_STACK_SIZE;

  case 1:
    return LCVM_RETURN_STACK_SIZE;

  default:
    return 0;
  }
}

uint32_t lcvm_core_get_reg_pc(void)
{
  return lcvm_CurrentOpcodeAdr;
}

uint32_t lcvm_core_get_reg_fp(void)
{
  return lcvm_RegFP;
}

int16_t lcvm_core_get_reg_osp(void)
{
  return lcvm_sp_op;
}

int16_t lcvm_core_get_reg_rsp(void)
{
  return lcvm_sp_ret;
}

uint8_t lcvm_core_get_reg_except(void)
{
  return lcvm_Exception;
}

uint8_t lcvm_core_step(void)
{
  static uint8_t opcode;

  // цикл ВМ
#ifndef LCVM_DEBUG
  for (int i = 0; i < LCVM_INSTR_PER_CALL; i++)
  {
#endif
    /*
    if (lcvm_debug)
    {
      if (lcvm_step_callback())
      return;
    }
    */

    // Если регистр PC вышел за пределы программы
    // то устанавливаем RUNTIME ошибку
    if (lcvm_RegPC >= lcvm_ProgramBufferSize)
      LCVM_EXCEPTION(LCVM_EXCEPTION_OUT_OF_PROGRAM);

    // Если состояние ВМ не является RUN
    // то выходим
    if (lcvm_State != LCVM_CORE_STATUS_RUN)
      return lcvm_State;

    // Сохраняем во временную переменную
    // Адрес текущей операции
    lcvm_CurrentOpcodeAdr = lcvm_RegPC;

    // Читаем очередную инструкцию
    opcode = lcvm_ProgramBuffer[lcvm_RegPC++];

    // Увеличиваем счетчик циклов
    lcvm_instruction_counter++;

    // Интерпретатор байт-кода
#include "opcodes/interpreter.inc"
  
#ifndef LCVM_DEBUG
  }
#endif

  return lcvm_State;
}
