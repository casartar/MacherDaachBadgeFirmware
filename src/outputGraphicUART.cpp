#include <string.h>
#include "outputGraphicsUART.h"
#include "main.h"

// helper function for mode-array
void outputGraphicsUART(){
  if (uartReceiveCompleteFlag) {
    strncpy((char*)matrix, (char*)uartInputBuffer,8);
    uartReceiveCompleteFlag = false;
  }
}
