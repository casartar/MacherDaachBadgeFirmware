#include "src/TimerOne/TimerOne.h"
#include "characters.h"
#include <string.h>
/* --------- --------- --------- ---------
 *  configure your badge in this section:
 */

// the text to display in OutputShiftString-Mode:
#define TEXT "MacherDaach 2019"
#define UART_SHIFT_SPEED_MS 40
#define TEXT_SHIFT_SPEED_MS 40

// Output modes and their order
#define NUM_OF_MODES  7
// Mode to display
static uint8_t outputMode = 0;

void (*output_functions[NUM_OF_MODES])() {
  outputShiftString,
  output_fill_matrix_spiral,
  output_fill_matrix_random,
  pong,
  snake,
  outputGraphicsUART,
  outputShiftUART
};

// Initializers to output modes (if necessary)
void (*initializer_functions[NUM_OF_MODES])() {
  nop,
  output_init_matrix_spiral,
  nop,
  pong_intro,
  snake_intro,
  nop,
  nop
};

// switch modes after pressing both buttons for this many seconds
#define SWITCH_TIME 2

/* --------- --------- --------- ---------
 * general Setup of the badge hardware
 */
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

volatile uint8_t reqModeSwitch = 0;
volatile uint16_t countdown = 0;

uint8_t x = 0;
uint8_t y = 0;

#define TIMER_PERIOD_IN_MS   2

#define TIME_1_S              (1000/TIMER_PERIOD_IN_MS)
#define TIME_200_MS           (200/TIMER_PERIOD_IN_MS)
#define TIME_50_MS            (50/TIMER_PERIOD_IN_MS)
#define TIME_20_MS            (20/TIMER_PERIOD_IN_MS)
#define TIME_10_MS            (10/TIMER_PERIOD_IN_MS)

#define UART_INPUT_BUFFER_SIZE 256 
volatile char uartInputBuffer[UART_INPUT_BUFFER_SIZE];         // a String to hold incoming data
volatile bool uartReceiveCompleteFlag = false;

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
  Serial.begin(9600);
  
  Timer1.initialize();
  // The display function gets called every 2 ms
  Timer1.attachInterrupt(display, TIMER_PERIOD_IN_MS*1000);

  // call initializer of first mode
  initializer_functions[0]();
}

void loop() {
  //outputShiftString("123abc");
  //output_fill_matrix_slow();

  if (reqModeSwitch){
    // both buttons were pressed for 3 seconds
    reqModeSwitch = 0;

    // create a defined state and turn off all leds
    clear_matrix_immediatly();

    // switch output mode
    outputMode++;
    // Check if max was reached, ignore last two modes (only available over uart)
    if (outputMode == NUM_OF_MODES-2) {
      outputMode = 0;
    }

    // Do initializations for a new output mode here if necessary
    initializer_functions[outputMode]();
    }

  // Call your output mode in this switch
  output_functions[outputMode]();
}

// Helper function for output_mode array
void nop() { }

void serialEvent() {
  static uint8_t index = 0;
  while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read();
    if (index == UART_INPUT_BUFFER_SIZE-1) {
      // Buffer is full - discard characters until CR is received
      return;
    }
    else if (inChar == '\r' ) {
      outputMode = 6; // switch output to outputShiftUART
      // if the incoming character is a CR, set a flag so the main loop can
      // do something about it:
      uartInputBuffer[index] = '\0';
      index = 0; 
      uartReceiveCompleteFlag = true;
    }
    else if (inChar == '\t' ) {
      outputMode = 5; // switch output to outputShiftUART
      // if the incoming character is a TAB, set a flag so the main loop can
      // do something about it:
      uartInputBuffer[8] = '\0';
      index = 0; 
      uartReceiveCompleteFlag = true;
    }
    else {
      // add character to the uartInputBuffer:
      uartInputBuffer[index++] = inChar;
    }
  }
}
