{
  // На стеке возврата должен быть доступен хотя бы 1 элемент
  if (lcvm_sp_ret < 0)
  {
    lcvm_State = LCVM_CORE_STATUS_STOP;
    return lcvm_State;
  }

  // Восстанавливаем адрес возврата
  lcvm_RegPC = lcvm_ReturnStack[lcvm_sp_ret--];
}