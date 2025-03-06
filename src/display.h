#ifndef DISPLAY_H
#define DISPLAY_H

#include <stdint.h>

void setupLCD();
void changeScreen(void (*displayFunction)(void));
void refreshDisplay();

//Wrappers
void displayWrite(const char* str);
void displayWrite(uint8_t n);
void displayClear(void);
void displaySetCursor(uint8_t col, uint8_t row);
void displayCursor(void);
void displayNoCursor(void);
void displayBlink(void);
void displayNoBlink(void);


//Debug
void helloWorldFunc();

#endif