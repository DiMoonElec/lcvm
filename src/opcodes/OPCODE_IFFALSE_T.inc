{
  // В коде программы должен быть доступен для чтения 1 байт
  CHECK_PROGRAM_AVAILABLE_BYTES_1();

  // В стеке должен находиться 1 элемент, это условие операции
  CHECK_OPSTACK_AVAILABLE_ELEMENTS_1();

  // Если условие выполняется, то загружаем адрес перехода
  if (lcvm_OperationStack[lcvm_sp_op].u32 == 0)
    lcvm_RegPC += (int8_t)(lcvm_ProgramBuffer[lcvm_RegPC]);
  else
    lcvm_RegPC += 1;

  lcvm_sp_op--;
}