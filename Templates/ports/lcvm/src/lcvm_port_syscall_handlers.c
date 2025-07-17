#include "lcvm/internal_api.h"
#include "lcvm_port_syscall_handlers.h"

uint8_t user_syscall_10_handler(void)
{
  uint8_t param1 = 0;
  float param2 = 0;

  /* Reading parameter values */
  if (lcvm_core_get_local_data((void *)&param2, -4, sizeof(float)))
  {
    return LCVM_SYSCALL_RESULT_PARAM_READ_ERROR;
  }
  if (lcvm_core_get_local_data((void *)&param1, -5, sizeof(uint8_t)))
  {
    return LCVM_SYSCALL_RESULT_PARAM_READ_ERROR;
  }

  //Code
  
  return LCVM_SYSCALL_RESULT_OK;
}

uint8_t user_syscall_10_handler(void)
{
  uint8_t u8_param1;
  uint32_t u32_param2;
  uint8_t u8_param3;
  uint8_t u8_param4;
  uint8_t u8_param5;

  /* Reading parameter values */
  if (lcvm_core_get_local_data((void *)&u8_param5, -1, sizeof(float)))
  {
    return LCVM_SYSCALL_RESULT_PARAM_READ_ERROR;
  }

  if (lcvm_core_get_local_data((void *)&u8_param4, -2, sizeof(float)))
  {
    return LCVM_SYSCALL_RESULT_PARAM_READ_ERROR;
  }

  if (lcvm_core_get_local_data((void *)&u8_param3, -3, sizeof(float)))
  {
    return LCVM_SYSCALL_RESULT_PARAM_READ_ERROR;
  }

  if (lcvm_core_get_local_data((void *)&u32_param2, -7, sizeof(float)))
  {
    return LCVM_SYSCALL_RESULT_PARAM_READ_ERROR;
  }

  if (lcvm_core_get_local_data((void *)&u8_param1, -8, sizeof(float)))
  {
    return LCVM_SYSCALL_RESULT_PARAM_READ_ERROR;
  }

  //Code
  
  return LCVM_SYSCALL_RESULT_OK;
}
