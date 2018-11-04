void display() {
  // LED Matrix multiplexing
  static uint8_t state = 0;
  
  if (state==0) {
    digitalWrite(LED_X[7], ROW_DISABLE);
  } else {
    digitalWrite(LED_X[state-1], ROW_DISABLE);
  }

  //digitalWrite(LED_Y1, !matrix[0][state]);
  setRow(~matrix[state]); 
  digitalWrite(LED_X[state], ROW_ENABLE);

  if (state == 7) {
    state = 0;
  } else {
    state += 1;
  }

  
  // Debouncing push buttons
  static uint8_t debounce_timer_1 = 0;
  static uint8_t debounce_timer_2 = 0;

  uint8_t val;

  if (debounce_timer_1 > 0) {
    debounce_timer_1--;
  } else {
    val = digitalRead(button_1_Pin);
    if ((button_1_state == BUTTON_INACTIVE) && (val == LOW)){
        debounce_timer_1 = TIME_50_MS;   // 50ms
        button_1_state = BUTTON_PRESSED;
    } else if (button_1_state == BUTTON_PRESSED){ // aka 50MS later ...
      if (val == LOW){
        button_1_state = BUTTON_HELD; // now, this counts
        debounce_timer_1 = TIME_20_MS;  // --> read button every 20ms
      } else {
        button_1_state = BUTTON_INACTIVE; // nope, just a glitch
      }
    } else if (button_1_state == BUTTON_HELD){
      if (val == HIGH){
        debounce_timer_1 = TIME_50_MS;  // 50ms
        button_1_state = BUTTON_RELEASED;
      } else {
        debounce_timer_1 = TIME_20_MS;  // --> read button only every 20ms
      }
    } else if (button_1_state == BUTTON_RELEASED){
      if (val == HIGH){
        button_1_state = BUTTON_INACTIVE; // yep, it's released
      } else {
        button_1_state = BUTTON_HELD; // nope, just a glitch
      }
    }
  }

  if (debounce_timer_2 > 0) {
    debounce_timer_2--;
  } else {
    val = digitalRead(button_2_Pin);
    if ((button_2_state == BUTTON_INACTIVE) && (val == LOW)){
        debounce_timer_2 = TIME_50_MS;   // 50ms
        button_2_state = BUTTON_PRESSED;
    } else if (button_2_state == BUTTON_PRESSED){ // aka 50MS later ...
      if (val == LOW){
        button_2_state = BUTTON_HELD; // now, this counts
        debounce_timer_2 = TIME_20_MS;  // --> read button every 20ms while on hold
      } else {
        button_2_state = BUTTON_INACTIVE; // nope, just a glitch
      }
    } else if (button_2_state == BUTTON_HELD){
      if (val == HIGH){
        debounce_timer_2 = TIME_50_MS;  // 50ms
        button_2_state = BUTTON_RELEASED;
      } else {
        debounce_timer_2 = TIME_20_MS;  // --> read button only every 20ms while on hold
      }
    } else if (button_2_state == BUTTON_RELEASED){
      if (val == HIGH){
        button_2_state = BUTTON_INACTIVE; // yep, it's released
      } else {
        button_2_state = BUTTON_HELD; // nope, just a glitch
      }
    }
  }

  static uint16_t mode_switch_timer = 0;

  if (button_1_state == BUTTON_HELD
   && button_2_state == BUTTON_HELD){
    mode_switch_timer++;
    if (mode_switch_timer == SWITCH_TIME * TIME_1_S) {
      reqModeSwitch = 1;
    }
  }
  else{
    mode_switch_timer = 0;
  }
  
  // Countdown
  if (countdown > 0) countdown--;
}

// Helper functions
void clear_matrix_immediatly(){
  memset(matrix, 0, 8*sizeof(*matrix));
  x = 0;
  y = 0;
}

// Helper functions
void clear_matrix_immediatly_without_reset(){
  memset(matrix, 0, 8*sizeof(*matrix));
}

void matrixSetPixel(byte x, byte y, bool value){
  bitWrite(matrix[x], y, value);
}

bool matrixGetPixel(byte x, byte y){
  return bitRead(matrix[y], x);
}

void matrixShiftUp() {
  for (uint8_t y=0; y<8; y++) {
    matrix[y]<<=1;
  }
}

void matrixShiftDown() {
  for (uint8_t y=0; y<8; y++) {
    matrix[y]>>=1;
  }
}

void matrixShiftLeft(uint8_t newColumn) {
  for (uint8_t y=0; y<7; y++) {
    matrix[y]=matrix[y+1];
  }
  matrix[7]= newColumn;
}

void matrixShiftRight(uint8_t newColumn) {
  for (uint8_t y=0; y<7; y++) {
    matrix[y+1]=matrix[y];
  }
  matrix[0]= newColumn;
}

void setRow(uint8_t values){
  uint8_t portcValues = values & B00111111; //remove the last 2 Bits from value
  uint8_t portbValues = values & B11000000; //remove the first 6 Bits from value
  
  PORTC       = PORTC  & B11000000; //reset PORTC but not PC6 and PC7
  PORTC       = portcValues | PORTC; // final PORTC values

  PORTB       = PORTB & B11001111; //reset PORTB but only PB4 and PB5
  portbValues = portbValues >> 2 ;
  PORTB       = portbValues | PORTB; // final PORTB values
}

void displayCharacter(const byte* image) {
  // this is just bad and needs fixing!
  displayCharacterOffset(image, 0, 0);
}

void displayCharacterOffset(const byte* image, int8_t x, int8_t y) {

  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      if(((j+x) >= 0 && (j+x) < 8) && ((i+y) >= 0 && (i+y) < 8)){
        // set pixel
        //matrix[8-(i+y)] = pgm_read_byte_near(image + i);
        matrixSetPixel(j+x,7-(i+y), bitRead(pgm_read_byte_near(image + i),7-j));
        //matrix[i+y][j+x] = bitRead(image[i],7-j);
      }
    }
  }
}
