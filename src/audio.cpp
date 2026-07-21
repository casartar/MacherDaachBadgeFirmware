#include "audio.h"
#include "main.h"

unsigned long audio_duration = 0; // duration is decreased by 1 with each loop, 0 = audio stops

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

void updateAudio()
{
    if (audio_duration > 0) {
        audio_duration--;
        if (audio_duration == 0)
            playAudio(STOP, STOP); // stop audio
    }
}

#ifdef SOUNDBADGE
void playAudio(int note_index, int note_length)
{
    if (note_index == STOP) {
        // stop timer (stop audio completely or play pause)
        // Stop Timer1 clock by clearing CS bits (keeps PWM config)
        TCCR1B &= ~((1 << CS12) | (1 << CS11) | (1 << CS10));
        // set pin to INPUT_PULLUP to supress buzzing on matrix update
        pinMode(audio_out_pin, INPUT_PULLUP);
    } else {
        // initialize timer1 for audio output with fast PWM on pin 9 (OC1A)
        pinMode(audio_out_pin, OUTPUT);

        // set frequency and duration
        int16_t frequency_hertz = (int16_t)pgm_read_word(&notes[note_index]);
        audio_duration = FULL_NOTE_DURATION / note_length;

        // Start Timer1
        TCCR1B = (1 << WGM13) | (1 << WGM12) | (1 << CS10); // No prescaler

        // Constrain frequency to reasonable range (avoiding division by zero)
        frequency_hertz = constrain(frequency_hertz, 50, 8000);

        // Calculate TOP value for desired frequency
        // ICR1 = (CPU_freq / (prescaler * desired_freq)) - 1
        // CPU_freq = 1 MHz
        ICR1 = (unsigned int)((1000000.0 / (float)frequency_hertz) - 1);

        // Calculate OCR1A value based on duty cycle percentage
        OCR1A = (unsigned int)(((float)duty_cycle / 100.0) * ICR1);
    }
}
#else
void playAudio(int, int) { }
#endif