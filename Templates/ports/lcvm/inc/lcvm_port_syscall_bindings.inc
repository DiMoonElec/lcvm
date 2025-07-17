#include "lcvm_port_syscall_handlers.h"

typedef struct
{
  uint16_t SysCallID;
  uint8_t (*SysCallHandler)(void);
} SysCallHandler_t;

static const SysCallHandler_t SysCallHandlers[] = {
    {.SysCallID = 10, .SysCallHandler = user_syscall_10_handler},
    {.SysCallID = 11, .SysCallHandler = user_syscall_11_handler},
};

