{
  // В стеке должно быть хотя бы две свободных ячейки
  CHECK_OPSTACK_ELEMENTS_FREE_2();

  // В памяти программ должен быть доступен хотя бы 8 байт
  CHECK_PROGRAM_AVAILABLE_BYTES_8();

  lcvm_sp_op++;
  lcvm_OperationStack[lcvm_sp_op].bytes[0] = lcvm_ProgramBuffer[lcvm_RegPC++];
  lcvm_OperationStack[lcvm_sp_op].bytes[1] = lcvm_ProgramBuffer[lcvm_RegPC++];
  lcvm_OperationStack[lcvm_sp_op].bytes[2] = lcvm_ProgramBuffer[lcvm_RegPC++];
  lcvm_OperationStack[lcvm_sp_op].bytes[3] = lcvm_ProgramBuffer[lcvm_RegPC++];

  lcvm_sp_op++;
  lcvm_OperationStack[lcvm_sp_op].bytes[0] = lcvm_ProgramBuffer[lcvm_RegPC++];
  lcvm_OperationStack[lcvm_sp_op].bytes[1] = lcvm_ProgramBuffer[lcvm_RegPC++];
  lcvm_OperationStack[lcvm_sp_op].bytes[2] = lcvm_ProgramBuffer[lcvm_RegPC++];
  lcvm_OperationStack[lcvm_sp_op].bytes[3] = lcvm_ProgramBuffer[lcvm_RegPC++];
}