#ifndef __LCVM_INTERNAL_API_H__
#define __LCVM_INTERNAL_API_H__

#include <stdint.h>

/* define-ы кодов возврата
  из обработчиков системных запросов */
#define LCVM_SYSCALL_RESULT_OK 0
#define LCVM_SYSCALL_RESULT_PARAM_READ_ERROR 1
#define LCVM_SYSCALL_RESULT_PARAM_VALUE_INVALID 2
#define LCVM_SYSCALL_RESULT_INCORRECT_ID 3

/* Чтение памяти виртуальной машины по адресу, относительно FP */
int8_t lcvm_core_get_local_data(void *buffer, int16_t offset, uint8_t size);

/* Чтение памяти виртуальной машины по абсолютному */
int8_t lcvm_core_ram_set_int8(uint32_t adr, int8_t value);
int8_t lcvm_core_ram_get_int8(uint32_t adr, int8_t *value);

int8_t lcvm_core_ram_set_uint8(uint32_t adr, uint8_t value);
int8_t lcvm_core_ram_get_uint8(uint32_t adr, uint8_t *value);

int8_t lcvm_core_ram_set_int16(uint32_t adr, int16_t value);
int8_t lcvm_core_ram_get_int16(uint32_t adr, int16_t *value);

int8_t lcvm_core_ram_set_uint16(uint32_t adr, uint16_t value);
int8_t lcvm_core_ram_get_uint16(uint32_t adr, uint16_t *value);

#endif
