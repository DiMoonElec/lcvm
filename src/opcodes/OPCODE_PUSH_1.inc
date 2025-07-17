{
  // В стеке должен быть хотя бы одна свободная ячейка
  CHECK_OPSTACK_ELEMENTS_FREE_1();

  // В памяти программ должен быть доступен хотя бы 1 байт
  CHECK_PROGRAM_AVAILABLE_BYTES_1();

  lcvm_sp_op++;
#ifdef LCVM_ALLOW_UNALIGNED_ACCESS
  lcvm_OperationStack[lcvm_sp_op].u32 = *(uint8_t *)&lcvm_ProgramBuffer[lcvm_RegPC];
  lcvm_RegPC++;
#else
  lcvm_OperationStack[lcvm_sp_op].u32 = lcvm_ProgramBuffer[lcvm_RegPC];
  lcvm_RegPC++;
#endif
}