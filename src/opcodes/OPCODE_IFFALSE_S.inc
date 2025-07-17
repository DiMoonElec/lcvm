{
  // В коде программы должно быть доступно для чтения 2 байта
  CHECK_PROGRAM_AVAILABLE_BYTES_2();

  // В стеке должен находиться 1 элемент, это условие операции
  CHECK_OPSTACK_AVAILABLE_ELEMENTS_1();

  // Если условие выполняется, то загружаем адрес перехода
  if (lcvm_OperationStack[lcvm_sp_op].u32 == 0)
  {
    lcvm_short_element_t e;
    e.bytes[0] = lcvm_ProgramBuffer[lcvm_RegPC];
    e.bytes[1] = lcvm_ProgramBuffer[lcvm_RegPC + 1];
    lcvm_RegPC += e.s16;
  }
  else
    lcvm_RegPC += 2;

  lcvm_sp_op--;
}