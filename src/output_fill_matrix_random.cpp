#include <Arduino.h>
#include "output_fill_matrix_random.h"
#include "main.h"

unsigned int rng();

void output_fill_matrix_random() {
  static uint8_t i = 0;
  if(countdown == 0){
    x = rng() / 256;

    matrix[i] = x;
    i++;
    if (i >7){
      i=0;
    }
    countdown = TIME_20_MS;
  }
}


unsigned int rng() {
  static unsigned int r = 0;
  r += micros(); // seeded with changing number
  r ^= r << 2;
  r ^= r >> 7;
  r ^= r << 7;
  return (r);
}

