#include "src/TimerOne/TimerOne.h"
#include "characters.h"

#define ROW_ENABLE HIGH
#define ROW_DISABLE LOW
#define COLUMN_ON LOW
#define COLUMN_OFF HIGH

#define TEXT "ABCDEabcde1234567890"
#define TEXT_SHIFT_SPEED_MS 80

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

const uint8_t LED_X[8] = {LED_X1, LED_X2, LED_X3, LED_X4, LED_X5, LED_X6, LED_X7, LED_X8};
const uint8_t LED_Y[8] = {LED_Y1, LED_Y2, LED_Y3, LED_Y4, LED_Y5, LED_Y6, LED_Y7, LED_Y8};

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

uint8_t matrix[8] {
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000
};

// Add here a define for your output mode and increase OUTPUT_MODE_MAX accordingly
#define FILL_MATRIX_SLOW        0
#define FILL_MATRIX_FAST        1
#define FILL_MATRIX_SPIRAL      2
#define FILL_MATRIX_RANDOM      3
#define OUTPUT_TEXT             4

#define OUTPUT_MODE_MAX         5

volatile uint8_t reqModeSwitch = 0;
volatile uint16_t countdown = 0;

uint8_t x = 0;
uint8_t y = 0;

#define TIMER_PERIOD_IN_MS   2

#define TIME_3_S              (3000/TIMER_PERIOD_IN_MS)
#define TIME_200_MS           (200/TIMER_PERIOD_IN_MS)
#define TIME_50_MS            (50/TIMER_PERIOD_IN_MS)
#define TIME_20_MS            (20/TIMER_PERIOD_IN_MS)

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
  // The display function gets called every 2 ms
  Timer1.attachInterrupt(display, TIMER_PERIOD_IN_MS*1000);
}

void display() {

  // LED Matrix multiplexing
  static uint8_t state = 0;
  
  if (state==0) {
    digitalWrite(LED_X[7], ROW_DISABLE);
  } else {
    digitalWrite(LED_X[state-1], ROW_DISABLE);
  }

  //digitalWrite(LED_Y1, !matrix[0][state]);
  /*
  digitalWrite(LED_Y1, !bitRead(matrix[0],state));
  digitalWrite(LED_Y2, !bitRead(matrix[1],state));
  digitalWrite(LED_Y3, !bitRead(matrix[2],state));
  digitalWrite(LED_Y4, !bitRead(matrix[3],state));
  digitalWrite(LED_Y5, !bitRead(matrix[4],state));
  digitalWrite(LED_Y6, !bitRead(matrix[5],state));
  digitalWrite(LED_Y7, !bitRead(matrix[6],state));
  digitalWrite(LED_Y8, !bitRead(matrix[7],state));
  */ 
  setRow(~matrix[state]); 
  digitalWrite(LED_X[state], ROW_ENABLE);

  if (state == 7) {
    state = 0;
  } else {
    state += 1;
  }
  
  // Countdown
  if (countdown > 0) countdown--;
}

void loop() {
  output_fill_matrix_slow();
}

// output mode functions
void output_fill_matrix_slow(){
  if (countdown == 0){
    // set pixel
    //clear_matrix_immediatly_without_reset();
    matrixSetPixel(x,y, true);
    x++;
    if (x > 7){
      x = 0;
      y++;
      if (y > 7){
        clear_matrix_immediatly();
      }
    }
    countdown = TIME_200_MS;
  }
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

void setRow(uint8_t values){
    uint8_t portcValues = values & B00111111; //remove the last 2 Bits from value
    uint8_t portbValues = values & B11000000; //remove the last 2 Bits from value
    
    PORTC       = PORTC  & B11000000; //reset PORTC but not PC6 and PC7
    PORTC       = portcValues | PORTC; // final PORTC values

    PORTB       = PORTB & B11001111;
    portbValues = portbValues >> 2 ;
    PORTB       = portbValues | PORTB;
}
