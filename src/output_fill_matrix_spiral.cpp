#include "output_fill_matrix_spiral.h"
#include "audio.h"
#include "display.h"
#include "main.h"
#include <Arduino.h>

#define MODE_CLEAR 0
#define MODE_FILL 1

#define SPIRAL_RIGHT 0
#define SPIRAL_UP 1
#define SPIRAL_LEFT 2
#define SPIRAL_DOWN 3

void output_fill_matrix_spiral(bool init);

void output_init_matrix_spiral()
{
    output_fill_matrix_spiral(true);
}

void output_fill_matrix_spiral()
{
    output_fill_matrix_spiral(false);
}

void output_fill_matrix_spiral(bool init)
{
    static uint8_t round = 0;
    static uint8_t mode = MODE_FILL;
    static uint8_t direction = 0;

    if (init) {
        round = 0;
        mode = MODE_FILL;
        direction = SPIRAL_RIGHT;
        x = -1;
        y = 0;
    }

    if (countdown == 0) {
        if (mode == MODE_FILL) {
            if (x == round && y == round + 1) {
                direction = SPIRAL_RIGHT;
                playAudio(random(24 + random(24)), HALF);
                round++;
            } else if (x == 7 - round && y == round) {
                direction = SPIRAL_UP;
            } else if (x == 7 - round && y == 7 - round) {
                direction = SPIRAL_LEFT;
            } else if (x == round && y == 7 - round) {
                direction = SPIRAL_DOWN;
            }

        } else {
            // clear
            if (x == round && y == round) {
                direction = SPIRAL_RIGHT;
            } else if (x == 7 - round && y == round) {
                direction = SPIRAL_UP;
            } else if (x == 7 - round && y == 7 - round) {
                direction = SPIRAL_LEFT;
            } else if (x == round - 1 && y == 7 - round) {
                direction = SPIRAL_DOWN;
                playAudio(random(24 + random(24)), HALF);
                round--;
            }
        }

        switch (direction) {
        case SPIRAL_RIGHT:
            x++;
            break; // to the right
        case SPIRAL_UP:
            y++;
            break; // upwards
        case SPIRAL_LEFT:
            x--;
            break; // to the left
        case SPIRAL_DOWN:
            y--;
            break; // downwards
        }

        matrixSetPixel(x, y, mode);

        if (mode == MODE_FILL && x == 3 && y == 4) { // last pixel activ - switch to turn off
            mode = MODE_CLEAR;
            direction = SPIRAL_RIGHT;
            x--;
            y--;
        }

        if (mode == MODE_CLEAR && x == 0 && y == 7) { // last pixel clear - refill again
            mode = MODE_FILL;
            direction = SPIRAL_RIGHT;
            x = -1;
            y = 0;
        }
        countdown = TIME_20_MS;
    }
}
