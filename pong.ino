extern PROGMEM const byte PONGO[][8] = {
{ // left half of introscreen
  B00000000,
  B01100000,
  B01010000,
  B01100100,
  B01001010,
  B01000100,
  B00000000,
  B00000000
},{ // right half of introscreen
  B00000000,
  B00000000,
  B00000000,
  B11000110,
  B10101010,
  B10100110,
  B00000010,
  B00000100
},{ // Left player wins
  B10101000,
  B01010000,
  B00000000,
  B00100000,
  B00100000,
  B00000000,
  B11010000,
  B10110000
},{ // right player wins
  B00010101,
  B00001010,
  B00000000,
  B00000100,
  B00000100,
  B00000000,
  B00001101,
  B00001011
}};

// game states
#define PLAY 0
#define POINT_A 1
#define POINT_B 2
#define WIN 99


void pong_intro() {

  for (int i = 0; i<5; i++) {
    for (int xOffset = 0; xOffset >= -8; xOffset -= 1) {
      // left part
      if (xOffset >= -7) {
        displayCharacterOffset(PONGO[0],xOffset,0);
      }
      // right part
      if(xOffset <= -1) {
        displayCharacterOffset(PONGO[1],xOffset+8,0);
      }
      delay(150 - i*25);
    }
    for (int xOffset = -7; xOffset < 0; xOffset += 1) {
      // left part
      displayCharacterOffset(PONGO[0],xOffset,0);
      // right part
      displayCharacterOffset(PONGO[1],xOffset+8,0);
      delay(150 - i*25 - 12);
    }
  }
}


void pong(){
  static uint8_t speed = 100;
  static uint8_t points_a = 0;
  static uint8_t points_b = 0;
  static uint8_t pos_act = 0;
  static bool direction = false; // false = right ;-)
  static bool lane = true; // true = upper lane
  static uint8_t fields_valid = 2; // rebounce if button was pressed
  static uint8_t game_state = PLAY;
  static uint8_t blinker = 0;

  // check rebounce
  if( ((direction == false) && (pos_act > 7-fields_valid) && (button_2_state == BUTTON_PRESSED)) ||
      ((direction == true) && (pos_act < 0 + fields_valid) && (button_1_state == BUTTON_PRESSED)) ) {
    direction = !direction;
    lane = !lane;
  }

  if (countdown == 0){ // game logic and then display something

    if (game_state == PLAY) {
      if (direction) {
        pos_act--;
      }else{
        pos_act++;
      }

      // check for points
      // act_pos is unsigned -> values greater 7 is a point for A or B depending on direction
      if(pos_act > 7){
        // count points
        if (direction){
          points_b++;
          game_state = POINT_B;
        }else{
          points_a++;
          game_state = POINT_A;
        }
        // get ready for the next round
        direction = !direction;
        if (direction) {
          pos_act=7;
        }else{
          pos_act=0;
        }
        lane = true;
        speed = 100;

        // check if the winner is decided
        if (points_a == 8) {
          points_a = 9;
          game_state = WIN;
        } else if (points_b == 8) {
          points_b = 9;
          game_state = WIN;
        }
      }
    }

    // reset last frame
    clear_matrix_immediatly_without_reset();
    
    switch (game_state) {
      case PLAY:
        // draw new frame
        if (lane) {
          matrixSetPixel(pos_act, 4, true);
        } else {
          matrixSetPixel(pos_act, 3, true);
        }
        matrixSetPixel(points_a, 0, true);
        matrixSetPixel(points_b, 7, true);
        speed--;
        countdown = speed;
        break;

      case POINT_A:
        matrixSetPixel(points_a, 0, blinker & 0x01);
        matrixSetPixel(points_b, 7, true);
        blinker += 1;
        countdown = 100;
        break;

      case POINT_B:
        matrixSetPixel(points_a, 0, true);
        matrixSetPixel(points_b, 7, blinker & 0x01);
        blinker += 1;
        countdown = 100;
        break;

      case WIN:
        if (points_b == 9) {
          displayCharacter (PONGO[3]);
          direction = false; // nächstes Spiel startet beim Verlierer
        } else {
          displayCharacter (PONGO[2]);
          direction = true; // nächstes Spiel startet beim Verlierer
        }
        // get ready for the next game
        if (direction) {
          pos_act=7;
        }else{
          pos_act=0;
        }
        points_a = 0;
        points_b = 0;
        game_state = PLAY;
        countdown = 800;
        break;
    }

    if (blinker >= 6) {
      blinker = 0;
      countdown = speed;
      game_state = PLAY;
    }
  }
}
