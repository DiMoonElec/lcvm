{
  // В коде программы должeн быть доступeн для чтения 1 байт
  CHECK_PROGRAM_AVAILABLE_BYTES_1();

  lcvm_RegPC += (int8_t)(lcvm_ProgramBuffer[lcvm_RegPC]);
}