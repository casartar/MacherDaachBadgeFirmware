#include <Arduino.h>

void display();
void clear_matrix_immediatly();
void matrixSetPixel(byte x, byte y, bool value);
void displayCharacterOffset(const byte* image, int8_t x, int8_t y);
void clear_matrix_immediatly_without_reset();
void displayCharacter(const byte* image);
void matrixShiftLeft(uint8_t newColumn);