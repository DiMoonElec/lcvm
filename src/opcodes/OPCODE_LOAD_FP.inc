{
  // В стеке должен быть место для загрузки в него 1 элемента
  CHECK_OPSTACK_ELEMENTS_FREE_1();

  lcvm_sp_op++;
  lcvm_OperationStack[lcvm_sp_op].u32 = lcvm_RegFP;
}