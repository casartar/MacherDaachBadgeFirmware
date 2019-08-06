char outputShiftCurrent[UART_INPUT_BUFFER_SIZE];
char outputShiftNext[UART_INPUT_BUFFER_SIZE];
bool newDataAvailableFlag = false;
bool outputShiftCompleteFlag = true;

// helper function for mode-array
void outputShiftUART(){
  if (uartReceiveCompleteFlag) {
    // Received a whole new String from UART
    // Copy it to outputShiftNext so UART can receive a new String
    // outputShiftNext will always be overwritten there is no guarantee
    // the string will be displayed
    strcpy((char*)outputShiftNext, (char*)uartInputBuffer);
    newDataAvailableFlag = true;
    uartReceiveCompleteFlag = false;
  }
  if (outputShiftCompleteFlag && newDataAvailableFlag) {
    // New String in outputShiftNext available and
    // outputShiftUART function has shifted out outputShiftCurrent
    // so outputShiftCurrent is replaced by outputShiftNext
    // no corruption of the ongoing output shift
    newDataAvailableFlag = false;
    outputShiftCompleteFlag = false;
    strcpy((char*)outputShiftCurrent, (char*)outputShiftNext);
  }
  outputShiftUART(outputShiftCurrent,false);
}

//Shifts string through matrix
void outputShiftUART(char * text, bool newstart){
  char *t;
  //  static int i = startposition;
  static int i = 0;
  static int xOffset = 7;
  static int yOffset = 0;
  static bool fistrun = false;

   if (newstart == true){
     i = 0;
     fistrun = true;
    }
  
  /* iterate over text characters
   * loop takes car of two characters a the same time
  */

  if (countdown == 0){
    //remember last drawn char
    t = text;
    t = t + i;

    // if first character start from left side
    if (fistrun){
      xOffset=7;
      fistrun=false;
    }
    // draw char
    displayCharacterOffset(ASCII[(int)*t],xOffset,yOffset);
    
    // *********second charcter part***********
    if (xOffset < 0) {
      displayCharacterOffset(ASCII[(int)*(t+1)],xOffset+8,yOffset);
    }
    
    countdown = UART_SHIFT_SPEED_MS;
    
    //reset if end of string
    if(*t == '\0'){
      i = 0;     
      //xOffset=0;   
      fistrun = true;  
      outputShiftCompleteFlag = true;
    }
    // if charachter shift completed
    if(xOffset <= -8){
      xOffset=0;
      i++;
    }
    //set X offset for next cycle
    xOffset--;
  }
}
