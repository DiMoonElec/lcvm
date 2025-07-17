{
  // В коде программы должен быть доступен для чтения 1 байт
  CHECK_PROGRAM_AVAILABLE_BYTES_1();

  // id нативной функции
  uint8_t fid = lcvm_ProgramBuffer[lcvm_RegPC];
  lcvm_RegPC++;

  // Обработчик системного вызова
  uint8_t result = lcvm_syscall((uint16_t)fid);

  if (result != LCVM_SYSCALL_RESULT_OK)
  {
    if (result == LCVM_SYSCALL_RESULT_INCORRECT_ID)
      lcvm_Exception = LCVM_EXCEPTION_INVALID_SYSCALL_ID;
    else
      lcvm_Exception = LCVM_EXCEPTION_INTERNAL_ERROR;
  }
}