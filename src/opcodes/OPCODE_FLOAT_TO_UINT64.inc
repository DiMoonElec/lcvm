{
  CHECK_OPSTACK_AVAILABLE_ELEMENTS_1();
  CHECK_OPSTACK_ELEMENTS_FREE_1();

  lcvm_long_element_t op;
  op.u64 = (int64_t)lcvm_OperationStack[lcvm_sp_op].f;

  lcvm_OperationStack[lcvm_sp_op].u32 = op.dwords[0];
  lcvm_sp_op++;
  lcvm_OperationStack[lcvm_sp_op].u32 = op.dwords[1];
}