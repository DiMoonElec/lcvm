switch (opcode)
{
case OPCODE_NOP:
#include "OPCODE_NOP.inc"
  break;

case OPCODE_INCR:
#include "OPCODE_INCR.inc"
  break;

case OPCODE_DECR:
#include "OPCODE_DECR.inc"
  break;

case OPCODE_INV:
#include "OPCODE_INV.inc"
  break;

case OPCODE_MUL:
#include "OPCODE_MUL.inc"
  break;

case OPCODE_DIV:
#include "OPCODE_DIV.inc"
  break;

case OPCODE_REM:
#include "OPCODE_REM.inc"
  break;

case OPCODE_ADD:
#include "OPCODE_ADD.inc"
  break;

case OPCODE_SUB:
#include "OPCODE_SUB.inc"
  break;

case OPCODE_LESS:
#include "OPCODE_LESS.inc"
  break;

case OPCODE_LESSEQ:
#include "OPCODE_LESSEQ.inc"
  break;

case OPCODE_MORE:
#include "OPCODE_MORE.inc"
  break;

case OPCODE_MOREEQ:
#include "OPCODE_MOREEQ.inc"
  break;

case OPCODE_EQ:
#include "OPCODE_EQ.inc"
  break;

case OPCODE_NEQ:
#include "OPCODE_NEQ.inc"
  break;

case OPCODE_LSHIFT:
#include "OPCODE_LSHIFT.inc"
  break;

case OPCODE_RSHIFT:
#include "OPCODE_RSHIFT.inc"
  break;

case OPCODE_AND:
#include "OPCODE_AND.inc"
  break;

case OPCODE_XOR:
#include "OPCODE_XOR.inc"
  break;

case OPCODE_OR:
#include "OPCODE_OR.inc"
  break;

case OPCODE_NOT:
#include "OPCODE_NOT.inc"
  break;

case OPCODE_PUSH_1:
#include "OPCODE_PUSH_1.inc"
  break;

case OPCODE_PUSH_2:
#include "OPCODE_PUSH_2.inc"
  break;

case OPCODE_PUSH_4:
#include "OPCODE_PUSH_4.inc"
  break;

case OPCODE_PUSH_8:
#include "OPCODE_PUSH_8.inc"
  break;

case OPCODE_DUP:
#include "OPCODE_DUP.inc"
  break;

case OPCODE_DUP_2:
#include "OPCODE_DUP_2.inc"
  break;

case OPCODE_DROP:
#include "OPCODE_DROP.inc"
  break;

case OPCODE_DROP_2:
#include "OPCODE_DROP_2.inc"
  break;

case OPCODE_STORE_1:
#include "OPCODE_STORE_1.inc"
  break;

case OPCODE_STORE_2:
#include "OPCODE_STORE_2.inc"
  break;

case OPCODE_STORE_4:
#include "OPCODE_STORE_4.inc"
  break;

case OPCODE_STORE_8:
#include "OPCODE_STORE_8.inc"
  break;

case OPCODE_GSTORE_1:
#include "OPCODE_GSTORE_1.inc"
  break;

case OPCODE_GSTORE_2:
#include "OPCODE_GSTORE_2.inc"
  break;

case OPCODE_GSTORE_4:
#include "OPCODE_GSTORE_4.inc"
  break;

case OPCODE_GSTORE_8:
#include "OPCODE_GSTORE_8.inc"
  break;

case OPCODE_ASTORE_1:
#include "OPCODE_ASTORE_1.inc"
  break;

case OPCODE_ASTORE_2:
#include "OPCODE_ASTORE_2.inc"
  break;

case OPCODE_ASTORE_4:
#include "OPCODE_ASTORE_4.inc"
  break;

case OPCODE_ASTORE_8:
#include "OPCODE_ASTORE_8.inc"
  break;

case OPCODE_LOAD_1:
#include "OPCODE_LOAD_1.inc"
  break;

case OPCODE_LOAD_2:
#include "OPCODE_LOAD_2.inc"
  break;

case OPCODE_LOAD_4:
#include "OPCODE_LOAD_4.inc"
  break;

case OPCODE_LOAD_8:
#include "OPCODE_LOAD_8.inc"
  break;

case OPCODE_GLOAD_1:
#include "OPCODE_GLOAD_1.inc"
  break;

case OPCODE_GLOAD_2:
#include "OPCODE_GLOAD_2.inc"
  break;

case OPCODE_GLOAD_4:
#include "OPCODE_GLOAD_4.inc"
  break;

case OPCODE_GLOAD_8:
#include "OPCODE_GLOAD_8.inc"
  break;

case OPCODE_ALOAD_1:
#include "OPCODE_ALOAD_1.inc"
  break;

case OPCODE_ALOAD_2:
#include "OPCODE_ALOAD_2.inc"
  break;

case OPCODE_ALOAD_4:
#include "OPCODE_ALOAD_4.inc"
  break;

case OPCODE_ALOAD_8:
#include "OPCODE_ALOAD_8.inc"
  break;

case OPCODE_CALL:
#include "OPCODE_CALL.inc"
  break;

case OPCODE_CALL_T:
#include "OPCODE_CALL_T.inc"
  break;

case OPCODE_CALL_S:
#include "OPCODE_CALL_S.inc"
  break;

case OPCODE_REFCALL:
#include "OPCODE_REFCALL.inc"
  break;

case OPCODE_SYSCALL:
#include "OPCODE_SYSCALL.inc"
  break;

case OPCODE_SYSCALL_T:
#include "OPCODE_SYSCALL_T.inc"
  break;

case OPCODE_IFFALSE:
#include "OPCODE_IFFALSE.inc"
  break;

case OPCODE_IFFALSE_T:
#include "OPCODE_IFFALSE_T.inc"
  break;

case OPCODE_IFFALSE_S:
#include "OPCODE_IFFALSE_S.inc"
  break;

case OPCODE_IFTRUE:
#include "OPCODE_IFTRUE.inc"
  break;

case OPCODE_IFTRUE_T:
#include "OPCODE_IFTRUE_T.inc"
  break;

case OPCODE_IFTRUE_S:
#include "OPCODE_IFTRUE_S.inc"
  break;

case OPCODE_JMP:
#include "OPCODE_JMP.inc"
  break;

case OPCODE_JMP_T:
#include "OPCODE_JMP_T.inc"
  break;

case OPCODE_JMP_S:
#include "OPCODE_JMP_S.inc"
  break;

case OPCODE_RET:
#include "OPCODE_RET.inc"
  break;

case OPCODE_INCR_FP:
#include "OPCODE_INCR_FP.inc"
  break;

case OPCODE_INCR_FP_T:
#include "OPCODE_INCR_FP_T.inc"
  break;

case OPCODE_DECR_FP:
#include "OPCODE_DECR_FP.inc"
  break;

case OPCODE_DECR_FP_T:
#include "OPCODE_DECR_FP_T.inc"
  break;

case OPCODE_LOAD_FP:
#include "OPCODE_LOAD_FP.inc"
  break;

case OPCODE_BOOL_TO_INT16:
case OPCODE_BOOL_TO_UINT16:
#include "OPCODE_BOOL_TO_UINT16.inc"
  break;

case OPCODE_BOOL_TO_INT32:
case OPCODE_BOOL_TO_UINT32:
#include "OPCODE_BOOL_TO_UINT32.inc"
  break;

case OPCODE_BOOL_TO_INT64:
case OPCODE_BOOL_TO_UINT64:
#include "OPCODE_BOOL_TO_UINT64.inc"
  break;

case OPCODE_BOOL_TO_FLOAT:
#include "OPCODE_BOOL_TO_FLOAT.inc"
  break;

case OPCODE_BOOL_TO_DOUBLE:
#include "OPCODE_BOOL_TO_DOUBLE.inc"
  break;

case OPCODE_INT8_TO_INT16:
#include "OPCODE_INT8_TO_INT16.inc"
  break;

case OPCODE_INT8_TO_UINT16:
#include "OPCODE_INT8_TO_UINT16.inc"
  break;

case OPCODE_INT8_TO_INT32:
#include "OPCODE_INT8_TO_INT32.inc"
  break;

case OPCODE_INT8_TO_UINT32:
#include "OPCODE_INT8_TO_UINT32.inc"
  break;

case OPCODE_INT8_TO_INT64:
#include "OPCODE_INT8_TO_INT64.inc"
  break;

case OPCODE_INT8_TO_UINT64:
#include "OPCODE_INT8_TO_UINT64.inc"
  break;

case OPCODE_INT8_TO_FLOAT:
#include "OPCODE_INT8_TO_FLOAT.inc"
  break;

case OPCODE_INT8_TO_DOUBLE:
#include "OPCODE_INT8_TO_DOUBLE.inc"
  break;

case OPCODE_BOOL_TO_INT8:
case OPCODE_BOOL_TO_UINT8:
case OPCODE_INT8_TO_BOOL:
case OPCODE_UINT8_TO_BOOL:
#include "OPCODE_UINT8_TO_BOOL.inc"
  break;

case OPCODE_UINT8_TO_INT16:
#include "OPCODE_UINT8_TO_INT16.inc"
  break;

case OPCODE_UINT8_TO_UINT16:
#include "OPCODE_UINT8_TO_UINT16.inc"
  break;

case OPCODE_UINT8_TO_INT32:
#include "OPCODE_UINT8_TO_INT32.inc"
  break;

case OPCODE_UINT8_TO_UINT32:
#include "OPCODE_UINT8_TO_UINT32.inc"
  break;

case OPCODE_UINT8_TO_INT64:
case OPCODE_UINT8_TO_UINT64:
#include "OPCODE_UINT8_TO_UINT64.inc"
  break;

case OPCODE_UINT8_TO_FLOAT:
#include "OPCODE_UINT8_TO_FLOAT.inc"
  break;

case OPCODE_UINT8_TO_DOUBLE:
#include "OPCODE_UINT8_TO_DOUBLE.inc"
  break;

case OPCODE_INT16_TO_INT32:
#include "OPCODE_INT16_TO_INT32.inc"
  break;

case OPCODE_INT16_TO_UINT32:
#include "OPCODE_INT16_TO_UINT32.inc"
  break;

case OPCODE_INT16_TO_INT64:
#include "OPCODE_INT16_TO_INT64.inc"
  break;

case OPCODE_INT16_TO_UINT64:
#include "OPCODE_INT16_TO_UINT64.inc"
  break;

case OPCODE_INT16_TO_FLOAT:
#include "OPCODE_INT16_TO_FLOAT.inc"
  break;

case OPCODE_INT16_TO_DOUBLE:
#include "OPCODE_INT16_TO_DOUBLE.inc"
  break;

case OPCODE_INT16_TO_BOOL:
case OPCODE_UINT16_TO_BOOL:
#include "OPCODE_UINT16_TO_BOOL.inc"
  break;

case OPCODE_UINT16_TO_INT32:
#include "OPCODE_UINT16_TO_INT32.inc"
  break;

case OPCODE_UINT16_TO_UINT32:
#include "OPCODE_UINT16_TO_UINT32.inc"
  break;

case OPCODE_UINT16_TO_INT64:
#include "OPCODE_UINT16_TO_INT64.inc"
  break;

case OPCODE_UINT16_TO_UINT64:
#include "OPCODE_UINT16_TO_UINT64.inc"
  break;

case OPCODE_UINT16_TO_FLOAT:
#include "OPCODE_UINT16_TO_FLOAT.inc"
  break;

case OPCODE_UINT16_TO_DOUBLE:
#include "OPCODE_UINT16_TO_DOUBLE.inc"
  break;

case OPCODE_INT32_TO_INT64:
#include "OPCODE_INT32_TO_INT64.inc"
  break;

case OPCODE_INT32_TO_UINT64:
#include "OPCODE_INT32_TO_UINT64.inc"
  break;

case OPCODE_INT32_TO_FLOAT:
#include "OPCODE_INT32_TO_FLOAT.inc"
  break;

case OPCODE_INT32_TO_DOUBLE:
#include "OPCODE_INT32_TO_DOUBLE.inc"
  break;

case OPCODE_INT32_TO_BOOL:
case OPCODE_UINT32_TO_BOOL:
#include "OPCODE_UINT32_TO_BOOL.inc"
  break;

case OPCODE_INT8_TO_UINT8:
case OPCODE_UINT8_TO_INT8:
case OPCODE_INT16_TO_INT8:
case OPCODE_INT16_TO_UINT8:
case OPCODE_INT16_TO_UINT16:
case OPCODE_UINT16_TO_INT8:
case OPCODE_UINT16_TO_UINT8:
case OPCODE_UINT16_TO_INT16:
case OPCODE_INT32_TO_INT8:
case OPCODE_INT32_TO_UINT8:
case OPCODE_INT32_TO_INT16:
case OPCODE_INT32_TO_UINT16:
case OPCODE_INT32_TO_UINT32:
case OPCODE_UINT32_TO_INT8:
case OPCODE_UINT32_TO_UINT8:
case OPCODE_UINT32_TO_INT16:
case OPCODE_UINT32_TO_UINT16:
case OPCODE_UINT32_TO_INT32:
#include "OPCODE_UINT32_TO_INT32.inc"
  break;

case OPCODE_UINT32_TO_INT64:
#include "OPCODE_UINT32_TO_INT64.inc"
  break;

case OPCODE_UINT32_TO_UINT64:
#include "OPCODE_UINT32_TO_UINT64.inc"
  break;

case OPCODE_UINT32_TO_FLOAT:
#include "OPCODE_UINT32_TO_FLOAT.inc"
  break;

case OPCODE_UINT32_TO_DOUBLE:
#include "OPCODE_UINT32_TO_DOUBLE.inc"
  break;

case OPCODE_INT64_TO_FLOAT:
#include "OPCODE_INT64_TO_FLOAT.inc"
  break;

case OPCODE_INT64_TO_DOUBLE:
#include "OPCODE_INT64_TO_DOUBLE.inc"
  break;

case OPCODE_INT64_TO_BOOL:
case OPCODE_UINT64_TO_BOOL:
#include "OPCODE_UINT64_TO_BOOL.inc"
  break;

case OPCODE_INT64_TO_INT8:
case OPCODE_INT64_TO_UINT8:
case OPCODE_INT64_TO_INT16:
case OPCODE_INT64_TO_UINT16:
case OPCODE_INT64_TO_INT32:
case OPCODE_INT64_TO_UINT32:
case OPCODE_UINT64_TO_INT8:
case OPCODE_UINT64_TO_UINT8:
case OPCODE_UINT64_TO_INT16:
case OPCODE_UINT64_TO_UINT16:
case OPCODE_UINT64_TO_INT32:
case OPCODE_UINT64_TO_UINT32:
#include "OPCODE_UINT64_TO_UINT32.inc"
  break;

case OPCODE_INT64_TO_UINT64:
case OPCODE_UINT64_TO_INT64:
#include "OPCODE_UINT64_TO_INT64.inc"
  break;

case OPCODE_UINT64_TO_FLOAT:
#include "OPCODE_UINT64_TO_FLOAT.inc"
  break;

case OPCODE_UINT64_TO_DOUBLE:
#include "OPCODE_UINT64_TO_DOUBLE.inc"
  break;

case OPCODE_FLOAT_TO_BOOL:
#include "OPCODE_FLOAT_TO_BOOL.inc"
  break;

case OPCODE_FLOAT_TO_INT8:
#include "OPCODE_FLOAT_TO_INT8.inc"
  break;

case OPCODE_FLOAT_TO_UINT8:
#include "OPCODE_FLOAT_TO_UINT8.inc"
  break;

case OPCODE_FLOAT_TO_INT16:
#include "OPCODE_FLOAT_TO_INT16.inc"
  break;

case OPCODE_FLOAT_TO_UINT16:
#include "OPCODE_FLOAT_TO_UINT16.inc"
  break;

case OPCODE_FLOAT_TO_INT32:
#include "OPCODE_FLOAT_TO_INT32.inc"
  break;

case OPCODE_FLOAT_TO_UINT32:
#include "OPCODE_FLOAT_TO_UINT32.inc"
  break;

case OPCODE_FLOAT_TO_INT64:
#include "OPCODE_FLOAT_TO_INT64.inc"
  break;

case OPCODE_FLOAT_TO_UINT64:
#include "OPCODE_FLOAT_TO_UINT64.inc"
  break;

case OPCODE_FLOAT_TO_DOUBLE:
#include "OPCODE_FLOAT_TO_DOUBLE.inc"
  break;

case OPCODE_DOUBLE_TO_BOOL:
#include "OPCODE_DOUBLE_TO_BOOL.inc"
  break;

case OPCODE_DOUBLE_TO_INT8:
#include "OPCODE_DOUBLE_TO_INT8.inc"
  break;

case OPCODE_DOUBLE_TO_UINT8:
#include "OPCODE_DOUBLE_TO_UINT8.inc"
  break;

case OPCODE_DOUBLE_TO_INT16:
#include "OPCODE_DOUBLE_TO_INT16.inc"
  break;

case OPCODE_DOUBLE_TO_UINT16:
#include "OPCODE_DOUBLE_TO_UINT16.inc"
  break;

case OPCODE_DOUBLE_TO_INT32:
#include "OPCODE_DOUBLE_TO_INT32.inc"
  break;

case OPCODE_DOUBLE_TO_UINT32:
#include "OPCODE_DOUBLE_TO_UINT32.inc"
  break;

case OPCODE_DOUBLE_TO_INT64:
#include "OPCODE_DOUBLE_TO_INT64.inc"
  break;

case OPCODE_DOUBLE_TO_UINT64:
#include "OPCODE_DOUBLE_TO_UINT64.inc"
  break;

case OPCODE_DOUBLE_TO_FLOAT:
#include "OPCODE_DOUBLE_TO_FLOAT.inc"
  break;

case OPCODE_HALT:
#include "OPCODE_HALT.inc"
  break;

default:
  LCVM_EXCEPTION(LCVM_EXCEPTION_UNKNOWN_INSTRUCTION);
}
