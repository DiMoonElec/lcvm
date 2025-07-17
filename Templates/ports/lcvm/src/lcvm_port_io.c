#include "lcvm/internal_api.h"
#include <string.h>

/* Driver Headers */
#include "digital_inputs.h"
#include "digital_outputs.h"
#include "analog_inputs.h"
#include "rtc.h"
#include "ftime.h"

#define DI_COUNT 12
#define DO_COUNT 8
#define AIN_COUNT 4
#define USER_LED_COUNT 1

typedef struct
{
  uint8_t enabled;
  uint32_t addr;
} VarBinding_t;

typedef struct
{
  VarBinding_t digital_in[DI_COUNT];
  VarBinding_t digital_out[DO_COUNT];
  VarBinding_t ain_code[AIN_COUNT];
  VarBinding_t user_led[USER_LED_COUNT];
  VarBinding_t rtc[7]; // weekday, sec, min, hour, day, month, year
} IoBindings;

static IoBindings bindings;

enum RtcIndex
{
  RTC_WEEKDAY = 0,
  RTC_SEC,
  RTC_MIN,
  RTC_HOUR,
  RTC_DAY,
  RTC_MONTH,
  RTC_YEAR
};

static void bind_variable(VarBinding_t *var, uint32_t addr)
{
  var->enabled = 1;
  var->addr = addr;
}

/*
  Unbinding all resources from variables
  Called by the Runtime during program loading.
*/
void lcvm_port_io_unlink_variables(void)
{
  memset(&bindings, 0, sizeof(bindings));
}

/*
  Binding a resource ID to a project variable address
  Called by the Runtime during program loading.
*/
int lcvm_port_io_link_variable(uint16_t id, uint32_t addr)
{
  switch (id)
  {
  case 1:
    bind_variable(&bindings.digital_in[0], addr);
    break;
  case 2:
    bind_variable(&bindings.digital_in[1], addr);
    break;
  case 3:
    bind_variable(&bindings.digital_in[2], addr);
    break;
  case 4:
    bind_variable(&bindings.digital_in[3], addr);
    break;
  case 5:
    bind_variable(&bindings.digital_in[4], addr);
    break;
  case 6:
    bind_variable(&bindings.digital_in[5], addr);
    break;
  case 7:
    bind_variable(&bindings.digital_in[6], addr);
    break;
  case 8:
    bind_variable(&bindings.digital_in[7], addr);
    break;
  case 9:
    bind_variable(&bindings.digital_in[8], addr);
    break;
  case 10:
    bind_variable(&bindings.digital_in[9], addr);
    break;
  case 11:
    bind_variable(&bindings.digital_in[10], addr);
    break;
  case 12:
    bind_variable(&bindings.digital_in[11], addr);
    break;

  case 21:
    bind_variable(&bindings.digital_out[0], addr);
    break;
  case 22:
    bind_variable(&bindings.digital_out[1], addr);
    break;
  case 23:
    bind_variable(&bindings.digital_out[2], addr);
    break;
  case 24:
    bind_variable(&bindings.digital_out[3], addr);
    break;
  case 25:
    bind_variable(&bindings.digital_out[4], addr);
    break;
  case 26:
    bind_variable(&bindings.digital_out[5], addr);
    break;
  case 27:
    bind_variable(&bindings.digital_out[6], addr);
    break;
  case 28:
    bind_variable(&bindings.digital_out[7], addr);
    break;

  case 50:
    bind_variable(&bindings.rtc[RTC_WEEKDAY], addr);
    break;
  case 51:
    bind_variable(&bindings.rtc[RTC_SEC], addr);
    break;
  case 52:
    bind_variable(&bindings.rtc[RTC_MIN], addr);
    break;
  case 53:
    bind_variable(&bindings.rtc[RTC_HOUR], addr);
    break;
  case 54:
    bind_variable(&bindings.rtc[RTC_DAY], addr);
    break;
  case 55:
    bind_variable(&bindings.rtc[RTC_MONTH], addr);
    break;
  case 56:
    bind_variable(&bindings.rtc[RTC_YEAR], addr);
    break;

  case 81:
    bind_variable(&bindings.ain_code[0], addr);
    break;
  case 82:
    bind_variable(&bindings.ain_code[1], addr);
    break;
  case 83:
    bind_variable(&bindings.ain_code[2], addr);
    break;
  case 84:
    bind_variable(&bindings.ain_code[3], addr);
    break;

  case 128:
    bind_variable(&bindings.user_led[0], addr);
    break;

  default:
    return -1;
  }
  return 0;
}

/*
  Set output signals to their default state.  
  Called by the Runtime during firmware initialization and program shutdown.
*/
void lcvm_port_io_set_default(void)
{
  WRITE_DOUT1(0);
  WRITE_DOUT2(0);
  WRITE_DOUT3(0);
  WRITE_DOUT4(0);
  WRITE_DOUT5(0);
  WRITE_DOUT6(0);
  WRITE_DOUT7(0);
  WRITE_DOUT8(0);
  USER_LED0(0);
}

/*
  Read input signals into Input variables.  
  Called by the Runtime before entering the loop() function.
*/
int8_t lcvm_port_io_action_get(void)
{
  // Чтение дискретных входов
#define HANDLE_DIN(binding, read_macro)                        \
  if ((binding).enabled)                                       \
  {                                                            \
    if (lcvm_core_ram_set_uint8((binding).addr, read_macro())) \
      return -1;                                               \
  }

  HANDLE_DIN(bindings.digital_in[0], READ_DIN1);
  HANDLE_DIN(bindings.digital_in[1], READ_DIN2);
  HANDLE_DIN(bindings.digital_in[2], READ_DIN3);
  HANDLE_DIN(bindings.digital_in[3], READ_DIN4);
  HANDLE_DIN(bindings.digital_in[4], READ_DIN5);
  HANDLE_DIN(bindings.digital_in[5], READ_DIN6);
  HANDLE_DIN(bindings.digital_in[6], READ_DIN7);
  HANDLE_DIN(bindings.digital_in[7], READ_DIN8);
  HANDLE_DIN(bindings.digital_in[8], READ_DIN9);
  HANDLE_DIN(bindings.digital_in[9], READ_DIN10);
  HANDLE_DIN(bindings.digital_in[10], READ_DIN11);
  HANDLE_DIN(bindings.digital_in[11], READ_DIN12);

#undef HANDLE_DIN

// Чтение аналоговых входов
#define HANDLE_AIN(binding, value)                       \
  if ((binding).enabled)                                 \
  {                                                      \
    if (lcvm_core_ram_set_uint16((binding).addr, value)) \
      return -1;                                         \
  }

  HANDLE_AIN(bindings.ain_code[0], AnalogInputs_CodeRead(1));
  HANDLE_AIN(bindings.ain_code[1], AnalogInputs_CodeRead(2));
  HANDLE_AIN(bindings.ain_code[2], AnalogInputs_CodeRead(3));
  HANDLE_AIN(bindings.ain_code[3], AnalogInputs_CodeRead(4));

#undef HANDLE_AIN

  ftime_t t;
  CounterToFtime(rtc_counter_get(), &t);

  if (bindings.rtc[RTC_WEEKDAY].enabled && lcvm_core_ram_set_uint8(bindings.rtc[RTC_WEEKDAY].addr, t.weekday))
    return -1;
  if (bindings.rtc[RTC_SEC].enabled && lcvm_core_ram_set_uint8(bindings.rtc[RTC_SEC].addr, t.second))
    return -1;
  if (bindings.rtc[RTC_MIN].enabled && lcvm_core_ram_set_uint8(bindings.rtc[RTC_MIN].addr, t.minute))
    return -1;
  if (bindings.rtc[RTC_HOUR].enabled && lcvm_core_ram_set_uint8(bindings.rtc[RTC_HOUR].addr, t.hour))
    return -1;
  if (bindings.rtc[RTC_DAY].enabled && lcvm_core_ram_set_uint8(bindings.rtc[RTC_DAY].addr, t.day))
    return -1;
  if (bindings.rtc[RTC_MONTH].enabled && lcvm_core_ram_set_uint8(bindings.rtc[RTC_MONTH].addr, t.month))
    return -1;
  if (bindings.rtc[RTC_YEAR].enabled && lcvm_core_ram_set_uint16(bindings.rtc[RTC_YEAR].addr, t.year))
    return -1;

  return 0;
}

/*
  Set output signals based on the values of Output variables.  
  Called by the Runtime after exiting the loop() function.
*/
int8_t lcvm_port_io_action_set(void)
{
  uint8_t val;

#define HANDLE_DOUT(binding, write_macro)              \
  if ((binding).enabled)                               \
  {                                                    \
    if (lcvm_core_ram_get_uint8((binding).addr, &val)) \
      return -1;                                       \
    write_macro(val);                                  \
  }

  HANDLE_DOUT(bindings.digital_out[0], WRITE_DOUT1);
  HANDLE_DOUT(bindings.digital_out[1], WRITE_DOUT2);
  HANDLE_DOUT(bindings.digital_out[2], WRITE_DOUT3);
  HANDLE_DOUT(bindings.digital_out[3], WRITE_DOUT4);
  HANDLE_DOUT(bindings.digital_out[4], WRITE_DOUT5);
  HANDLE_DOUT(bindings.digital_out[5], WRITE_DOUT6);
  HANDLE_DOUT(bindings.digital_out[6], WRITE_DOUT7);
  HANDLE_DOUT(bindings.digital_out[7], WRITE_DOUT8);
  
  HANDLE_DOUT(bindings.user_led[0], USER_LED0);
  
#undef HANDLE_DOUT

  return 0;
}
