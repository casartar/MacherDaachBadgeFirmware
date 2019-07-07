// helper function for mode-array
void outputGraphicsUART(){
  if (uartReceiveCompleteFlag) {
    strcpy((char*)matrix, (char*)uartInputBuffer);
    uartReceiveCompleteFlag = false;
  }
}
