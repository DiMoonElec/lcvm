#ifndef __LCVM_CORE_H__
#define __LCVM_CORE_H__

#include <stdint.h>

typedef struct
{
  const uint8_t *Program;
  uint32_t ProgramSize;
} lcvm_application_t;

#define LCVM_CORE_STATUS_RUN 0
#define LCVM_CORE_STATUS_STOP 1
#define LCVM_CORE_STATUS_EXCEPTION 2

uint32_t lcvm_core_get_instruction_counter(void);
void lcvm_core_reset_instruction_counter(void);

void lcvm_core_reset(void);
void lcvm_core_load(lcvm_application_t *app);
void lcvm_core_set_function(uint32_t adr);
uint8_t lcvm_core_step(void);

int8_t lcvm_syscall(uint16_t id);

#endif
