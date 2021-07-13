#include "main.h"
#include "display.h"
#include "outputGraphicsUART.h"
#include "outputShiftString.h"
#include "outputShiftUART.h"
#include "output_fill_matrix_random.h"
#include "output_fill_matrix_spiral.h"
#include "output_square.h"
#include "pong.h"
#include "snake.h"
#include <Arduino.h>
#include <TimerOne.h>
#include <string.h>

/* --------- --------- --------- ---------
 *  configure your badge in this section:
 */

// Output modes and their order
#define NUM_OF_MODES 8
// Mode to display
static uint8_t outputMode = 0;

void (*output_functions[NUM_OF_MODES])() {
    outputShiftString,
    output_fill_matrix_spiral,
    output_fill_matrix_random,
    output_square,
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
    output_init_square,
    pong_intro,
    snake_intro,
    nop,
    nop
};

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

volatile char uartInputBuffer[UART_INPUT_BUFFER_SIZE]; // a String to hold incoming data
volatile bool uartReceiveCompleteFlag = false;

void setup()
{
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
    Timer1.attachInterrupt(display, TIMER_PERIOD_IN_MS * 1000);

    // call initializer of first mode
    initializer_functions[0]();
}

void loop()
{
    //outputShiftString("123abc");
    //output_fill_matrix_slow();

    if (reqModeSwitch) {
        // both buttons were pressed for 3 seconds
        reqModeSwitch = 0;

        // create a defined state and turn off all leds
        clear_matrix_immediatly();

        // switch output mode
        outputMode++;
        // Check if max was reached, ignore last two modes (only available over uart)
        if (outputMode == NUM_OF_MODES - 2) {
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

void serialEvent()
{
    static uint8_t index = 0;
    while (Serial.available()) {
        // get the new byte:
        char inChar = (char)Serial.read();
        if (index == UART_INPUT_BUFFER_SIZE - 1) {
            // Buffer is full - discard characters until CR is received
            return;
        } else if (inChar == '\r') {
            outputMode = 6; // switch output to outputShiftUART
            // if the incoming character is a CR, set a flag so the main loop can
            // do something about it:
            uartInputBuffer[index] = '\0';
            index = 0;
            uartReceiveCompleteFlag = true;
        } else if (inChar == '\t') {
            outputMode = 5; // switch output to outputShiftUART
            // if the incoming character is a TAB, set a flag so the main loop can
            // do something about it:
            uartInputBuffer[index] = '\0';
            index = 0;
            uartReceiveCompleteFlag = true;
        } else {
            // add character to the uartInputBuffer:
            uartInputBuffer[index++] = inChar;
        }
    }
}
