{
  // На стеке должен находиться хотя бы 1 элемент
  CHECK_OPSTACK_AVAILABLE_ELEMENTS_1();

  // На стеке должен быть свободен хотя бы 1 элемент
  CHECK_OPSTACK_ELEMENTS_FREE_1();

  lcvm_OperationStack[lcvm_sp_op + 1].u32 = lcvm_OperationStack[lcvm_sp_op].u32;
  lcvm_sp_op++;
}