char outputShiftText[UART_INPUT_BUFFER_SIZE];

// helper function for mode-array
void outputShiftUART(){
  if (uartReceiveCompleteFlag) {
    strcpy((char*)outputShiftText, (char*)uartInputBuffer);
    outputShiftUART(outputShiftText, true);
    uartReceiveCompleteFlag = false;
  }
  outputShiftUART(outputShiftText,false);
}

//Shifts string through matrix
void outputShiftUART(char * text, bool newstart){
  char *t;
//  static int i = startposition;
   static int i = 0;
   static int xOffset = -1;
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
    }
    // if charachter shift completed
    if(xOffset <= -9){
      xOffset=-1;
      i++;
    }
    //set X offset for next cycle
    xOffset--;
  }
}
