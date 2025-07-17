#ifndef __LCVM_CORE_MACROS_H__
#define __LCVM_CORE_MACROS_H__

/******************************************************************
     Вспомогательные макросы
*******************************************************************/

#define LCVM_EXCEPTION(ex)                   \
  {                                          \
    lcvm_Exception = ex;                     \
    lcvm_State = LCVM_CORE_STATUS_EXCEPTION; \
    return lcvm_State;                       \
  }

#define CHECK_OPSTACK_AVAILABLE_ELEMENTS_1() \
  if (lcvm_sp_op < 0)                        \
    LCVM_EXCEPTION(LCVM_EXCEPTION_OPSTACK_EMPTY);

#define CHECK_OPSTACK_AVAILABLE_ELEMENTS_2() \
  if (lcvm_sp_op < 1)                        \
    LCVM_EXCEPTION(LCVM_EXCEPTION_OPSTACK_EMPTY);

#define CHECK_OPSTACK_AVAILABLE_ELEMENTS_3() \
  if (lcvm_sp_op < 2)                        \
    LCVM_EXCEPTION(LCVM_EXCEPTION_OPSTACK_EMPTY);

#define CHECK_OPSTACK_AVAILABLE_ELEMENTS_4() \
  if (lcvm_sp_op < 3)                        \
    LCVM_EXCEPTION(LCVM_EXCEPTION_OPSTACK_EMPTY);

#define CHECK_OPSTACK_ELEMENTS_FREE_1()            \
  if (lcvm_sp_op >= LCVM_OPERATION_STACK_SIZE - 2) \
    LCVM_EXCEPTION(LCVM_EXCEPTION_OPSTACK_OVERFLOW);

#define CHECK_OPSTACK_ELEMENTS_FREE_2()            \
  if (lcvm_sp_op >= LCVM_OPERATION_STACK_SIZE - 3) \
    LCVM_EXCEPTION(LCVM_EXCEPTION_OPSTACK_OVERFLOW);

#define CHECK_RETSTACK_ELEMENTS_FREE_1()         \
  if (lcvm_sp_ret >= LCVM_RETURN_STACK_SIZE - 2) \
    LCVM_EXCEPTION(LCVM_EXCEPTION_RETSTACK_OVERFLOW);

#define CHECK_PROGRAM_AVAILABLE_BYTES_1()   \
  if (lcvm_RegPC >= lcvm_ProgramBufferSize) \
    LCVM_EXCEPTION(LCVM_EXCEPTION_OUT_OF_PROGRAM);

#define CHECK_PROGRAM_AVAILABLE_BYTES_2()         \
  if (lcvm_RegPC >= (lcvm_ProgramBufferSize - 1)) \
    LCVM_EXCEPTION(LCVM_EXCEPTION_OUT_OF_PROGRAM);

#define CHECK_PROGRAM_AVAILABLE_BYTES_4()         \
  if (lcvm_RegPC >= (lcvm_ProgramBufferSize - 3)) \
    LCVM_EXCEPTION(LCVM_EXCEPTION_OUT_OF_PROGRAM);

#define CHECK_PROGRAM_AVAILABLE_BYTES_8()         \
  if (lcvm_RegPC >= (lcvm_ProgramBufferSize - 7)) \
    LCVM_EXCEPTION(LCVM_EXCEPTION_OUT_OF_PROGRAM);

/******************************************************************
     Макросы для стандартных бинарных операций
*******************************************************************/

#define BINARY_OPERATION_TYPED(field, type, cast_type, access_field, operation) \
  {                                                                             \
    CHECK_OPSTACK_AVAILABLE_ELEMENTS_2();                                       \
    type a = lcvm_OperationStack[lcvm_sp_op - 1].field;                         \
    type b = lcvm_OperationStack[lcvm_sp_op].field;                             \
    lcvm_sp_op--;                                                               \
    lcvm_OperationStack[lcvm_sp_op].access_field = (cast_type)(a operation b);  \
  }

#define BINARY_OPERATION_S8(operation) BINARY_OPERATION_TYPED(s8, int8_t, uint8_t, u32, operation)
#define BINARY_OPERATION_S16(operation) BINARY_OPERATION_TYPED(s16, int16_t, uint16_t, u32, operation)
#define BINARY_OPERATION_S32(operation) BINARY_OPERATION_TYPED(s32, int32_t, uint32_t, u32, operation)

#define BINARY_OPERATION_U8(operation) BINARY_OPERATION_TYPED(u8, uint8_t, uint8_t, u32, operation)
#define BINARY_OPERATION_U16(operation) BINARY_OPERATION_TYPED(u16, uint16_t, uint16_t, u32, operation)
#define BINARY_OPERATION_U32(operation) BINARY_OPERATION_TYPED(u32, uint32_t, uint32_t, u32, operation)

#define BINARY_OPERATION_FLOAT(operation) BINARY_OPERATION_TYPED(f, float, uint32_t, f, operation)

#if 0
#define BINARY_OPERATION_S8(operation)                              \
  {                                                                 \
    CHECK_OPSTACK_AVAILABLE_ELEMENTS_2();                           \
    int8_t a = lcvm_OperationStack[lcvm_sp_op - 1].s8;              \
    int8_t b = lcvm_OperationStack[lcvm_sp_op].s8;                  \
    lcvm_sp_op--;                                                   \
    lcvm_OperationStack[lcvm_sp_op].u32 = (uint8_t)(a operation b); \
  }

#define BINARY_OPERATION_S16(operation)                                  \
  {                                                                      \
    CHECK_OPSTACK_AVAILABLE_ELEMENTS_2();                                \
    int16_t a = lcvm_OperationStack[lcvm_sp_op - 1].s16;                 \
    int16_t b = lcvm_OperationStack[lcvm_sp_op].s16;                     \
    lcvm_OperationStack[lcvm_sp_op - 1].u32 = (uint16_t)(a operation b); \
    lcvm_sp_op--;                                                        \
  }

#define BINARY_OPERATION_S32(operation)                      \
  {                                                          \
    CHECK_OPSTACK_AVAILABLE_ELEMENTS_2();                    \
    int32_t a = lcvm_OperationStack[lcvm_sp_op - 1].s32;     \
    int32_t b = lcvm_OperationStack[lcvm_sp_op].s32;         \
    lcvm_OperationStack[lcvm_sp_op - 1].s32 = a operation b; \
    lcvm_sp_op--;                                            \
  }
#endif

#define BINARY_OPERATION_S64(operation)                      \
  {                                                          \
    CHECK_OPSTACK_AVAILABLE_ELEMENTS_4();                    \
    lcvm_long_element_t op1, op2;                            \
    op1.dwords[0] = lcvm_OperationStack[lcvm_sp_op - 3].u32; \
    op1.dwords[1] = lcvm_OperationStack[lcvm_sp_op - 2].u32; \
    op2.dwords[0] = lcvm_OperationStack[lcvm_sp_op - 1].u32; \
    op2.dwords[1] = lcvm_OperationStack[lcvm_sp_op].u32;     \
    op1.s64 = op1.s64 operation op2.s64;                     \
    lcvm_OperationStack[lcvm_sp_op - 3].u32 = op1.dwords[0]; \
    lcvm_OperationStack[lcvm_sp_op - 2].u32 = op1.dwords[1]; \
    lcvm_sp_op -= 2;                                         \
  }
#if 0
#define BINARY_OPERATION_U8(operation)                                                       \
  {                                                                                          \
    CHECK_OPSTACK_AVAILABLE_ELEMENTS_2();                                                    \
    lcvm_OperationStack[lcvm_sp_op - 1].u8 =                                                 \
        lcvm_OperationStack[lcvm_sp_op - 1].u8 operation lcvm_OperationStack[lcvm_sp_op].u8; \
    lcvm_sp_op--;                                                                            \
  }

#define BINARY_OPERATION_U16(operation)                                                        \
  {                                                                                            \
    CHECK_OPSTACK_AVAILABLE_ELEMENTS_2();                                                      \
    lcvm_OperationStack[lcvm_sp_op - 1].u16 =                                                  \
        lcvm_OperationStack[lcvm_sp_op - 1].u16 operation lcvm_OperationStack[lcvm_sp_op].u16; \
    lcvm_sp_op--;                                                                              \
  }

#define BINARY_OPERATION_U32(operation)                                                        \
  {                                                                                            \
    CHECK_OPSTACK_AVAILABLE_ELEMENTS_2();                                                      \
    lcvm_OperationStack[lcvm_sp_op - 1].u32 =                                                  \
        lcvm_OperationStack[lcvm_sp_op - 1].u32 operation lcvm_OperationStack[lcvm_sp_op].u32; \
    lcvm_sp_op--;                                                                              \
  }
#endif

#define BINARY_OPERATION_U64(operation)                      \
  {                                                          \
    CHECK_OPSTACK_AVAILABLE_ELEMENTS_4();                    \
    lcvm_long_element_t op1, op2;                            \
    op1.dwords[0] = lcvm_OperationStack[lcvm_sp_op - 3].u32; \
    op1.dwords[1] = lcvm_OperationStack[lcvm_sp_op - 2].u32; \
    op2.dwords[0] = lcvm_OperationStack[lcvm_sp_op - 1].u32; \
    op2.dwords[1] = lcvm_OperationStack[lcvm_sp_op].u32;     \
    op1.u64 = op1.u64 operation op2.u64;                     \
    lcvm_OperationStack[lcvm_sp_op - 3].u32 = op1.dwords[0]; \
    lcvm_OperationStack[lcvm_sp_op - 2].u32 = op1.dwords[1]; \
    lcvm_sp_op -= 2;                                         \
  }

#if 0
#define BINARY_OPERATION_FLOAT(operation)                                                  \
  {                                                                                        \
    CHECK_OPSTACK_AVAILABLE_ELEMENTS_2();                                                  \
    lcvm_OperationStack[lcvm_sp_op - 1].f =                                                \
        lcvm_OperationStack[lcvm_sp_op - 1].f operation lcvm_OperationStack[lcvm_sp_op].f; \
    lcvm_sp_op--;                                                                          \
  }
#endif
#define BINARY_OPERATION_DOUBLE(operation)                   \
  {                                                          \
    CHECK_OPSTACK_AVAILABLE_ELEMENTS_4();                    \
    lcvm_long_element_t op1, op2;                            \
    op1.dwords[0] = lcvm_OperationStack[lcvm_sp_op - 3].u32; \
    op1.dwords[1] = lcvm_OperationStack[lcvm_sp_op - 2].u32; \
    op2.dwords[0] = lcvm_OperationStack[lcvm_sp_op - 1].u32; \
    op2.dwords[1] = lcvm_OperationStack[lcvm_sp_op].u32;     \
    op1.d = op1.d operation op2.d;                           \
    lcvm_OperationStack[lcvm_sp_op - 3].u32 = op1.dwords[0]; \
    lcvm_OperationStack[lcvm_sp_op - 2].u32 = op1.dwords[1]; \
    lcvm_sp_op -= 2;                                         \
  }

/******************************************************************
     Макросы для операций сдвига
*******************************************************************/

#define SHIFT_OPERATION_S8(operation)                                                        \
  {                                                                                          \
    CHECK_OPSTACK_AVAILABLE_ELEMENTS_2();                                                    \
    lcvm_OperationStack[lcvm_sp_op - 1].s8 =                                                 \
        lcvm_OperationStack[lcvm_sp_op - 1].s8 operation lcvm_OperationStack[lcvm_sp_op].u8; \
    lcvm_sp_op--;                                                                            \
  }

#define SHIFT_OPERATION_S16(operation)                                                        \
  {                                                                                           \
    CHECK_OPSTACK_AVAILABLE_ELEMENTS_2();                                                     \
    lcvm_OperationStack[lcvm_sp_op - 1].s16 =                                                 \
        lcvm_OperationStack[lcvm_sp_op - 1].s16 operation lcvm_OperationStack[lcvm_sp_op].u8; \
    lcvm_sp_op--;                                                                             \
  }

#define SHIFT_OPERATION_S32(operation)                                                        \
  {                                                                                           \
    CHECK_OPSTACK_AVAILABLE_ELEMENTS_2();                                                     \
    lcvm_OperationStack[lcvm_sp_op - 1].s32 =                                                 \
        lcvm_OperationStack[lcvm_sp_op - 1].s32 operation lcvm_OperationStack[lcvm_sp_op].u8; \
    lcvm_sp_op--;                                                                             \
  }

#define SHIFT_OPERATION_S64(operation)                              \
  {                                                                 \
    CHECK_OPSTACK_AVAILABLE_ELEMENTS_3();                           \
    lcvm_long_element_t op1;                                        \
    op1.dwords[0] = lcvm_OperationStack[lcvm_sp_op - 2].u32;        \
    op1.dwords[1] = lcvm_OperationStack[lcvm_sp_op - 1].u32;        \
    op1.s64 = op1.s64 operation lcvm_OperationStack[lcvm_sp_op].u8; \
    lcvm_OperationStack[lcvm_sp_op - 2].u32 = op1.dwords[0];        \
    lcvm_OperationStack[lcvm_sp_op - 1].u32 = op1.dwords[1];        \
    lcvm_sp_op--;                                                   \
  }

#define SHIFT_OPERATION_U8(operation)                                                        \
  {                                                                                          \
    CHECK_OPSTACK_AVAILABLE_ELEMENTS_2();                                                    \
    lcvm_OperationStack[lcvm_sp_op - 1].u8 =                                                 \
        lcvm_OperationStack[lcvm_sp_op - 1].u8 operation lcvm_OperationStack[lcvm_sp_op].u8; \
    lcvm_sp_op--;                                                                            \
  }

#define SHIFT_OPERATION_U16(operation)                                                        \
  {                                                                                           \
    CHECK_OPSTACK_AVAILABLE_ELEMENTS_2();                                                     \
    lcvm_OperationStack[lcvm_sp_op - 1].u16 =                                                 \
        lcvm_OperationStack[lcvm_sp_op - 1].u16 operation lcvm_OperationStack[lcvm_sp_op].u8; \
    lcvm_sp_op--;                                                                             \
  }

#define SHIFT_OPERATION_U32(operation)                                                        \
  {                                                                                           \
    CHECK_OPSTACK_AVAILABLE_ELEMENTS_2();                                                     \
    lcvm_OperationStack[lcvm_sp_op - 1].u32 =                                                 \
        lcvm_OperationStack[lcvm_sp_op - 1].u32 operation lcvm_OperationStack[lcvm_sp_op].u8; \
    lcvm_sp_op--;                                                                             \
  }

#define SHIFT_OPERATION_U64(operation)                              \
  {                                                                 \
    CHECK_OPSTACK_AVAILABLE_ELEMENTS_3();                           \
    lcvm_long_element_t op1;                                        \
    op1.dwords[0] = lcvm_OperationStack[lcvm_sp_op - 2].u32;        \
    op1.dwords[1] = lcvm_OperationStack[lcvm_sp_op - 1].u32;        \
    op1.u64 = op1.u64 operation lcvm_OperationStack[lcvm_sp_op].u8; \
    lcvm_OperationStack[lcvm_sp_op - 2].u32 = op1.dwords[0];        \
    lcvm_OperationStack[lcvm_sp_op - 1].u32 = op1.dwords[1];        \
    lcvm_sp_op--;                                                   \
  }

/******************************************************************
     Макросы для операций сравнения
*******************************************************************/

#define COMP_OPERATION_S8(operation)                                                         \
  {                                                                                          \
    CHECK_OPSTACK_AVAILABLE_ELEMENTS_2();                                                    \
    lcvm_OperationStack[lcvm_sp_op - 1].u32 =                                                \
        lcvm_OperationStack[lcvm_sp_op - 1].s8 operation lcvm_OperationStack[lcvm_sp_op].s8; \
    lcvm_sp_op--;                                                                            \
  }

#define COMP_OPERATION_S16(operation)                                                          \
  {                                                                                            \
    CHECK_OPSTACK_AVAILABLE_ELEMENTS_2();                                                      \
    lcvm_OperationStack[lcvm_sp_op - 1].u32 =                                                  \
        lcvm_OperationStack[lcvm_sp_op - 1].s16 operation lcvm_OperationStack[lcvm_sp_op].s16; \
    lcvm_sp_op--;                                                                              \
  }

#define COMP_OPERATION_S32(operation)                                                          \
  {                                                                                            \
    CHECK_OPSTACK_AVAILABLE_ELEMENTS_2();                                                      \
    lcvm_OperationStack[lcvm_sp_op - 1].u32 =                                                  \
        lcvm_OperationStack[lcvm_sp_op - 1].s32 operation lcvm_OperationStack[lcvm_sp_op].s32; \
    lcvm_sp_op--;                                                                              \
  }

#define COMP_OPERATION_S64(operation)                                    \
  {                                                                      \
    CHECK_OPSTACK_AVAILABLE_ELEMENTS_4();                                \
    lcvm_long_element_t op1, op2;                                        \
    op1.dwords[0] = lcvm_OperationStack[lcvm_sp_op - 3].u32;             \
    op1.dwords[1] = lcvm_OperationStack[lcvm_sp_op - 2].u32;             \
    op2.dwords[0] = lcvm_OperationStack[lcvm_sp_op - 1].u32;             \
    op2.dwords[1] = lcvm_OperationStack[lcvm_sp_op].u32;                 \
    lcvm_OperationStack[lcvm_sp_op - 3].u32 = op1.s64 operation op2.s64; \
    lcvm_sp_op -= 3;                                                     \
  }

#define COMP_OPERATION_U8(operation)                                                         \
  {                                                                                          \
    CHECK_OPSTACK_AVAILABLE_ELEMENTS_2();                                                    \
    lcvm_OperationStack[lcvm_sp_op - 1].u32 =                                                \
        lcvm_OperationStack[lcvm_sp_op - 1].u8 operation lcvm_OperationStack[lcvm_sp_op].u8; \
    lcvm_sp_op--;                                                                            \
  }

#define COMP_OPERATION_U16(operation)                                                          \
  {                                                                                            \
    CHECK_OPSTACK_AVAILABLE_ELEMENTS_2();                                                      \
    lcvm_OperationStack[lcvm_sp_op - 1].u32 =                                                  \
        lcvm_OperationStack[lcvm_sp_op - 1].u16 operation lcvm_OperationStack[lcvm_sp_op].u16; \
    lcvm_sp_op--;                                                                              \
  }

#define COMP_OPERATION_U32(operation)                                                          \
  {                                                                                            \
    CHECK_OPSTACK_AVAILABLE_ELEMENTS_2();                                                      \
    lcvm_OperationStack[lcvm_sp_op - 1].u32 =                                                  \
        lcvm_OperationStack[lcvm_sp_op - 1].u32 operation lcvm_OperationStack[lcvm_sp_op].u32; \
    lcvm_sp_op--;                                                                              \
  }

#define COMP_OPERATION_U64(operation)                                    \
  {                                                                      \
    CHECK_OPSTACK_AVAILABLE_ELEMENTS_4();                                \
    lcvm_long_element_t op1, op2;                                        \
    op1.dwords[0] = lcvm_OperationStack[lcvm_sp_op - 3].u32;             \
    op1.dwords[1] = lcvm_OperationStack[lcvm_sp_op - 2].u32;             \
    op2.dwords[0] = lcvm_OperationStack[lcvm_sp_op - 1].u32;             \
    op2.dwords[1] = lcvm_OperationStack[lcvm_sp_op].u32;                 \
    lcvm_OperationStack[lcvm_sp_op - 3].u32 = op1.u64 operation op2.u64; \
    lcvm_sp_op -= 3;                                                     \
  }

#define COMP_OPERATION_FLOAT(operation)                                                    \
  {                                                                                        \
    CHECK_OPSTACK_AVAILABLE_ELEMENTS_2();                                                  \
    lcvm_OperationStack[lcvm_sp_op - 1].u32 =                                              \
        lcvm_OperationStack[lcvm_sp_op - 1].f operation lcvm_OperationStack[lcvm_sp_op].f; \
    lcvm_sp_op--;                                                                          \
  }

#define COMP_OPERATION_DOUBLE(operation)                             \
  {                                                                  \
    CHECK_OPSTACK_AVAILABLE_ELEMENTS_4();                            \
    lcvm_long_element_t op1, op2;                                    \
    op1.dwords[0] = lcvm_OperationStack[lcvm_sp_op - 3].u32;         \
    op1.dwords[1] = lcvm_OperationStack[lcvm_sp_op - 2].u32;         \
    op2.dwords[0] = lcvm_OperationStack[lcvm_sp_op - 1].u32;         \
    op2.dwords[1] = lcvm_OperationStack[lcvm_sp_op].u32;             \
    lcvm_OperationStack[lcvm_sp_op - 3].u32 = op1.d operation op2.d; \
    lcvm_sp_op -= 3;                                                 \
  }

#define COMP_OPERATION_BOOL_EQ()                                                      \
  {                                                                                   \
    CHECK_OPSTACK_AVAILABLE_ELEMENTS_2();                                             \
    lcvm_OperationStack[lcvm_sp_op - 1].u32 =                                         \
        lcvm_OperationStack[lcvm_sp_op - 1].u8 && lcvm_OperationStack[lcvm_sp_op].u8; \
    lcvm_sp_op--;                                                                     \
  }

#define COMP_OPERATION_BOOL_NEQ()                                                        \
  {                                                                                      \
    CHECK_OPSTACK_AVAILABLE_ELEMENTS_2();                                                \
    lcvm_OperationStack[lcvm_sp_op - 1].u32 =                                            \
        !(lcvm_OperationStack[lcvm_sp_op - 1].u8 && lcvm_OperationStack[lcvm_sp_op].u8); \
    lcvm_sp_op--;                                                                        \
  }

/******************************************************************
     Макросы для стандартных унарных операций
*******************************************************************/

#define UNARY_OPERATION_S8(operation)                                                  \
  {                                                                                    \
    CHECK_OPSTACK_AVAILABLE_ELEMENTS_1();                                              \
    lcvm_OperationStack[lcvm_sp_op].s8 = operation lcvm_OperationStack[lcvm_sp_op].s8; \
  }

#define UNARY_OPERATION_S16(operation)                                                   \
  {                                                                                      \
    CHECK_OPSTACK_AVAILABLE_ELEMENTS_1();                                                \
    lcvm_OperationStack[lcvm_sp_op].s16 = operation lcvm_OperationStack[lcvm_sp_op].s16; \
  }

#define UNARY_OPERATION_S32(operation)                                                   \
  {                                                                                      \
    CHECK_OPSTACK_AVAILABLE_ELEMENTS_1();                                                \
    lcvm_OperationStack[lcvm_sp_op].s32 = operation lcvm_OperationStack[lcvm_sp_op].s32; \
  }

#define UNARY_OPERATION_S64(operation)                     \
  {                                                        \
    CHECK_OPSTACK_AVAILABLE_ELEMENTS_2();                  \
    lcvm_long_element_t e;                                 \
    e.dwords[0] = lcvm_OperationStack[lcvm_sp_op - 1].u32; \
    e.dwords[1] = lcvm_OperationStack[lcvm_sp_op].u32;     \
    e.s64 = operation e.s64;                               \
    lcvm_OperationStack[lcvm_sp_op - 1].u32 = e.dwords[0]; \
    lcvm_OperationStack[lcvm_sp_op].u32 = e.dwords[1];     \
  }

#define UNARY_OPERATION_U8(operation)                                                  \
  {                                                                                    \
    CHECK_OPSTACK_AVAILABLE_ELEMENTS_1();                                              \
    lcvm_OperationStack[lcvm_sp_op].u8 = operation lcvm_OperationStack[lcvm_sp_op].u8; \
  }

#define UNARY_OPERATION_U16(operation)                                                   \
  {                                                                                      \
    CHECK_OPSTACK_AVAILABLE_ELEMENTS_1();                                                \
    lcvm_OperationStack[lcvm_sp_op].u16 = operation lcvm_OperationStack[lcvm_sp_op].u16; \
  }

#define UNARY_OPERATION_U32(operation)                                                   \
  {                                                                                      \
    CHECK_OPSTACK_AVAILABLE_ELEMENTS_1();                                                \
    lcvm_OperationStack[lcvm_sp_op].u32 = operation lcvm_OperationStack[lcvm_sp_op].u32; \
  }

#define UNARY_OPERATION_U64(operation)                     \
  {                                                        \
    CHECK_OPSTACK_AVAILABLE_ELEMENTS_2();                  \
    lcvm_long_element_t e;                                 \
    e.dwords[0] = lcvm_OperationStack[lcvm_sp_op - 1].u32; \
    e.dwords[1] = lcvm_OperationStack[lcvm_sp_op].u32;     \
    e.u64 = operation e.u64;                               \
    lcvm_OperationStack[lcvm_sp_op - 1].u32 = e.dwords[0]; \
    lcvm_OperationStack[lcvm_sp_op].u32 = e.dwords[1];     \
  }

#define UNARY_OPERATION_FLOAT(operation)                                             \
  {                                                                                  \
    CHECK_OPSTACK_AVAILABLE_ELEMENTS_1();                                            \
    lcvm_OperationStack[lcvm_sp_op].f = operation lcvm_OperationStack[lcvm_sp_op].f; \
  }

#define UNARY_OPERATION_DOUBLE(operation)                  \
  {                                                        \
    CHECK_OPSTACK_AVAILABLE_ELEMENTS_2();                  \
    lcvm_long_element_t e;                                 \
    e.dwords[0] = lcvm_OperationStack[lcvm_sp_op - 1].u32; \
    e.dwords[1] = lcvm_OperationStack[lcvm_sp_op].u32;     \
    e.d = operation e.d;                                   \
    lcvm_OperationStack[lcvm_sp_op - 1].u32 = e.dwords[0]; \
    lcvm_OperationStack[lcvm_sp_op].u32 = e.dwords[1];     \
  }

/******************************************************************
     Макросы для унарных операций инкремента/декремента
*******************************************************************/

#define INCR_DECR_OPERATION_S8(operation)         \
  {                                               \
    CHECK_OPSTACK_AVAILABLE_ELEMENTS_1();         \
    lcvm_OperationStack[lcvm_sp_op].s8 operation; \
  }

#define INCR_DECR_OPERATION_S16(operation)         \
  {                                                \
    CHECK_OPSTACK_AVAILABLE_ELEMENTS_1();          \
    lcvm_OperationStack[lcvm_sp_op].s16 operation; \
  }

#define INCR_DECR_OPERATION_S32(operation)         \
  {                                                \
    CHECK_OPSTACK_AVAILABLE_ELEMENTS_1();          \
    lcvm_OperationStack[lcvm_sp_op].s32 operation; \
  }

#define INCR_DECR_OPERATION_S64(operation)                 \
  {                                                        \
    CHECK_OPSTACK_AVAILABLE_ELEMENTS_2();                  \
    lcvm_long_element_t e;                                 \
    e.dwords[0] = lcvm_OperationStack[lcvm_sp_op - 1].u32; \
    e.dwords[1] = lcvm_OperationStack[lcvm_sp_op].u32;     \
    e.s64 operation;                                       \
    lcvm_OperationStack[lcvm_sp_op - 1].u32 = e.dwords[0]; \
    lcvm_OperationStack[lcvm_sp_op].u32 = e.dwords[1];     \
  }

#define INCR_DECR_OPERATION_U8(operation)         \
  {                                               \
    CHECK_OPSTACK_AVAILABLE_ELEMENTS_1();         \
    lcvm_OperationStack[lcvm_sp_op].u8 operation; \
  }

#define INCR_DECR_OPERATION_U16(operation)         \
  {                                                \
    CHECK_OPSTACK_AVAILABLE_ELEMENTS_1();          \
    lcvm_OperationStack[lcvm_sp_op].u16 operation; \
  }

#define INCR_DECR_OPERATION_U32(operation)         \
  {                                                \
    CHECK_OPSTACK_AVAILABLE_ELEMENTS_1();          \
    lcvm_OperationStack[lcvm_sp_op].u32 operation; \
  }

#define INCR_DECR_OPERATION_U64(operation)                 \
  {                                                        \
    CHECK_OPSTACK_AVAILABLE_ELEMENTS_2();                  \
    lcvm_long_element_t e;                                 \
    e.dwords[0] = lcvm_OperationStack[lcvm_sp_op - 1].u32; \
    e.dwords[1] = lcvm_OperationStack[lcvm_sp_op].u32;     \
    e.u64 operation;                                       \
    lcvm_OperationStack[lcvm_sp_op - 1].u32 = e.dwords[0]; \
    lcvm_OperationStack[lcvm_sp_op].u32 = e.dwords[1];     \
  }

#define INCR_DECR_OPERATION_FLOAT(operation)     \
  {                                              \
    CHECK_OPSTACK_AVAILABLE_ELEMENTS_1();        \
    lcvm_OperationStack[lcvm_sp_op].f operation; \
  }

#define INCR_DECR_OPERATION_DOUBLE(operation)              \
  {                                                        \
    CHECK_OPSTACK_AVAILABLE_ELEMENTS_2();                  \
    lcvm_long_element_t e;                                 \
    e.dwords[0] = lcvm_OperationStack[lcvm_sp_op - 1].u32; \
    e.dwords[1] = lcvm_OperationStack[lcvm_sp_op].u32;     \
    e.d operation;                                         \
    lcvm_OperationStack[lcvm_sp_op - 1].u32 = e.dwords[0]; \
    lcvm_OperationStack[lcvm_sp_op].u32 = e.dwords[1];     \
  }

#endif
