{
  CHECK_OPSTACK_AVAILABLE_ELEMENTS_2();

  lcvm_long_element_t op;
  op.dwords[0] = lcvm_OperationStack[lcvm_sp_op - 1].u32;
  op.dwords[1] = lcvm_OperationStack[lcvm_sp_op].u32;

  op.d = (double)op.u64;

  lcvm_OperationStack[lcvm_sp_op - 1].u32 = op.dwords[0];
  lcvm_OperationStack[lcvm_sp_op].u32 = op.dwords[1];
}