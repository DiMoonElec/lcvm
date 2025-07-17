{
  // В памяти программ должен быть доступен хотя бы 4 байта, это относительный адрес для сохранения
  CHECK_PROGRAM_AVAILABLE_BYTES_4();

  // В стеке должен находиться 1 элемент, это значение для сохранения
  CHECK_OPSTACK_AVAILABLE_ELEMENTS_1();

  lcvm_int_element_t e;

  e.bytes[0] = lcvm_ProgramBuffer[lcvm_RegPC++];
  e.bytes[1] = lcvm_ProgramBuffer[lcvm_RegPC++];
  e.bytes[2] = lcvm_ProgramBuffer[lcvm_RegPC++];
  e.bytes[3] = lcvm_ProgramBuffer[lcvm_RegPC++];

  e.s32 += lcvm_RegFP;

  if (e.u32 > (LCVM_RAMBUFFER_SIZE - 2))
    LCVM_EXCEPTION(LCVM_EXCEPTION_MEMORY_OUT_OF_RANGE);

  lcvm_RAMBuffer[e.u32] = lcvm_OperationStack[lcvm_sp_op].bytes[0];
  lcvm_RAMBuffer[e.u32 + 1] = lcvm_OperationStack[lcvm_sp_op].bytes[1];
  lcvm_sp_op--;
}