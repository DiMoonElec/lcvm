{
  // В стеке должен находиться 1 элемент, это адрес вызываемой подпрограммы
  CHECK_OPSTACK_AVAILABLE_ELEMENTS_1();

  // В стеке возврата должна быть свободна хотя бы одна ячейка
  CHECK_RETSTACK_ELEMENTS_FREE_1();

  // Сохраняем адрес возврата
  lcvm_ReturnStack[++lcvm_sp_ret] = lcvm_RegPC;

  lcvm_RegPC = lcvm_OperationStack[lcvm_sp_op].u32;
  lcvm_sp_op--;
}