{
  CHECK_OPSTACK_AVAILABLE_ELEMENTS_1();
  lcvm_OperationStack[lcvm_sp_op].u8 = (lcvm_OperationStack[lcvm_sp_op].f != 0);
}