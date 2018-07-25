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
}

void loop() {
  
  for (uint8_t y = 0; y < 8; y++){
    for (uint8_t x = 0; x < 8; x++){
      matrix[y][x] = 1;
        delay(100);
    }
  }
  for (uint8_t y = 8; y > 0; y--){
    for (uint8_t x = 8; x > 0; x--){
      matrix[y-1][x-1] = 0;
        delay(100);
    }
  }
}
