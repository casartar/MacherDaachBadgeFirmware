#include <Arduino.h>

void display();
void clear_matrix_immediately();
void matrixSetPixel(byte x, byte y, bool value);
void displayCharacterOffset(const byte* image, int8_t x, int8_t y);
void clear_matrix_immediately_without_reset();
void displayCharacter(const byte* image);
void matrixShiftLeft(uint8_t newColumn);