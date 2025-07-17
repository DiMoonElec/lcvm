{
  // В коде программы должно быть доступно для чтения 2 байта
  CHECK_PROGRAM_AVAILABLE_BYTES_2();

  lcvm_short_element_t e;
  e.bytes[0] = lcvm_ProgramBuffer[lcvm_RegPC];
  e.bytes[1] = lcvm_ProgramBuffer[lcvm_RegPC + 1];

  lcvm_RegFP -= e.s16;
  lcvm_RegPC += 2;
}