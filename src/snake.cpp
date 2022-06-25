#include "snake.h"
#include "display.h"
#include "main.h"
#include <Arduino.h>

// crazy snake !!1ELF!
// mmmixed up and down by schmo-fu

struct segment {
    int8_t pos;
    segment* next;
};

#define TOP 0
#define RIGHT 1
#define BOTTOM 2
#define LEFT 3

void snake_intro()
{
    char demosnake[] = "ooooooololoroorooroololooox";
    int8_t snake_head = 6 * 8 + 7;
    int8_t snake_tail = 6 * 8 + 7;
    uint8_t snake_dir = LEFT;
    uint8_t snake_length = 19;
    uint8_t snake_sim = 0;

    // pseudo mouse
    matrixSetPixel(5, 1, true);

    // Snake-Animation
    while (demosnake[snake_sim] != 'x') {

        // display snake
        matrixSetPixel(snake_head % 8, snake_head / 8, true); // show next head position
        if (snake_sim >= snake_length) {
            matrixSetPixel(snake_tail % 8, snake_tail / 8, false); // remove at tail position
        }

        // button simulation
        if (demosnake[snake_sim] == 'r') { // turn to the right
            if (snake_dir == TOP) {
                snake_dir = LEFT;
            } else {
                snake_dir--;
            }
        } else if (demosnake[snake_sim] == 'l') { // turn to the left
            if (snake_dir == LEFT) {
                snake_dir = TOP;
            } else {
                snake_dir++;
            }
        }

        // move the head
        switch (snake_dir) {
        case TOP:
            snake_head -= 8;
            if (snake_head < 0) {
                snake_head += 64;
            }
            break;
        case RIGHT:
            snake_head += 1;
            if (snake_head % 8 == 0) {
                snake_head -= 8;
            }
            break;
        case BOTTOM:
            snake_head += 8;
            if (snake_head > 63) {
                snake_head -= 64;
            }
            break;
        case LEFT:
            snake_head -= 1;
            if ((snake_head % 8 == 7) || (snake_head == -1)) {
                snake_head += 8;
            }
            break;
        }

        // move the tail
        if (snake_sim >= snake_length) {
            snake_tail -= 1; // tail moves only to the left, because it's just an animation, darling
        }

        // animation speed
        snake_sim += 1;
        delay(100);
    }

    // Shift Snake banner across the screen
    uint8_t banner[8][13] = {
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 1, 1, 0, 1, 0, 1, 0, 0, 1, 1, 0 },
        { 0, 1, 0, 1, 0, 1, 1, 0, 0, 1, 1, 1, 1 },
        { 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0 },
        { 0, 0, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
    };
    for (uint8_t i = 0; i < 13; i++) {
        matrixShiftLeft(B00000000);
        for (uint8_t j = 0; j < 8; j++) {
            matrixSetPixel(7, 7 - j, banner[j][i]);
        }
        delay(150);
    }
    matrixShiftLeft(B00000000);

    // cleanup after the intro
    delay(400);
    clear_matrix_immediatly_without_reset();
}

void snake()
{
    static uint8_t speed = 100;
    static bool debounced = true;
    static uint8_t snake_dir = RIGHT;
    static uint8_t snake_len = 1;
    static uint16_t snake_age = 0;
    static uint8_t mouse_pos = 10;
    static uint16_t egg_timer = 0;
    static segment* tail = new segment { .pos = 32, .next = NULL };

    // check buttons
    if (debounced) {
        if (button_1_state == BUTTON_HELD) { // turn to the left
            if (snake_dir == TOP) {
                snake_dir = LEFT;
            } else {
                snake_dir--;
            }
            debounced = false;
        }
        if (button_2_state == BUTTON_HELD) { // turn to the right
            if (snake_dir == LEFT) {
                snake_dir = TOP;
            } else {
                snake_dir++;
            }
            debounced = false;
        }
    } else if ((button_1_state == BUTTON_INACTIVE) && (button_2_state == BUTTON_INACTIVE)) {
        debounced = true;
        egg_timer = 0;
    } else if ((button_1_state == BUTTON_HELD) && (button_2_state == BUTTON_HELD)) {
        egg_timer = 1;
    } else if ((egg_timer > 0) && ((button_1_state == BUTTON_HELD) xor (button_2_state == BUTTON_HELD))) {
        egg_timer += 1;
        if (egg_timer == 15000) {
            egg_timer = 0;
            clear_matrix_immediatly_without_reset();
            snake_intro();
        }
    }

    if (countdown == 0) { // showtime!
        // snake ist getting older
        snake_age += 1;

        // move the snake
        segment* snake = new segment { .pos = tail->pos, .next = tail };
        switch (snake_dir) {
        case TOP:
            snake->pos += 8;
            if (snake->pos > 63) {
                snake->pos -= 64;
            }
            break;
        case RIGHT:
            snake->pos += 1;
            if (snake->pos % 8 == 0) {
                snake->pos -= 8;
            }
            break;
        case BOTTOM:
            snake->pos -= 8;
            if (snake->pos < 0) {
                snake->pos += 64;
            }
            break;
        case LEFT:
            snake->pos -= 1;
            if ((snake->pos % 8 == 7) || (snake->pos == -1)) {
                snake->pos += 8;
            }
            break;
        }

        // check for mouse contact
        if (snake->pos == mouse_pos) {
            snake_len += 1;
            if (snake_age >= (snake_len * 2)) { // eating makes the snake younger again
                snake_age -= snake_len * 2;
            } else {
                snake_age = 0;
            }
            // create new mouse at some later time
            mouse_pos = 64 + 4; // wait for three turns
        } else {
            // snake_len stays the same. As we added a new head we must remove the last tail segment
            segment* p = snake;
            while (p->next->next != NULL) {
                p = p->next;
            }
            delete p->next;
            p->next = NULL;
        }

        // no collision detection, but old snakes eat themselves
        if (snake_age >= 200) {
            if (snake_len >= 2) {
                segment* p = snake;
                while (p->next->next != NULL) {
                    p = p->next;
                }
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
            matrixSetPixel(mouse_pos % 8, mouse_pos / 8, true);
        } else if (mouse_pos == 64) {
            // new mouse position
            mouse_pos = (snake->pos + 28) % 64;
        } else {
            mouse_pos -= 1; // wait another turn
        }
        // draw snake
        tail = snake;
        while (snake != NULL) {
            matrixSetPixel(snake->pos % 8, snake->pos / 8, true);
            snake = snake->next;
        }
        countdown = speed - (snake_len - 1) * 5; // more speed with longer snakes, it's crazy!
    }
}
