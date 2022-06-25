#include "outputShiftString.h"
#include "characters.h"
#include "display.h"
#include "main.h"

const char text[] PROGMEM = TEXT;

void outputShiftString(const char* text);

// helper function for mode-array
void outputShiftString()
{
    outputShiftString(text);
}

//Shifts string through matrix
void outputShiftString(const char* text)
{
    const char* t;
    static int i = 0;
    static int xOffset = 0;
    static int yOffset = 0;
    static bool fistrun = true;

    /* iterate over text characters
   * loop takes car of two characters a the same time
  */

    if (countdown == 0) {
        //remember last drawn char
        t = text;
        t = t + i;

        // if first character start from left side
        if (fistrun) {
            xOffset = 7;
            fistrun = false;
        }
        // draw char
        displayCharacterOffset(ASCII[(int)*t], xOffset, yOffset);

        // *********second charcter part***********
        if (xOffset < 0) {
            displayCharacterOffset(ASCII[(int)*(t + 1)], xOffset + 8, yOffset);
        }

        countdown = TEXT_SHIFT_SPEED_MS;

        //reset if end of string
        if (*t == '\0') {
            i = 0;
            //xOffset=0;
            fistrun = true;
        }
        // if charachter shift completed
        if (xOffset <= -8) {
            xOffset = 0;
            i++;
        }
        //set X offset for next cycle
        xOffset--;
    }
}