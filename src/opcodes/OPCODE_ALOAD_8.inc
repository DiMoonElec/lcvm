{
  // Загрузить значение по ссылке
  // ref -> value0 value1
  //  ref - абсолютный адрес ОЗУ, с которого будет прочитано значение
  //  value0 value1 - uint64, прочитанное значение

  // На стеке должен находиться 1 элемент
  CHECK_OPSTACK_AVAILABLE_ELEMENTS_1();
  
  // На стеке должен быть свободным 1 элемент
  CHECK_OPSTACK_ELEMENTS_FREE_1();

  uint32_t adr = lcvm_OperationStack[lcvm_sp_op].u32;

  // Проверяем, не выходит ли данный адрес за пределы ОЗУ
  if (adr > LCVM_RAMBUFFER_SIZE - 8)
    LCVM_EXCEPTION(LCVM_EXCEPTION_MEMORY_OUT_OF_RANGE);

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