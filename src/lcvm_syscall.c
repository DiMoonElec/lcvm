#include "lcvm/internal_api.h"
#include "inc/lcvm_runtime.h"
#include "lcvm_port_syscall_bindings.inc"
/***************************************************************/

static uint8_t lcvm_syscall_set_cycle_time(void)
{
  uint16_t value = 0;

  if (lcvm_core_get_local_data((void *)&value, -2, sizeof(uint16_t)))
  {
    return LCVM_SYSCALL_RESULT_PARAM_READ_ERROR;
  }

  lcvm_runtime_set_cycle_time(value);
  return LCVM_SYSCALL_RESULT_OK;
}

/***************************************************************/

int8_t lcvm_syscall(uint16_t id)
{
  uint8_t result;

  // Поиск среди встроенных ID вызовов
  switch (id)
  {
  case 0x01: // Установить период выполнения программы
    return lcvm_syscall_set_cycle_time();
  }

  // Поиск среди пользовательских функций
  for (int i = 0; i < (sizeof(SysCallHandlers) / sizeof(SysCallHandler_t)); i++)
  {
    if (SysCallHandlers[i].SysCallID == id)
    {
      result = SysCallHandlers[i].SysCallHandler();
      return result;
    }
  }

  return LCVM_SYSCALL_RESULT_INCORRECT_ID;
}

/***************************************************************/