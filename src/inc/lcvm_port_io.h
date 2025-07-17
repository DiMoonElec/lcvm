#ifndef __LCVM_H__
#define __LCVM_H__

#include <stdint.h>

int8_t lcvm_port_io_action_get(void);
int8_t lcvm_port_io_action_set(void);
void lcvm_port_io_set_default(void);
int lcvm_port_io_link_variable(uint16_t id, uint32_t adr);
void lcvm_port_io_unlink_variables(void);

#endif