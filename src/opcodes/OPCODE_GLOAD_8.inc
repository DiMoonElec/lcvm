{
  // В памяти программ должен быть доступен хотя бы 4 байта, это относительный адрес для сохранения
  CHECK_PROGRAM_AVAILABLE_BYTES_4();

  // В стеке должен быть место для загрузки в него 1 элемента
  CHECK_OPSTACK_ELEMENTS_FREE_2();

  lcvm_int_element_t e;
  const uint8_t *p = lcvm_ProgramBuffer + lcvm_RegPC;
  lcvm_RegPC += 4;

  // Загружаем адрес
  e.bytes[0] = *(p++);
  e.bytes[1] = *(p++);
  e.bytes[2] = *(p++);
  e.bytes[3] = *(p++);

  uint32_t adr = e.u32;
  // Проверяем, не выходит ли данный адрес за пределы ОЗУ
  if (adr > LCVM_RAMBUFFER_SIZE - 8)
    LCVM_EXCEPTION(LCVM_EXCEPTION_MEMORY_OUT_OF_RANGE);

  lcvm_sp_op++;
  lcvm_OperationStack[lcvm_sp_op].bytes[0] = lcvm_RAMBuffer[adr];
  lcvm_OperationStack[lcvm_sp_op].bytes[1] = lcvm_RAMBuffer[adr + 1];
  lcvm_OperationStack[lcvm_sp_op].bytes[2] = lcvm_RAMBuffer[adr + 2];
  lcvm_OperationStack[lcvm_sp_op].bytes[3] = lcvm_RAMBuffer[adr + 3];

  lcvm_sp_op++;
  lcvm_OperationStack[lcvm_sp_op].bytes[0] = lcvm_RAMBuffer[adr + 4];
  lcvm_OperationStack[lcvm_sp_op].bytes[1] = lcvm_RAMBuffer[adr + 5];
  lcvm_OperationStack[lcvm_sp_op].bytes[2] = lcvm_RAMBuffer[adr + 6];
  lcvm_OperationStack[lcvm_sp_op].bytes[3] = lcvm_RAMBuffer[adr + 7];
}