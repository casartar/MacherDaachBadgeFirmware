// Square / Split moves from left to right and again from right to left
// You can switch between square and split with buttons
// You can pause with buttons and make the pause go away again

#include "output_square.h"
#include "display.h"
#include "main.h"
#include <Arduino.h>

void output_square(bool init);

void output_init_square()
{
    output_square(true);
}

void output_square()
{
    output_square(false);
}
// A square is painted (ledOn = 1) or a square is removed (ledOn = 0).
void draw_square(uint8_t pos_x, uint8_t pos_y, bool ledOn, uint8_t size)
{

    for (uint8_t i = 0; i < size; i++) // x-row
    {
        for (uint8_t k = 0; k < size; k++) // y-column
        {
            matrixSetPixel(i + pos_x, k + pos_y, ledOn); // Pixel an/aus machen bei bestimmter Position
        }
    }
}
// A split is painted (ledOn = 1) or a split is removed (ledOn = 0).
void draw_split(uint8_t pos_x, uint8_t pos_y, bool ledOn, uint8_t ysize, uint8_t xsize)
{

    for (uint8_t m = 0; m < xsize; m++) // x-row
    {
        for (uint8_t n = 0; n < ysize; n = n + 2) // y-column
        {
            matrixSetPixel(m + pos_x, n + pos_y, ledOn); // Pixel an/aus machen bei bestimmter Position
        }
    }
}
// There is a change of direction when one is needed (at the edges).
uint8_t leftright(uint8_t olddirection, uint8_t pos_row)
{
    // When the x-row of LEDs is over
    // When the object is all the way to the right, it moves to the left again
    if (pos_row == 4) {
        return -1;
    }
    // When the object is all the way to the left, it moves to the right again
    else if (pos_row == 0) {
        return +1;
    }
    // If the object is not all the way to the left or all the way to the right, it retains the direction in which it was previously moving.
    else {
        return olddirection;
    }
}
// The LEDs are switched on or off
bool LEDonoff(bool ledOn)
{
    // If the LEDs were on, the LEDs are switched off
    if (ledOn == true) {
        return false;
    }
    // If the LEDs were off, the LEDs are switched on
    else {
        return true;
    }
}

void output_square(bool init)
{
    static uint8_t square_size; // size of the square( 4 = 4x4 square)
    static uint8_t square_pos_row; // xpos from square
    static uint8_t square_pos_column; // ypos from square
    static uint8_t xsplit_size; // size of split in x-direction ( 4 = 4 LEDs per "row")
    static uint8_t ysplit_size; // size of the split in y-direction ( 8 = 4 "rows")
    static uint8_t split_pos_row; // xpos from split
    static uint8_t split_pos_colum; // xpos from split
    static int8_t direction_of_movement; // +1 = right / -1 = left
    static bool ledOn; // 0 = LED off / 1 = LED on
    static bool split; // false = no split / true = split
    static bool pause; // false = no pause / true = pause

    if (init) {
        square_pos_row = 0;
        square_pos_column = 2;
        square_size = 4;
        split_pos_row = 0;
        split_pos_colum = 0;
        ysplit_size = 8;
        xsplit_size = 4;
        ledOn = true;
        split = false;
        pause = false;
        direction_of_movement = -1;
    }

    // Button 2 is on the right, Button 1 is on the left, when the right button is pressed a split appears / when the left button is pressed a square appears
    if ((button_1_state == BUTTON_HELD) && (button_2_state == BUTTON_INACTIVE)) {
        split = false;
        pause = false;
    } else if ((button_2_state == BUTTON_HELD) && (button_1_state == BUTTON_INACTIVE)) {
        split = true;
        pause = false;
    }

    // There is a pause when both buttons are pressed at the same time, to stop the pause you should press the left or right button
    if ((button_2_state == BUTTON_PRESSED) && (button_1_state == BUTTON_PRESSED)) {
        pause = true;
    }

    // Split

    if (countdown == 0 && split == true && pause == false) {

        ledOn = LEDonoff(ledOn);

        // Remove Split(ledOn = 0)
        draw_split(split_pos_row, split_pos_colum, ledOn, ysplit_size, xsplit_size);

        // Remove square(ledOn = 0)
        draw_square(square_pos_row, square_pos_column, ledOn, square_size);

        direction_of_movement = leftright(direction_of_movement, split_pos_row);

        // The direction of movement is changed or remains / left -> right, right -> left
        split_pos_row += direction_of_movement;

        ledOn = LEDonoff(ledOn);

        // Split paint(ledOn = 1)
        draw_split(split_pos_row, split_pos_colum, ledOn, ysplit_size, xsplit_size);

        countdown = TIME_1_S; //the countdown is set from 1 to 0 every time, it makes the object move every second, time changeable
    }

    // Square

    if (countdown == 0 && split == false && pause == false) {

        ledOn = LEDonoff(ledOn);

        // Remove Split(ledOn = 0)
        draw_split(split_pos_row, split_pos_colum, ledOn, ysplit_size, xsplit_size);

        // Remove square(ledOn = 0)
        draw_square(square_pos_row, square_pos_column, ledOn, square_size);

        direction_of_movement = leftright(direction_of_movement, square_pos_row);

        // The direction of movement is changed or remains / left -> right, right -> left
        square_pos_row += direction_of_movement;

        ledOn = LEDonoff(ledOn);

        // Draw square(ledOn = 1)
        draw_square(square_pos_row, square_pos_column, ledOn, square_pos_row);

        // The countdown is set again and again from 0 to 1 and then again from 1 to 0. This makes that the object moves every 1 second, the time is changeable
        countdown = TIME_1_S;
    }
}
