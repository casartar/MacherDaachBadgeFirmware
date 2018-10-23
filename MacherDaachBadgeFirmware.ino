#include "src/TimerOne/TimerOne.h"
#include "characters.h"


#define TEXT "ABCDEFabcdef1234567890"

#define ROW_ENABLE HIGH
#define ROW_DISABLE LOW
#define COLUMN_ON LOW
#define COLUMN_OFF HIGH

#define TEXT_SHIFT_SPEED_MS 50

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
#define PONG                    5
#define SNAKE                   6

#define OUTPUT_MODE_MAX         7

volatile uint8_t reqModeSwitch = 0;
volatile uint16_t countdown = 0;

uint8_t x = 0;
uint8_t y = 0;

#define TIMER_PERIOD_IN_MS   2

#define TIME_3_S              (3000/TIMER_PERIOD_IN_MS)
#define TIME_200_MS           (200/TIMER_PERIOD_IN_MS)
#define TIME_50_MS            (50/TIMER_PERIOD_IN_MS)
#define TIME_20_MS            (20/TIMER_PERIOD_IN_MS)
#define TIME_10_MS            (10/TIMER_PERIOD_IN_MS)

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

void loop() {
  //outputShiftString("123abc");
  //output_fill_matrix_slow();
  static uint8_t outputMode = 0;

  if (reqModeSwitch){
    // both buttons were pressed for 3 seconds
    reqModeSwitch = 0;

    // create a defined state and turn off all leds
    clear_matrix_immediatly();

    // switch output mode
    outputMode++;
    if (outputMode == OUTPUT_MODE_MAX) outputMode = 0;

    // Do initializations for a new output mode here if necessary
    switch (outputMode){
      case FILL_MATRIX_SLOW:
        break;
      case FILL_MATRIX_FAST:
        break;
      case FILL_MATRIX_SPIRAL:
        x = -1;
        break;
      default:
        break;
    }
  }

  // Call your output mode in this switch
  switch (outputMode){
    case FILL_MATRIX_SLOW:
      //outputShiftString(TEXT);
      //outputString(TEXT);
      //displayCharacterOffset(LETTERS[0],3,0);
      output_fill_matrix_slow();
      //output_fill_matrix_random();
      break;
    case FILL_MATRIX_FAST:
      output_fill_matrix_fast();
      break;
    case FILL_MATRIX_SPIRAL:
      output_fill_matrix_spiral();
      break;
    case FILL_MATRIX_RANDOM:
      output_fill_matrix_random();
      break;
    case OUTPUT_TEXT:
      outputShiftString(TEXT);
      break;
    case PONG:
      pong();
      break;
    case SNAKE:
      snake();
      break;
    default:
      break;
  }
}

