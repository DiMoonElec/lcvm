#ifndef __LCVM_PUBLIC_API_H__
#define __LCVM_PUBLIC_API_H__

#include <stdint.h>

/**
 * @brief Состояниe Runtime
 */
typedef enum
{
  PLC_STATE_STOP = 0, /**< Остановлен */
  PLC_STATE_RUN = 1,  /**< Запущен */
  PLC_STATE_CYCLE = 2, /**< Выполняет один цикл, после перейдет в PAUSE */
  PLC_STATE_PAUSE = 3, /**< Выполнение приостановлено */
  PLC_STATE_EXCEPTION = 4 /**< Во время выполнения программы возникло исключение */
} lcvm_runtime_state_t;

typedef void (*plc_state_change_callback_t)(uint8_t new_state);

/*
* @brief Инициализация Runtime
* @param prgm_buff указатель на память программ
* @param size размер памяти программ
*/
void lcvm_runtime_init(uint8_t *prgm_buff, uint32_t size);


/*
* @brief Конечный автомат Runtime
*/
void lcvm_runtime_process(void);

/*
* @brief Установка callback-функции на изменение состояния Runtime
* @param cb ссылка на callback-функцию
*/
void lcvm_runtime_state_change_set_callback(plc_state_change_callback_t cb);

/*
* @brief Получить заданное время цикла
*/
uint32_t lcvm_runtime_get_cycle_time(void);

/*
* @brief Получить мгновенную длительность выполнения цикла
*/
uint32_t lcvm_runtime_get_duration(void);

/*
* @brief Получить максимальную длительность выполнения цикла с момента запуска программы
*/
uint32_t lcvm_runtime_get_duration_max(void);

/*
* @brief Запустить программу на выполнение
*/
int8_t lcvm_runtime_run(void);

/*
* @brief Остановить выполнение программы
*/
void lcvm_runtime_stop(void);

/*
* @brief Выполнить один цикл программы и перейти в состояние паузы
*/
int8_t lcvm_runtime_cycle(void);

/*
* @brief Получить текущее состояние Runtime
* @return Текущее состояние Runtime
*/
lcvm_runtime_state_t lcvm_runtime_get_state(void);

#endif