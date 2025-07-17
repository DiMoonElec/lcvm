{
  // В памяти программ должен быть доступен хотя бы 1 байт
  CHECK_PROGRAM_AVAILABLE_BYTES_1();

  switch (lcvm_ProgramBuffer[lcvm_RegPC++])
  {
  case TYPE_INT8:
    UNARY_OPERATION_S8(-);
    break;

  case TYPE_INT16:
    UNARY_OPERATION_S16(-);
    break;

  case TYPE_INT32:
    UNARY_OPERATION_S32(-);
    break;

  case TYPE_INT64:
    UNARY_OPERATION_S64(-);
    break;

  case TYPE_FLOAT:
    UNARY_OPERATION_FLOAT(-);
    break;

  case TYPE_DOUBLE:
    UNARY_OPERATION_DOUBLE(-);
    break;

  default:
    LCVM_EXCEPTION(LCVM_EXCEPTION_INVALID_INSTRUCTION_PARAM);
  }
}