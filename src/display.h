#ifndef DISPLAY_H
#define DISPLAY_H

#include <stdint.h>

void setupLCD();
void changeScreen(void (*displayFunction)(void));
void refreshDisplay();

//Wrappers
void displayWrite(const char* str);
void displayWrite(uint8_t n);
void displayWrite(unsigned int n);
void displayClear(void);
void displaySetCursor(uint8_t col, uint8_t row);
void displayCursor(void);
void displayNoCursor(void);
void displayBlink(void);
void displayNoBlink(void);

enum DISPLAY_LINES {L1 = 0, L2 = 1};
void displayDebugInt(DISPLAY_LINES line, int var, const char* prefix);
void displayDebugText(DISPLAY_LINES line, const char* txt);


//Debug
void helloWorldFunc();

#endif