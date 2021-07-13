#include "main.h"
#include "outputGraphicsUART.h"
#include <string.h>

// helper function for mode-array
void outputGraphicsUART()
{
    if (uartReceiveCompleteFlag) {
        strncpy((char*)matrix, (char*)uartInputBuffer, 8);
        uartReceiveCompleteFlag = false;
    }
}
