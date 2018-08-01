#include "TimerOne.h" 

#define ROW_ENABLE HIGH
#define ROW_DISABLE LOW
#define COLUMN_ON LOW
#define COLUMN_OFF HIGH

//                     Arduino   AVR    LED Matrix 
const uint8_t LED_X1 = 2;     // PD2    Pin 13
const uint8_t LED_X2 = 3;     // PD3    Pin  3
const uint8_t LED_X3 = 4;     // PD4    Pin  4
const uint8_t LED_X4 = 5;     // PD5    Pin 10
const uint8_t LED_X5 = 6;     // PD6    Pin  6
const uint8_t LED_X6 = 7;     // PD7    Pin 11
const uint8_t LED_X7 = 8;     // PB0    Pin 15
const uint8_t LED_X8 = 9;     // PB1    Pin 16

const uint8_t LED_Y8 = 14;    // PC0    Pin  9
const uint8_t LED_Y7 = 15;    // PC1    Pin 14
const uint8_t LED_Y6 = 16;    // PC2    Pin  8
const uint8_t LED_Y5 = 17;    // PC3    Pin 12
const uint8_t LED_Y4 = 18;    // PC4    Pin  1  
const uint8_t LED_Y3 = 19;    // PC5    Pin  7
const uint8_t LED_Y2 = 12;    // PB4    Pin  2
const uint8_t LED_Y1 = 13;    // PB5    Pin  5

const int button_1_Pin = 10;  // PB2        push button SW1
const int button_2_Pin = 11;  // PB3 (MOSI) push button SW2

typedef enum{
  BUTTON_PRESSED,
  BUTTON_HELD,
  BUTTON_RELEASED,
  BUTTON_INACTIVE,
}button_state;

volatile button_state button_1_state = BUTTON_INACTIVE;
volatile button_state button_2_state = BUTTON_INACTIVE;

uint8_t matrix[8][8] {
  0,0,0,0,0,0,0,0,
  0,0,0,0,0,0,0,0,
  0,0,0,0,0,0,0,0,
  0,0,0,0,0,0,0,0,
  0,0,0,0,0,0,0,0,
  0,0,0,0,0,0,0,0,
  0,0,0,0,0,0,0,0,
  0,0,0,0,0,0,0,0,
};

typedef enum {
  DO_NOTHING,
  FILL_MATRIX_SLOW,
  FILL_MATRIX_FAST,
  CLEAR_MATRIX_SLOW,
  CLEAR_MATRIX_FAST,
} actionType;

volatile uint16_t countdown = 0;

void setup() {
  pinMode(LED_X1, OUTPUT);
  pinMode(LED_X2, OUTPUT);
  pinMode(LED_X3, OUTPUT);
  pinMode(LED_X4, OUTPUT);
  pinMode(LED_X5, OUTPUT);
  pinMode(LED_X6, OUTPUT);
  pinMode(LED_X7, OUTPUT);
  pinMode(LED_X8, OUTPUT);

  pinMode(LED_Y1, OUTPUT);
  pinMode(LED_Y2, OUTPUT);
  pinMode(LED_Y3, OUTPUT);
  pinMode(LED_Y4, OUTPUT);
  pinMode(LED_Y5, OUTPUT);
  pinMode(LED_Y6, OUTPUT);
  pinMode(LED_Y7, OUTPUT);
  pinMode(LED_Y8, OUTPUT);

  digitalWrite(LED_X1, ROW_DISABLE);
  digitalWrite(LED_X2, ROW_DISABLE);
  digitalWrite(LED_X3, ROW_DISABLE);
  digitalWrite(LED_X4, ROW_DISABLE);
  digitalWrite(LED_X5, ROW_DISABLE);
  digitalWrite(LED_X6, ROW_DISABLE);
  digitalWrite(LED_X7, ROW_DISABLE);
  digitalWrite(LED_X8, ROW_DISABLE);

  digitalWrite(LED_Y1, COLUMN_OFF);
  digitalWrite(LED_Y2, COLUMN_OFF);
  digitalWrite(LED_Y3, COLUMN_OFF);
  digitalWrite(LED_Y4, COLUMN_OFF);
  digitalWrite(LED_Y5, COLUMN_OFF);
  digitalWrite(LED_Y6, COLUMN_OFF);
  digitalWrite(LED_Y7, COLUMN_OFF);
  digitalWrite(LED_Y8, COLUMN_OFF);

  pinMode(button_1_Pin, INPUT_PULLUP);
  pinMode(button_2_Pin, INPUT_PULLUP);

  Timer1.initialize();
  Timer1.attachInterrupt(display, 2000);
}

void display() {

  // LED Matrix multiplexing
  static uint8_t state = 0;

  digitalWrite(LED_X1, ROW_DISABLE);
  digitalWrite(LED_X2, ROW_DISABLE);
  digitalWrite(LED_X3, ROW_DISABLE);
  digitalWrite(LED_X4, ROW_DISABLE);
  digitalWrite(LED_X5, ROW_DISABLE);
  digitalWrite(LED_X6, ROW_DISABLE);
  digitalWrite(LED_X7, ROW_DISABLE);
  digitalWrite(LED_X8, ROW_DISABLE);

  if (matrix[0][state] != 0)
    digitalWrite(LED_Y1, COLUMN_ON);
  else
    digitalWrite(LED_Y1, COLUMN_OFF);
    
  if (matrix[1][state] != 0)
    digitalWrite(LED_Y2, COLUMN_ON);
  else
    digitalWrite(LED_Y2, COLUMN_OFF);
  
  if (matrix[2][state] != 0)
    digitalWrite(LED_Y3, COLUMN_ON);
  else
    digitalWrite(LED_Y3, COLUMN_OFF);
  
  if (matrix[3][state] != 0)
    digitalWrite(LED_Y4, COLUMN_ON);
  else
    digitalWrite(LED_Y4, COLUMN_OFF);
  
  if (matrix[4][state] != 0)
    digitalWrite(LED_Y5, COLUMN_ON);
  else
    digitalWrite(LED_Y5, COLUMN_OFF);
  
  if (matrix[5][state] != 0)
    digitalWrite(LED_Y6, COLUMN_ON);
  else
    digitalWrite(LED_Y6, COLUMN_OFF);
  
  if (matrix[6][state] != 0)
    digitalWrite(LED_Y7, COLUMN_ON);
  else
    digitalWrite(LED_Y7, COLUMN_OFF);
  
  if (matrix[7][state] != 0)
    digitalWrite(LED_Y8, COLUMN_ON);
  else
    digitalWrite(LED_Y8, COLUMN_OFF);

  switch (state){
    case 0:
      digitalWrite(LED_X1, ROW_ENABLE);
      state = 1;
      break;
    case 1:
      digitalWrite(LED_X2, ROW_ENABLE);
      state = 2;
      break;
    case 2:
      digitalWrite(LED_X3, ROW_ENABLE);
      state = 3;
      break;
    case 3:
      digitalWrite(LED_X4, ROW_ENABLE);
      state = 4;
      break;
    case 4:
      digitalWrite(LED_X5, ROW_ENABLE);
      state = 5;
      break;
    case 5:
      digitalWrite(LED_X6, ROW_ENABLE);
      state = 6;
      break;
    case 6:
      digitalWrite(LED_X7, ROW_ENABLE);
      state = 7;
      break;
    case 7 :
      digitalWrite(LED_X8, ROW_ENABLE);
      state = 0;
      break;
  }
  
  // Debouncing push buttons
  static uint8_t debounce_timer_1 = 0;
  static uint8_t debounce_timer_2 = 0;

  uint8_t val;

  if (debounce_timer_1 > 0) debounce_timer_1--;
  if (debounce_timer_1 == 0){
    val = digitalRead(button_1_Pin);
    if (button_1_state == BUTTON_INACTIVE && val == LOW){
      debounce_timer_1 = 50;  // 50ms
      button_1_state = BUTTON_PRESSED;
      //button_1_pressed = 1;
    }
    else if (button_1_state == BUTTON_PRESSED && val == LOW){
      button_1_state = BUTTON_HELD;
      //button_1_pressed = 0;
    }
    else if (button_1_state == BUTTON_HELD && val == HIGH){
      debounce_timer_1 = 50;  // 50ms
      button_1_state = BUTTON_RELEASED;
      //button_1_pressed = 0;
    }
    else if (button_1_state == BUTTON_RELEASED && val == HIGH){
      button_1_state = BUTTON_INACTIVE;
      //button_1_pressed = 0;
    }
  }

  if (debounce_timer_2 > 0) debounce_timer_2--;
  if (debounce_timer_2 == 0){
    val = digitalRead(button_2_Pin);
    if (button_2_state == BUTTON_INACTIVE && val == LOW){
      debounce_timer_2 = 50;  // 50ms
      button_2_state = BUTTON_PRESSED;
      //button_2_pressed = 1;
    }
    else if (button_2_state == BUTTON_PRESSED && val == LOW){
      button_2_state = BUTTON_HELD;
      //button_2_pressed = 0;
    }
    else if (button_2_state == BUTTON_HELD && val == HIGH){
      debounce_timer_2 = 50;  // 50ms
      button_2_state = BUTTON_RELEASED;
      //button_2_pressed = 0;
    }
    else if (button_2_state == BUTTON_RELEASED && val == HIGH){
      button_2_state = BUTTON_INACTIVE;
      //button_2_pressed = 0;
    }
  }

  // Countdown
  if (countdown > 0) countdown--;
}

void loop() {
  static uint8_t x = 0;
  static uint8_t y = 0;
  static actionType reqAction = DO_NOTHING;

  if (button_1_state == BUTTON_HELD && button_2_state == BUTTON_PRESSED){
    reqAction = FILL_MATRIX_SLOW;
    x = 0;
    y = 0;
  }
  if (button_1_state == BUTTON_PRESSED && button_2_state == BUTTON_HELD){
    reqAction = CLEAR_MATRIX_SLOW;
    x = 8;
    y = 8;
  }
  if (button_1_state == BUTTON_INACTIVE && button_2_state == BUTTON_PRESSED){
    reqAction = FILL_MATRIX_FAST;
    x = 0;
    y = 0;
  }
  if (button_1_state == BUTTON_PRESSED && button_2_state == BUTTON_INACTIVE){
    reqAction = CLEAR_MATRIX_FAST;
    x = 8;
    y = 8;
  }

  if (reqAction == FILL_MATRIX_SLOW){  
    if (countdown == 0){
      matrix[y][x] = 1;
      x++;
      if (x > 7){
        x = 0;
        y++;
        if (y > 7){
          reqAction = DO_NOTHING;
        }
      }
      countdown = 100;
    }
  }
  else if (reqAction == CLEAR_MATRIX_SLOW){  
    if (countdown == 0){
      matrix[y-1][x-1] = 0;
      x--;
      if (x == 0){
        x = 8;
        y--;
        if (y == 0){
          reqAction = DO_NOTHING;
        }
      }
      countdown = 100;
    }
  }
  else if (reqAction == FILL_MATRIX_FAST){  
    if (countdown == 0){
      matrix[y][x] = 1;
      x++;
      if (x > 7){
        x = 0;
        y++;
        if (y > 7){
          reqAction = DO_NOTHING;
        }
      }
      countdown = 10;
    }
  }
  else if (reqAction == CLEAR_MATRIX_FAST){  
    if (countdown == 0){
      matrix[y-1][x-1] = 0;
      x--;
      if (x == 0){
        x = 8;
        y--;
        if (y == 0){
          reqAction = DO_NOTHING;
        }
      }
      countdown = 10;
    }
  }
}
