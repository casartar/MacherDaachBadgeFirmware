// crazy snake !!1ELF!
// mmmixed up and down by schmo-fu
  
struct segment {
    int8_t pos;
    segment *next;
  };

void snake(){
  static uint8_t speed = 100;
  static bool debounced = true;
  #define TOP    0
  #define RIGHT  1
  #define BOTTOM 2
  #define LEFT   3
  static uint8_t snake_dir = RIGHT;
  static uint8_t snake_len = 1;
  static uint8_t snake_age = 0;
  static uint8_t mouse_pos = 10;
  static segment *tail = new segment {.pos = 32, .next = NULL};

  // check buttons
  if (debounced) {
    if (button_2_state == BUTTON_HELD) { // turn to the left
      if (snake_dir == TOP) { snake_dir = LEFT; }
      else { snake_dir--; } 
      debounced = false;
    }
    if (button_1_state == BUTTON_HELD) {
      if (snake_dir == LEFT) { snake_dir = TOP; }
      else { snake_dir++; } 
      debounced = false;
    }
  } else if ((button_2_state == BUTTON_INACTIVE) && (button_1_state == BUTTON_INACTIVE)) {
    debounced = true;
  }
  
  if (countdown == 0) {  // showtime!
    // snake ist getting older
    snake_age += 1;
    
    // move the snake
    segment *snake = new segment {.pos = tail->pos, .next = tail};
    switch (snake_dir) {
      case TOP: snake->pos -= 8; if (snake->pos < 0) {snake->pos += 64;} break;
      case RIGHT: snake->pos += 1; if (snake->pos % 8 == 0) {snake->pos -= 8;} break;
      case BOTTOM: snake->pos += 8; if (snake->pos > 63) {snake->pos -= 64;} break;
      case LEFT: snake->pos -= 1; if ((snake->pos % 8 == 7) || (snake->pos == -1)) {snake->pos += 8;} break;
    }
  
    // check for mouse contact
    if (snake->pos == mouse_pos) {
      snake_len += 1;
      if(snake_age >= (snake_len * 2)) { // eating makes the snake younger again
        snake_age -= snake_len * 2;
      } else {
        snake_age = 0;
      }
      // create new mouse at some later time
      mouse_pos = 64 + 3; // wait for three turns
    } else {
      // snake_len stays the same. As we added a new head we must remove the last tail segment
      segment *p = snake;
      while (p->next->next != NULL) { p = p->next; }
      delete p->next;
      p->next = NULL; 
    }
    
    // no collision detection, but old snakes eat themselves
    if (snake_age >= 200) {
      if (snake_len >= 2) {  
        segment *p = snake;
        while (p->next->next != NULL) { p = p->next; }
        delete p->next;
        p->next = NULL; 
        snake_len -= 1;
        snake_age -= 30;
      } else {
        snake_age = 0; // zooom! starved and reborn.
      }
    }
    
    // reset last frame
    clear_matrix_immediatly_without_reset();
    // update and draw mouse
    if (mouse_pos < 64) {
      matrixSetPixel(mouse_pos%8, mouse_pos/8, true);
    } else if (mouse_pos == 64) {
      // new mouse position
      mouse_pos = (snake->pos + 28)%64;
    } else {
      mouse_pos -= 1; // wait another turn
    }
    // draw snake
    tail = snake;
    while (snake != NULL) {
      matrixSetPixel(snake->pos%8, snake->pos/8, true);
      snake = snake->next;
    }
    countdown = speed - (snake_len-1) * 5; // more speed with longer snakes, it's crazy!
  }
}
