#include <Arduino.h>

const uint8_t duty_cycle = 50; // 50% duty cycle for audio PWM

const uint8_t notes_size = 60; // 60 notes in 5 octaves

const int FULL_NOTE_DURATION = 1000; // duration of a full note in loop cycles
#define STOP 0
#define FULL 1
#define HALF 2
#define QUARTER 4
#define EIGHT 8
#define SIXTEENTH 16

// note frequencies (hertz)
const int16_t notes[] PROGMEM = {
    // Octave 0
    131, 139, 147, 156, 165, 175, 185, 196, 208, 220, 233, 247,
    // Octave 1
    262, 277, 294, 311, 330, 349, 370, 392, 415, 440, 466, 494,
    // Octave 2
    523, 554, 587, 622, 659, 698, 740, 784, 831, 880, 932, 988,
    // Octave 3
    1047, 1109, 1175, 1245, 1319, 1397, 1480, 1568, 1661, 1760, 1865, 1976,
    // OCtave 4
    2093, 2217, 2349, 2489, 2637, 2794, 2960, 3136, 3322, 3520, 3729, 3951
};

// names fpr notes-indices (S = Sharp, #)
#define C_0 0
#define CS_0 1
#define D_0 2
#define DS_0 3
#define E_0 4
#define F_0 5
#define FS_0 6
#define G_0 7
#define GS_0 8
#define A_0 9
#define AS_0 10
#define H_0 11

#define C_1 12
#define CS_1 13
#define D_1 14
#define DS_1 15
#define E_1 16
#define F_1 17
#define FS_1 18
#define G_1 19
#define GS_1 20
#define A_1 21
#define AS_1 22
#define H_1 23

#define C_2 24
#define CS_2 25
#define D_2 26
#define DS_2 27
#define E_2 28
#define F_2 29
#define FS_2 30
#define G_2 31
#define GS_2 32
#define A_2 33
#define AS_2 34
#define H_2 35

#define C_3 36
#define CS_3 37
#define D_3 38
#define DS_3 39
#define E_3 40
#define F_3 41
#define FS_3 42
#define G_3 43
#define GS_3 44
#define A_3 45
#define AS_3 46
#define H_3 47

#define C_4 48
#define CS_4 49
#define D_4 50
#define DS_4 51
#define E_4 52
#define F_4 53
#define FS_4 54
#define G_4 55
#define GS_4 56
#define A_4 57
#define AS_4 58
#define H_4 59

void updateAudio();
void playAudio(int frequency_hertz, int note_length);