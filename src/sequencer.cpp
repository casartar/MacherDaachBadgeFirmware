#include "sequencer.h"

// The sequencer plays back tones, so it only makes sense (and only compiles) on badges
// that actually have a buzzer for audio output.
#ifdef SOUNDBADGE

#include "audio.h"
#include "display.h"
#include "main.h"
#include <Arduino.h>
#include <EEPROM.h>

// Note constants for pitch 1-7 (row index - 1 = array index)
static const int16_t PITCH_NOTES[7] = { C_2, D_2, E_2, F_2, G_2, A_2, H_2 };

#define SEQUENCER_IDLE_TIMEOUT (3 * TIME_1_S) // 3s without a key press -> auto-play starts
#define SEQUENCER_STEP_TIME (TIME_1_S / 4) // 2000ms / 8 columns = 250ms per step
#define SEQUENCER_EEPROM_BASE_ADDR 0 // 8 bytes (one per column) starting at this EEPROM address

// Default pattern used as long as the EEPROM is still in its unwritten factory state (0xFF):
// Tetris theme (Korobeiniki) opening riff - E H C D C H A, column 8 off.
static const uint8_t DEFAULT_PATTERN[8] = { 3, 7, 1, 2, 1, 7, 6, 0 };

static bool auto_playing = false;
static bool needs_redraw = true; // only redraw when the LED state actually changes (avoids flicker)
static bool waiting_for_release = true; // after a mode switch, wait for both buttons to be released first
static uint8_t column_pitch[8]; // pitch per column, 0 = off, 1..7 = row/note - stored in EEPROM

void sequencer_intro()
{
    auto_playing = true; // start the mode directly in auto-play instead of edit mode
    countdown = SEQUENCER_STEP_TIME;
    needs_redraw = true;
    waiting_for_release = true;

    for (uint8_t c = 0; c < 8; c++) {
        column_pitch[c] = EEPROM.read(SEQUENCER_EEPROM_BASE_ADDR + c);
        if (column_pitch[c] > 7) {
            // invalid/unwritten EEPROM content (e.g. 0xFF in factory state) -> default pattern
            column_pitch[c] = DEFAULT_PATTERN[c];
        }
    }
}

void sequencer()
{
    static uint8_t column = 0; // active column, 0 = left .. 7 = right
    static bool consumed_1 = false; // left button (change pitch) - single-click lock
    static bool consumed_2 = false; // right button (next column) - single-click lock

    if (waiting_for_release) {
        // After a mode switch (2s both buttons held), the buttons are often still
        // briefly pressed - only once both are truly released are key presses
        // processed in the sequencer (otherwise the mode-switch press would
        // wrongly count as the first edit action).
        if (button_1_state == BUTTON_INACTIVE && button_2_state == BUTTON_INACTIVE) {
            waiting_for_release = false;
            countdown = auto_playing ? SEQUENCER_STEP_TIME : SEQUENCER_IDLE_TIMEOUT;
        }
    } else {
        bool button_pressed = false;

        // Left button: cycle the pitch of the ACTIVE column
        if (!consumed_1) {
            if (button_1_state == BUTTON_HELD) {
                column_pitch[column] = (column_pitch[column] + 1) % 8; // 0..7, wraps to 0 (off)
                EEPROM.update(SEQUENCER_EEPROM_BASE_ADDR + column, column_pitch[column]);
                if (column_pitch[column] == 0) {
                    playAudio(STOP, STOP);
                } else {
                    playAudio(PITCH_NOTES[column_pitch[column] - 1], TENTH);
                }
                consumed_1 = true;
                button_pressed = true;
            }
        } else if (button_1_state == BUTTON_INACTIVE) {
            consumed_1 = false;
        }

        // Right button: advance the active column
        if (!consumed_2) {
            if (button_2_state == BUTTON_HELD) {
                column = (column + 1) % 8; // wrap 7 -> 0
                consumed_2 = true;
                button_pressed = true;
            }
        } else if (button_2_state == BUTTON_INACTIVE) {
            consumed_2 = false;
        }

        if (button_pressed) {
            // key press -> back to editing, restart the idle timer
            auto_playing = false;
            countdown = SEQUENCER_IDLE_TIMEOUT;
            needs_redraw = true;
        } else if (countdown == 0) {
            if (auto_playing) {
                // next step of the automatic playback
                column = (column + 1) % 8;
                if (column_pitch[column] > 0) {
                    playAudio(PITCH_NOTES[column_pitch[column] - 1], TENTH);
                }
                countdown = SEQUENCER_STEP_TIME;
            } else {
                // 3 seconds without a key press -> start playback
                auto_playing = true;
                countdown = SEQUENCER_STEP_TIME;
            }
            needs_redraw = true;
        }
    }

    if (!needs_redraw) {
        return;
    }
    needs_redraw = false;

    // Only redraw on an actual state change (avoids flicker)
    clear_matrix_immediately_without_reset();
    matrixSetPixel(column, 0, true); // cursor, bottom row
    if (auto_playing) {
        // auto-play: only show the pitch of the column currently being played
        if (column_pitch[column] > 0) {
            matrixSetPixel(column, column_pitch[column], true);
        }
    } else {
        // editing: show pitch LEDs of all columns at once
        for (uint8_t c = 0; c < 8; c++) {
            if (column_pitch[c] > 0) {
                matrixSetPixel(c, column_pitch[c], true);
            }
        }
    }
}

#endif // SOUNDBADGE
