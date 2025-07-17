{
  CHECK_OPSTACK_AVAILABLE_ELEMENTS_1();
  CHECK_OPSTACK_ELEMENTS_FREE_1();

  lcvm_long_element_t op;
  op.s64 = lcvm_OperationStack[lcvm_sp_op].s16;

  lcvm_OperationStack[lcvm_sp_op].u32 = op.dwords[0];
  lcvm_sp_op++;
  lcvm_OperationStack[lcvm_sp_op].u32 = op.dwords[1];
}