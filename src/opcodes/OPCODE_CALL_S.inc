{
  // В коде программы должно быть доступно для чтения 2 байта
  CHECK_PROGRAM_AVAILABLE_BYTES_2();

  // В стеке возврата должна быть свободна хотя бы одна ячейка
  CHECK_RETSTACK_ELEMENTS_FREE_1();

  // Сохраняем адрес возврата
  lcvm_ReturnStack[++lcvm_sp_ret] = lcvm_RegPC + 2;

  // Загружаем адрес вызываемой функции
  lcvm_short_element_t e;
  e.bytes[0] = lcvm_ProgramBuffer[lcvm_RegPC];
  e.bytes[1] = lcvm_ProgramBuffer[lcvm_RegPC + 1];
  lcvm_RegPC += e.s16;
}