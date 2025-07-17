{
  // В коде программы должен быть доступен для чтения 1 байт
  CHECK_PROGRAM_AVAILABLE_BYTES_1();

  // В стеке возврата должна быть свободна хотя бы одна ячейка
  CHECK_RETSTACK_ELEMENTS_FREE_1();

  // Сохраняем адрес возврата
  lcvm_ReturnStack[++lcvm_sp_ret] = lcvm_RegPC + 1;

  // Загружаем адрес вызываемой функции
  lcvm_RegPC += (int8_t)(lcvm_ProgramBuffer[lcvm_RegPC]);
}