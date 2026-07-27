#include "sequencer.h"
#include "audio.h"
#include "display.h"
#include "main.h"
#include <Arduino.h>
#include <EEPROM.h>

// Notenkonstanten für Tonhöhe 1-7 (Zeilenindex - 1 = Array-Index)
static const int16_t PITCH_NOTES[7] = { C_2, D_2, E_2, F_2, G_2, A_2, H_2 };

#define SEQUENCER_IDLE_TIMEOUT (3 * TIME_1_S) // 3s ohne Tastendruck -> Auto-Play startet
#define SEQUENCER_STEP_TIME (TIME_1_S / 4) // 2000ms / 8 Spalten = 250ms pro Schritt
#define SEQUENCER_EEPROM_BASE_ADDR 0 // 8 Bytes (eins je Spalte) ab dieser EEPROM-Adresse

static bool auto_playing = false;
static bool needs_redraw = true; // nur neu zeichnen, wenn sich am LED-Status etwas ändert (sonst Flackern)
static bool waiting_for_release = true; // nach Moduswechsel erst Loslassen beider Tasten abwarten
static uint8_t column_pitch[8]; // Tonhöhe je Spalte, 0 = aus, 1..7 = Zeile/Note - im EEPROM gespeichert

void sequencer_intro()
{
    auto_playing = false;
    countdown = SEQUENCER_IDLE_TIMEOUT;
    needs_redraw = true;
    waiting_for_release = true;

    for (uint8_t c = 0; c < 8; c++) {
        column_pitch[c] = EEPROM.read(SEQUENCER_EEPROM_BASE_ADDR + c);
        if (column_pitch[c] > 7) {
            // ungültiger/unbeschriebener EEPROM-Inhalt (z.B. 0xFF im Werkszustand)
            column_pitch[c] = 0;
        }
    }
}

void sequencer()
{
    static uint8_t column = 0; // aktive Spalte, 0 = links .. 7 = rechts
    static bool consumed_1 = false; // linker Button (Tonhöhe wechseln) - Einzel-Klick-Sperre
    static bool consumed_2 = false; // rechter Button (Spalte weiter) - Einzel-Klick-Sperre

    if (waiting_for_release) {
        // Nach dem Moduswechsel (2s beide Tasten gehalten) sind die Tasten oft noch
        // kurz gedrückt - erst wenn beide wirklich losgelassen wurden, werden
        // Tastendrücke im Sequencer verarbeitet (sonst zählt der Moduswechsel-Druck
        // fälschlich als erste Editier-Aktion).
        if (button_1_state == BUTTON_INACTIVE && button_2_state == BUTTON_INACTIVE) {
            waiting_for_release = false;
            countdown = SEQUENCER_IDLE_TIMEOUT;
        }
    } else {
        bool button_pressed = false;

        // Linker Button: Tonhöhe der AKTIVEN Spalte weiterschalten
        if (!consumed_1) {
            if (button_1_state == BUTTON_HELD) {
                column_pitch[column] = (column_pitch[column] + 1) % 8; // 0..7, wrap zu 0 (aus)
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

        // Rechter Button: aktive Spalte weiterschalten
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
            // Tastendruck -> zurück ins Editieren, Idle-Timer neu starten
            auto_playing = false;
            countdown = SEQUENCER_IDLE_TIMEOUT;
            needs_redraw = true;
        } else if (countdown == 0) {
            if (auto_playing) {
                // nächster Schritt der automatischen Wiedergabe
                column = (column + 1) % 8;
                if (column_pitch[column] > 0) {
                    playAudio(PITCH_NOTES[column_pitch[column] - 1], TENTH);
                }
                countdown = SEQUENCER_STEP_TIME;
            } else {
                // 3 Sekunden ohne Tastendruck -> Wiedergabe starten
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

    // Nur bei tatsächlicher Zustandsänderung neu zeichnen (vermeidet Flackern)
    clear_matrix_immediately_without_reset();
    matrixSetPixel(column, 0, true); // Cursor, unterste Zeile
    if (auto_playing) {
        // Auto-Play: nur die Tonhöhe der gerade abgespielten Spalte zeigen
        if (column_pitch[column] > 0) {
            matrixSetPixel(column, column_pitch[column], true);
        }
    } else {
        // Editieren: Tonhöhen-LEDs aller Spalten gleichzeitig zeigen
        for (uint8_t c = 0; c < 8; c++) {
            if (column_pitch[c] > 0) {
                matrixSetPixel(c, column_pitch[c], true);
            }
        }
    }
}
