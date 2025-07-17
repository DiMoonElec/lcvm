{
  // Загрузить значение по ссылке
  // ref -> value
  //  ref - абсолютный адрес ОЗУ, с которого будет прочитано значение
  //  value - uint16, прочитанное значение

  // На стеке должен находиться 1 элемент
  CHECK_OPSTACK_AVAILABLE_ELEMENTS_1();

  uint32_t adr = lcvm_OperationStack[lcvm_sp_op].u32;

  // Проверяем, не выходит ли данный адрес за пределы ОЗУ
  if (adr > LCVM_RAMBUFFER_SIZE - 2)
    LCVM_EXCEPTION(LCVM_EXCEPTION_MEMORY_OUT_OF_RANGE);

  lcvm_OperationStack[lcvm_sp_op].u32 = 0;
  lcvm_OperationStack[lcvm_sp_op].bytes[0] = lcvm_RAMBuffer[adr];
  lcvm_OperationStack[lcvm_sp_op].bytes[1] = lcvm_RAMBuffer[adr + 1];
}