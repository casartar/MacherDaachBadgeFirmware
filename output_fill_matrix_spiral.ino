void output_init_matrix_spiral() {
  output_fill_matrix_spiral(true);
}

void output_fill_matrix_spiral() {
  output_fill_matrix_spiral(false);
}

void output_fill_matrix_spiral(bool init){
  static uint8_t round = 0;
  static uint8_t mode = 1;  // 1 = fill, 0 = clear
  static uint8_t direction = 0;

  if(init){
    round = 0;
    mode = 1;
    direction = 0;
    x = -1;
    y = 0;
  }
  
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

    matrixSetPixel(x, y, mode);

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
