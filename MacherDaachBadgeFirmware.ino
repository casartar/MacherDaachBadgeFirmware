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

// Add here a define for your output mode and increase OUTPUT_MODE_MAX accordingly
#define FILL_MATRIX_SLOW        0
#define FILL_MATRIX_FAST        1
#define FILL_MATRIX_SPIRAL      2
#define FILL_MATRIX_RANDOM      3
#define OUTPUT_MODE_MAX         4

volatile uint8_t reqModeSwitch = 0;
volatile uint16_t countdown = 0;

int8_t x = 0;
int8_t y = 0;

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

  digitalWrite(LED_Y1, !matrix[0][state]);
  digitalWrite(LED_Y2, !matrix[1][state]);
  digitalWrite(LED_Y3, !matrix[2][state]);
  digitalWrite(LED_Y4, !matrix[3][state]);
  digitalWrite(LED_Y5, !matrix[4][state]);
  digitalWrite(LED_Y6, !matrix[5][state]);
  digitalWrite(LED_Y7, !matrix[6][state]);
  digitalWrite(LED_Y8, !matrix[7][state]);

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
    if (mode_switch_timer == TIME_3_S){
      reqModeSwitch = 1;
    }
  }
  else{
    mode_switch_timer = 0;
  }

  // Countdown
  if (countdown > 0) countdown--;
}

void loop() {
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
      default:
        break;
    }
  }

  // Call your output mode in this switch
  switch (outputMode){
    case FILL_MATRIX_SLOW:
      output_fill_matrix_slow();
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
    default:
      break;
  }
}

// output mode functions
void output_fill_matrix_slow(){
  if (countdown == 0){
    matrix[y][x] = 1;
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

void output_fill_matrix_fast(){
  if (countdown == 0){
    matrix[y][x] = 1;
    x++;
    if (x > 7){
      x = 0;
      y++;
      if (y > 7){
        clear_matrix_immediatly();
      }
    }
    countdown = TIME_20_MS;
  }
}

void output_fill_matrix_spiral(){
  static uint8_t round = 0;
  static uint8_t mode = 1;  // 1 = fill, 0 = clear
  static uint8_t direction = 0;

  if (countdown == 0){
    if (mode == 1) {
      // fill
      if (x == round && y == round + 1) {
        direction = 0;
        round++;
      } else if (x == 7 - round && y == round) {
        direction = 1;
      } else if (x == 7 -round && y == 7 - round) {
        direction = 2;
      } else if (x == round && y == 7 - round) {
        direction = 3;
      }

    } else {
      // clear
      if (x == round && y == round) {
        direction = 0;
      } else if (x == 7 - round && y == round) {
        direction = 1;
      } else if (x == 7 - round && y == 7 - round) {
        direction = 2;
      } else if (x == round - 1 && y == 7 - round) {
        direction = 3;
        round--;
      }
    }

    switch(direction) {
      case 0: x++; break;  // to the right
      case 1: y++; break;  // upwards
      case 2: x--; break;  // to the left
      case 3: y--; break;  // downwards
    }

    matrix[y][x] = mode;

    if (mode == 1 && x == 3 && y == 4) {  // last pixel activ - switch to turn off
      mode = 0;
      direction = 0;
      x--;
      y--;
    }

    if (mode == 0 && x == 0 && y == 7) {  // last pixel clear - refill again
      mode = 1;
      direction = 0;
      x = -1;
      y = 0;
    }
    countdown = TIME_20_MS;
  }
}

unsigned int rng() {
  static unsigned int r = 0;
  r += micros(); // seeded with changing number
  r ^= r << 2; r ^= r >> 7; r ^= r << 7;
  return (r);
}

void output_fill_matrix_random() {
    x = rng() / 8192;
    y = rng() / 8192;
    matrix[y][x] = !matrix[y][x];
}

// add your output mode function here

// Helper functions
void clear_matrix_immediatly(){
  for (y = 0; y < 8; y++){
    for (x = 0; x < 8; x++){
      matrix[y][x] = 0;
    }
  }
  // reset x and y for further use
  x = 0;
  y = 0;
}
