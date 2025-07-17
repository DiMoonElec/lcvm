#include "lcvm/public_api.h"
#include "inc/lcvm_runtime.h"
#include "inc/lcvm_core.h"
#include "inc/lcvm_core_exceptions.h"
#include "inc/lcvm_port_io.h"
#include "utils.h"

#include "lcvm_config.h"
#include "lcvm_port_hardware.h"
////////////////////////////////////////////////////////////////////////////

enum
{
  STATE_STOP = 0,
  STATE_RUN_INIT,
  STATE_LOOP_RUN,
  STATE_RUN_CONTINUE,
  STATE_PAUSE,

  NUM_STATES
};

enum
{
  PLC_NO_CMD = 0,
  PLC_CMD_RUN,
  PLC_CMD_STOP,
  PLC_CMD_BREAK
};

////////////////////////////////////////////////////////////////////////////

static uint8_t *PLCProgram;
static uint32_t PLCProgramSize;

////////////////////////////////////////////////////////////////////////////

static plc_state_change_callback_t state_change_callback;

static lcvm_application_t app;

static lcvm_runtime_state_t plc_state;

static uint8_t state;
static uint32_t timer = 0;

static uint32_t cycle_time = LCVM_DEFAULT_CYCLE_VALUE_MS;

static uint32_t duration_timer;  // Таймер замера времени цикла
static uint32_t duration_ms;     // Текущее время цикла
static uint32_t duration_ms_max; // Максимальное время цикла

static uint32_t function_loop_adr; // Адрес функции loop

////////////////////////////////////////////////////////////////////////////

static int set_function(uint16_t id, uint32_t adr)
{
  switch (id)
  {
  case 0:
    function_loop_adr = adr;
    return 0;
  }

  return -1;
}

static uint8_t section_0_present = 0; // Флаг наличия секции 0

// Функция обработки секций
static int parse_section(uint8_t id, uint32_t size, uint8_t *buffer)
{
  switch (id)
  {
  case 0x00: // code
  {
    if (buffer == 0 || size == 0)
      return -1; // Ошибка данных

    app.Program = buffer;
    app.ProgramSize = size;
    section_0_present = 1; // Отмечаем наличие секции 0
    return 0;
  }

  case 0x01: // variable
  {
    int index = 0;
    while (index < size)
    {
      if (index + 6 > size) // Проверка границ данных
        return -1;

      uint16_t var_id = GetUInt16(buffer, index);
      index += 2;

      uint32_t var_adr = GetUInt32(buffer, index);
      index += 4;

      if (lcvm_port_io_link_variable(var_id, var_adr) == -1)
        return -1; // Ошибка обработки переменной
    }
    return 0;
  }

  case 0x02: // function
  {
    int index = 0;
    while (index < size)
    {
      if (index + 6 > size) // Проверка границ данных
        return -1;

      uint16_t func_id = GetUInt16(buffer, index);
      index += 2;

      uint32_t func_adr = GetUInt32(buffer, index);
      index += 4;

      if (set_function(func_id, func_adr) == -1)
        return -1; // Ошибка обработки функции
    }
    return 0;
  }

  default:
    return 0; // Игнорируем неизвестные секции
  }
}

// Функция загрузки программы
static int prgm_load(uint8_t *plc_program, uint32_t prgBuffSize)
{
  if (plc_program == 0 || prgBuffSize < 8)
    return -1; // Некорректные входные данные

  int index = 0;

  // Размер исполняемого файла
  uint32_t exe_size = GetUInt32(plc_program, index);
  index += 4;

  if (exe_size > prgBuffSize || exe_size < 8)
    return -1; // Некорректный размер файла

  // Тип ПЛК
  uint16_t plc_id = GetUInt16(plc_program, index);
  index += 2;

  index += 4; // uid сборки

  // Сбрасываем флаг наличия секции 0
  section_0_present = 0;

  lcvm_port_io_unlink_variables();

  // Разбор секций
  while (index < exe_size - 4)
  {
    if (index + 5 > exe_size)
      return -1; // Проверка на выход за пределы файла

    uint8_t section_id = plc_program[index];
    index++;

    uint32_t section_size = GetUInt32(plc_program, index);
    index += 4;

    if (index + section_size > exe_size)
      return -1; // Проверка на выход за пределы секции

    if (parse_section(section_id, section_size, &plc_program[index]) == -1)
      return -1; // Ошибка обработки секции

    index += section_size;
  }

  // Проверка наличия секции 0
  if (!section_0_present)
    return -1; // Ошибка: отсутствует обязательная секция 0

  return 0; // Успешная загрузка
}

static int load(void)
{
  if (prgm_load(PLCProgram, PLCProgramSize))
    return -1;

  lcvm_core_load(&app);

  return 0;
}

////////////////////////////////////////////////////////////////////////////

void lcvm_runtime_init(uint8_t *prgm_buff, uint32_t size)
{
  PLCProgram = prgm_buff;
  PLCProgramSize = size;

  lcvm_port_io_set_default();
  state_change_callback = 0;
  plc_state = PLC_STATE_STOP;
  state = STATE_STOP;
}

void lcvm_runtime_state_change_set_callback(plc_state_change_callback_t c)
{
  state_change_callback = c;
}

int8_t lcvm_runtime_set_cycle_time(uint16_t value)
{
  cycle_time = value;
  return 0;
}

uint32_t lcvm_runtime_get_cycle_time(void)
{
  return cycle_time;
}

uint32_t lcvm_runtime_get_duration(void)
{
  return duration_ms;
}

uint32_t lcvm_runtime_get_duration_max(void)
{
  return duration_ms_max;
}

int8_t lcvm_runtime_run(void)
{
  if (state == STATE_STOP)
  {
    if (load())
      return -1;
  }

  if (state == STATE_STOP)
  {
    plc_state = PLC_STATE_RUN;
    return 0;
  }

  if (state == STATE_PAUSE)
  {
    plc_state = PLC_STATE_RUN;
    return 1;
  }

  return -2;
}

void lcvm_runtime_stop(void)
{
  if (plc_state == PLC_STATE_RUN      //
      || plc_state == PLC_STATE_CYCLE //
      || plc_state == PLC_STATE_PAUSE //
      || plc_state == PLC_STATE_EXCEPTION)
    plc_state = PLC_STATE_STOP;
}

int8_t lcvm_runtime_cycle(void)
{
  if (state == STATE_STOP)
  {
    if (load())
      return -1;
  }

  if (state == STATE_STOP            //
      || state == STATE_RUN_INIT     //
      || state == STATE_LOOP_RUN     //
      || state == STATE_RUN_CONTINUE //
      || state == STATE_PAUSE)
  {
    plc_state = PLC_STATE_CYCLE;
    return 0;
  }

  return -2;
}

lcvm_runtime_state_t lcvm_runtime_get_state(void)
{
  return plc_state;
}

void lcvm_runtime_process(void)
{
  switch (state)
  {
  case STATE_STOP:
  {
    // ПЛК находится в состоянии Stop

    // Если ПЛК перевели в режим RUN или CYCLE
    if (plc_state == PLC_STATE_RUN || plc_state == PLC_STATE_CYCLE)
    {
      /// Инициализация ВМ ///
      lcvm_core_reset();         // Сброс ВМ
      lcvm_core_set_function(0); // Функция init расположена по адресу 0

      // Сброс метрик в значения по-умолчанию
      cycle_time = LCVM_DEFAULT_CYCLE_VALUE_MS;
      duration_ms = 0;
      duration_ms_max = 0;

      // Вызываем callback
      if (state_change_callback != 0)
        state_change_callback(PLC_STATE_RUN);

      // Переходим в состояние исполнения кода инициализации ВМ
      state = STATE_RUN_INIT;
    }
  }
  break;
  ////////////////////////////////////////////////////////
  case STATE_RUN_INIT: // Выполнение кода инициализации приложения ПЛК
  {
    if (plc_state == PLC_STATE_STOP)
    {
      lcvm_port_io_set_default();

      if (state_change_callback != 0)
        state_change_callback(PLC_STATE_STOP);

      state = STATE_STOP;
      break;
    }

    // Чтение состояния входов перед выполнением init
    if (lcvm_port_io_action_get())
    {
      lcvm_port_io_set_default();

      if (state_change_callback != 0)
        state_change_callback(PLC_STATE_EXCEPTION);

      plc_state = PLC_STATE_EXCEPTION;
      state = STATE_STOP;
      break;
    }

    uint8_t r = lcvm_core_step();

    if (r == LCVM_CORE_STATUS_STOP) // Если init завершилась
    {
      // Установка состояния выходов после завершения init
      if (lcvm_port_io_action_set())
      {
        lcvm_port_io_set_default();

        if (state_change_callback != 0)
          state_change_callback(PLC_STATE_EXCEPTION);

        plc_state = PLC_STATE_EXCEPTION;
        state = STATE_STOP;
        break;
      }

      state = STATE_LOOP_RUN; // Переходим в состояние выполнения loop
    }
    else if (r == LCVM_CORE_STATUS_EXCEPTION) // Если произошел Exception
    {
      lcvm_port_io_set_default();

      if (state_change_callback != 0)
        state_change_callback(PLC_STATE_EXCEPTION);

      plc_state = PLC_STATE_EXCEPTION;
      state = STATE_STOP;
      break;
    }
  }
  break;
  ////////////////////////////////////////////////////////
  ////////////////////////////////////////////////////////
  case STATE_LOOP_RUN:
  {
    if (plc_state == PLC_STATE_STOP)
    {
      lcvm_port_io_set_default();

      if (state_change_callback != 0)
        state_change_callback(PLC_STATE_STOP);

      state = STATE_STOP;
      break;
    }

    if ((LCVM_TICK_MS() - timer) >= cycle_time)
    {
      timer += cycle_time;
      lcvm_core_set_function(function_loop_adr);

      // Перед циклом программы читаем входы
      duration_timer = LCVM_TICK_MS();

      // Чтение состояния входов перед выполнением loop
      if (lcvm_port_io_action_get())
      {
        lcvm_port_io_set_default();

        if (state_change_callback != 0)
          state_change_callback(PLC_STATE_EXCEPTION);

        plc_state = PLC_STATE_EXCEPTION;
        state = STATE_STOP;
        break;
      }

      // Выполнение функции loop
      uint8_t r = lcvm_core_step();

      if (r == LCVM_CORE_STATUS_RUN)
      {
        // Если функция loop не завершилась,
        // то повторно вызываем ее в следующий раз
        state = STATE_RUN_CONTINUE;
      }
      else if (r == LCVM_CORE_STATUS_STOP)
      {
        // Если функция loop завершилась

        // Установка состояния выходов после завершения цикла программы
        if (lcvm_port_io_action_set())
        {
          lcvm_port_io_set_default();

          if (state_change_callback != 0)
            state_change_callback(PLC_STATE_EXCEPTION);

          plc_state = PLC_STATE_EXCEPTION;
          state = STATE_STOP;
          break;
        }

        // Замер длительности цикла
        duration_ms = LCVM_TICK_MS() - duration_timer;

        // Замеряем максимальную длительность цикла
        if (duration_ms > duration_ms_max)
          duration_ms_max = duration_ms;

        if (plc_state == PLC_STATE_CYCLE)
        {
          if (state_change_callback != 0)
            state_change_callback(PLC_STATE_PAUSE);

          plc_state = PLC_STATE_PAUSE;
          state = STATE_PAUSE;
          break;
        }
      }
      else if (r == LCVM_CORE_STATUS_EXCEPTION) // Если произошел Exception
      {
        lcvm_port_io_set_default();

        if (state_change_callback != 0)
          state_change_callback(PLC_STATE_EXCEPTION);

        plc_state = PLC_STATE_EXCEPTION;
        state = STATE_STOP;
        break;
      }
    }
  }
  break;
  ////////////////////////////////////////////////////////
  case STATE_RUN_CONTINUE:
  {
    if (plc_state == PLC_STATE_STOP)
    {
      lcvm_port_io_set_default();

      if (state_change_callback != 0)
        state_change_callback(PLC_STATE_STOP);

      state = STATE_STOP;
      break;
    }

    uint8_t r = lcvm_core_step();

    if (r == LCVM_CORE_STATUS_STOP)
    {
      // Если функция loop завершилась, то
      // повторяем все действия, которые выполняются в
      // состоянии STATE_LOOP_RUN при LCVM_CORE_STATUS_STOP

      if (lcvm_port_io_action_set())
      {
        lcvm_port_io_set_default();

        if (state_change_callback != 0)
          state_change_callback(PLC_STATE_EXCEPTION);

        plc_state = PLC_STATE_EXCEPTION;
        state = STATE_STOP;
        break;
      }

      duration_ms = LCVM_TICK_MS() - duration_timer;
      if (duration_ms > duration_ms_max)
        duration_ms_max = duration_ms;

      // Переходим обратно
      if (plc_state == PLC_STATE_CYCLE)
      {
        if (state_change_callback != 0)
          state_change_callback(PLC_STATE_PAUSE);

        plc_state = PLC_STATE_PAUSE;
        state = STATE_PAUSE;
      }
      else
      {
        state = STATE_LOOP_RUN;
      }
    }
    else if (r == LCVM_CORE_STATUS_EXCEPTION) // Если произошел Exception
    {
      lcvm_port_io_set_default();

      if (state_change_callback != 0)
        state_change_callback(PLC_STATE_EXCEPTION);

      plc_state = PLC_STATE_EXCEPTION;
      state = STATE_STOP;
      break;
    }
  }
  break;
  ////////////////////////////////////////////////////////
  case STATE_PAUSE:
  {
    if (plc_state == PLC_STATE_STOP)
    {
      lcvm_port_io_set_default();

      if (state_change_callback != 0)
        state_change_callback(PLC_STATE_STOP);

      state = STATE_STOP;
    }
    else if (plc_state == PLC_STATE_RUN)
    {
      if (state_change_callback != 0)
        state_change_callback(PLC_STATE_RUN);

      state = STATE_LOOP_RUN;
    }
    else if (plc_state == PLC_STATE_CYCLE)
    {
      if (state_change_callback != 0)
        state_change_callback(PLC_STATE_CYCLE);

      state = STATE_LOOP_RUN;
    }
  }
  break;
  }
}

////////////////////////////////////////////////////////////////////////////
