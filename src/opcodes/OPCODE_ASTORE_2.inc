{
  // Созранить значение по ссылке
  // Состояние стека: ref, value -> .
  //  ref - абсолютный адрес ОЗУ, в который будет сохранено значение
  //  value - uint16, сохраняемое значение

  // На стеке должно лежать 2 элемента
  CHECK_OPSTACK_AVAILABLE_ELEMENTS_2();

  uint32_t adr = lcvm_OperationStack[lcvm_sp_op - 1].u32;

  // Проверяем, не выходит ли данный адрес за пределы ОЗУ
  if (adr > LCVM_RAMBUFFER_SIZE - 2)
    LCVM_EXCEPTION(LCVM_EXCEPTION_MEMORY_OUT_OF_RANGE);

  lcvm_RAMBuffer[adr] = lcvm_OperationStack[lcvm_sp_op].bytes[0];
  lcvm_RAMBuffer[adr + 1] = lcvm_OperationStack[lcvm_sp_op].bytes[1];

  lcvm_sp_op -= 2;
}