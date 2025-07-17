{
  // В коде программы должен быть доступен для чтения 1 байт
  CHECK_PROGRAM_AVAILABLE_BYTES_1();

  lcvm_RegFP -= (int8_t)lcvm_ProgramBuffer[lcvm_RegPC];
  lcvm_RegPC++;
}