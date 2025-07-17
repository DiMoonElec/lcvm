{
  // На стеке должно находиться хотя бы 2 элемента
  CHECK_OPSTACK_AVAILABLE_ELEMENTS_2();

  // На стеке должно быть свободо хотя бы 2 элемента
  CHECK_OPSTACK_ELEMENTS_FREE_2();

  lcvm_OperationStack[lcvm_sp_op + 1].u32 = lcvm_OperationStack[lcvm_sp_op - 1].u32;
  lcvm_OperationStack[lcvm_sp_op + 2].u32 = lcvm_OperationStack[lcvm_sp_op].u32;
  lcvm_sp_op += 2;
}