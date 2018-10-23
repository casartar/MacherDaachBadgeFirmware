
void pong(){
  static uint8_t speed = 100;
  static bool start_left = true;
  //static uint8_t difficult_a = 0;
  //static uint8_t difficult_b = 0;
  static uint8_t points_a = 0;
  static uint8_t points_b = 0;
  static uint8_t pos_act = 0;
  static bool direction = 0; // 0 = right
  static uint8_t fields_valid = 2; // rebounce if button was pressed 

  // check rebounce
  if(direction == false && (pos_act > 7-fields_valid) && button_2_state == BUTTON_PRESSED || direction == true && (pos_act < 0 + fields_valid)  && button_1_state == BUTTON_PRESSED){
    direction = !direction;
  }
  
  if (countdown == 0){

    if(direction){
      pos_act--;
    }else{
      pos_act++;
    }
  
    // check for points
    // act_pos is unsigned -> values greater 7 is a point for A or B depending on direction
    if(pos_act > 7){
      if (direction){
        points_b++;
      }else{
        points_a++;
      }
      
      start_left != start_left;
      if(start_left){
        pos_act=0;
        direction=0;
      }else{
        pos_act=7;
        direction=1;
      }
      speed =100;
    }

    if(points_a > 7 || points_b > 7){
      points_a=0;
      points_b=0;
    }
    // reset last frame
    clear_matrix_immediatly_without_reset();
    // draw new frame
    matrixSetPixel(pos_act, 4, true);
    matrixSetPixel(points_a, 0, true);
    matrixSetPixel(points_b, 7, true);
    speed--;
    countdown = speed;
  }
}

