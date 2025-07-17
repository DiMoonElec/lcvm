{
  // В стеке должен быть хотя бы одна свободная ячейка
  CHECK_OPSTACK_ELEMENTS_FREE_1();

  // В памяти программ должен быть доступен хотя бы 4 байта
  CHECK_PROGRAM_AVAILABLE_BYTES_4();

  lcvm_sp_op++;
#ifdef LCVM_ALLOW_UNALIGNED_ACCESS
  lcvm_OperationStack[lcvm_sp_op].u32 = *(uint32_t *)&lcvm_ProgramBuffer[lcvm_RegPC];
  lcvm_RegPC += 4;
#else
  lcvm_OperationStack[lcvm_sp_op].u32 =
      (uint32_t)lcvm_ProgramBuffer[lcvm_RegPC] |
      ((uint32_t)lcvm_ProgramBuffer[lcvm_RegPC + 1] << 8) |
      ((uint32_t)lcvm_ProgramBuffer[lcvm_RegPC + 2] << 16) |
      ((uint32_t)lcvm_ProgramBuffer[lcvm_RegPC + 3] << 24);

  lcvm_RegPC += 4;
#endif
}