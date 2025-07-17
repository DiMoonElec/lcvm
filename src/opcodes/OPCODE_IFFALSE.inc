{
  // В коде программы должно быть доступно для чтения 4 байта
  CHECK_PROGRAM_AVAILABLE_BYTES_4();

  // В стеке должен находиться 1 элемент, это условие операции
  CHECK_OPSTACK_AVAILABLE_ELEMENTS_1();

  // Если условие выполняется, то загружаем адрес перехода
  if (lcvm_OperationStack[lcvm_sp_op].u8 == 0)
  {
    lcvm_int_element_t e;
    e.bytes[0] = lcvm_ProgramBuffer[lcvm_RegPC];
    e.bytes[1] = lcvm_ProgramBuffer[lcvm_RegPC + 1];
    e.bytes[2] = lcvm_ProgramBuffer[lcvm_RegPC + 2];
    e.bytes[3] = lcvm_ProgramBuffer[lcvm_RegPC + 3];
    lcvm_RegPC = e.u32;
  }
  else
    lcvm_RegPC += 4;

  lcvm_sp_op--;
}