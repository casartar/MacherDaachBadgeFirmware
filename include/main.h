#include <Arduino.h>

// the text to display in OutputShiftString-Mode:
#define TEXT "MacherDaach 2019"
#define UART_SHIFT_SPEED_MS 40
#define TEXT_SHIFT_SPEED_MS 40

#define TIMER_PERIOD_IN_MS   2

#define TIME_1_S              (1000/TIMER_PERIOD_IN_MS)
#define TIME_200_MS           (200/TIMER_PERIOD_IN_MS)
#define TIME_50_MS            (50/TIMER_PERIOD_IN_MS)
#define TIME_20_MS            (20/TIMER_PERIOD_IN_MS)
#define TIME_10_MS            (10/TIMER_PERIOD_IN_MS)

// switch modes after pressing both buttons for this many seconds
#define SWITCH_TIME 2

#define UART_INPUT_BUFFER_SIZE 256 

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


extern volatile uint16_t countdown;
extern uint8_t x;
extern uint8_t y;
extern uint8_t matrix[8];

typedef enum{
  BUTTON_PRESSED,
  BUTTON_HELD,
  BUTTON_RELEASED,
  BUTTON_INACTIVE,
}button_state;

extern volatile button_state button_1_state;
extern volatile button_state button_2_state;

extern volatile uint8_t reqModeSwitch;
extern volatile uint16_t countdown;

extern volatile bool uartReceiveCompleteFlag;
extern volatile char uartInputBuffer[UART_INPUT_BUFFER_SIZE];

void nop();