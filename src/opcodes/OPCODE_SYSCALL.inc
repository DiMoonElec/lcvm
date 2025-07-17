{
  // В коде программы должно быть доступно для чтения 2 байта
  CHECK_PROGRAM_AVAILABLE_BYTES_2();

  // id нативной функции
  lcvm_short_element_t e;
  e.bytes[0] = lcvm_ProgramBuffer[lcvm_RegPC];
  e.bytes[1] = lcvm_ProgramBuffer[lcvm_RegPC + 1];
  lcvm_RegPC += 2;

  // Обработчик системного вызова
  uint8_t result = lcvm_syscall(e.u16);

  if (result != LCVM_SYSCALL_RESULT_OK)
  {
    if (result == LCVM_SYSCALL_RESULT_INCORRECT_ID)
      lcvm_Exception = LCVM_EXCEPTION_INVALID_SYSCALL_ID;
    else
      lcvm_Exception = LCVM_EXCEPTION_INTERNAL_ERROR;
  }
}