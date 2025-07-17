{
  // В памяти программ должен быть доступен хотя бы 4 байта, это относительный адрес для сохранения
  CHECK_PROGRAM_AVAILABLE_BYTES_4();

  // В стеке должен находиться 1 элемент, это значение для сохранения
  CHECK_OPSTACK_AVAILABLE_ELEMENTS_1();

  lcvm_int_element_t e;
  const uint8_t *p = lcvm_ProgramBuffer + lcvm_RegPC;
  lcvm_RegPC += 4;

  // Загружаем адрес
  e.bytes[0] = *(p++);
  e.bytes[1] = *(p++);
  e.bytes[2] = *(p++);
  e.bytes[3] = *(p++);
  e.s32 += lcvm_RegFP;

  // Проверяем, не выходит ли данный адрес за пределы ОЗУ
  if ((e.s32 < 0) || (e.s32 > LCVM_RAMBUFFER_SIZE - 4))
    LCVM_EXCEPTION(LCVM_EXCEPTION_MEMORY_OUT_OF_RANGE);

  lcvm_RAMBuffer[e.s32] = lcvm_OperationStack[lcvm_sp_op].bytes[0];
  lcvm_RAMBuffer[e.s32 + 1] = lcvm_OperationStack[lcvm_sp_op].bytes[1];
  lcvm_RAMBuffer[e.s32 + 2] = lcvm_OperationStack[lcvm_sp_op].bytes[2];
  lcvm_RAMBuffer[e.s32 + 3] = lcvm_OperationStack[lcvm_sp_op].bytes[3];
  lcvm_sp_op--;
}