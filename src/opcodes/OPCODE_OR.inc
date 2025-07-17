{
  // В памяти программ должен быть доступен хотя бы 1 байт
  CHECK_PROGRAM_AVAILABLE_BYTES_1();

  switch (lcvm_ProgramBuffer[lcvm_RegPC++])
  {
  case TYPE_INT8:
    BINARY_OPERATION_S8(|);
    break;

  case TYPE_INT16:
    BINARY_OPERATION_S16(|);
    break;

  case TYPE_INT32:
    BINARY_OPERATION_S32(|);
    break;

  case TYPE_INT64:
    BINARY_OPERATION_S64(|);
    break;

  case TYPE_UINT8:
    BINARY_OPERATION_U8(|);
    break;

  case TYPE_UINT16:
    BINARY_OPERATION_U16(|);
    break;

  case TYPE_UINT32:
    BINARY_OPERATION_U32(|);
    break;

  case TYPE_UINT64:
    BINARY_OPERATION_U64(|);
    break;

  case TYPE_BOOL:
    BINARY_OPERATION_U8(||);
    break;

  default:
    LCVM_EXCEPTION(LCVM_EXCEPTION_INVALID_INSTRUCTION_PARAM);
  }
}