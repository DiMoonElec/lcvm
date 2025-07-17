{
  // Созранить значение по ссылке
  // Состояние стека: ref, value0 value1 -> .
  //  ref - абсолютный адрес ОЗУ, в который будет сохранено значение
  //  value0, value1 - uint64, сохраняемое значение

  // На стеке должно лежать 3 элемента
  CHECK_OPSTACK_AVAILABLE_ELEMENTS_3();

  uint32_t adr = lcvm_OperationStack[lcvm_sp_op - 2].u32;

  // Проверяем, не выходит ли данный адрес за пределы ОЗУ
  if (adr > LCVM_RAMBUFFER_SIZE - 8)
    LCVM_EXCEPTION(LCVM_EXCEPTION_MEMORY_OUT_OF_RANGE);

  lcvm_RAMBuffer[adr] = lcvm_OperationStack[lcvm_sp_op - 1].bytes[0];
  lcvm_RAMBuffer[adr + 1] = lcvm_OperationStack[lcvm_sp_op - 1].bytes[1];
  lcvm_RAMBuffer[adr + 2] = lcvm_OperationStack[lcvm_sp_op - 1].bytes[2];
  lcvm_RAMBuffer[adr + 3] = lcvm_OperationStack[lcvm_sp_op - 1].bytes[3];

  lcvm_RAMBuffer[adr + 4] = lcvm_OperationStack[lcvm_sp_op].bytes[0];
  lcvm_RAMBuffer[adr + 5] = lcvm_OperationStack[lcvm_sp_op].bytes[1];
  lcvm_RAMBuffer[adr + 6] = lcvm_OperationStack[lcvm_sp_op].bytes[2];
  lcvm_RAMBuffer[adr + 7] = lcvm_OperationStack[lcvm_sp_op].bytes[3];

  lcvm_sp_op -= 2;
}