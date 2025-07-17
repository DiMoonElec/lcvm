{
  CHECK_OPSTACK_AVAILABLE_ELEMENTS_1();
  lcvm_OperationStack[lcvm_sp_op].s32 = (int32_t)lcvm_OperationStack[lcvm_sp_op].f;
}