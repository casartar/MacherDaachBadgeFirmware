#include "audio.h"
#include "main.h"

unsigned long audio_duration = 0; // duration is decreased by 1 with each loop, 0 = audio stops

void updateAudio()
{
    if (audio_duration > 0) {
        audio_duration--;
        if (audio_duration == 0)
            playAudio(STOP, STOP); // stop audio
    }
}

void playAudio(int note_index, int note_length)
{
#ifndef SOUNDBADGE
    return;
#endif
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