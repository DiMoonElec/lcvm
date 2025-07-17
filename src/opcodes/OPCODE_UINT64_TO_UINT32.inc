{
  CHECK_OPSTACK_AVAILABLE_ELEMENTS_2();

  lcvm_long_element_t op;
  op.dwords[1] = lcvm_OperationStack[lcvm_sp_op].u32;
  lcvm_sp_op--;
  op.dwords[0] = lcvm_OperationStack[lcvm_sp_op].u32;

  lcvm_OperationStack[lcvm_sp_op].u8 = (int8_t)op.u64;
}