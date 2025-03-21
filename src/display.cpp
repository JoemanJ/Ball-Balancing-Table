#include "display.h"

#include "Arduino.h"
#include <LiquidCrystal.h>

#define PIN_LCD_RS 18 // pin 12 on Arduino
#define PIN_LCD_ENABLE 19 // pin 11 on Arduino
#define PIN_LCD_D4 27
#define PIN_LCD_D5 26
#define PIN_LCD_D6 25
#define PIN_LCD_D7 33

LiquidCrystal lcd = LiquidCrystal(\
    PIN_LCD_RS,     \
    PIN_LCD_ENABLE, \
    PIN_LCD_D4,     \
    PIN_LCD_D5,     \
    PIN_LCD_D6,     \
    PIN_LCD_D7);

void (*_displayCallback)(void);

void setupLCD()
{
    pinMode(PIN_LCD_RS, OUTPUT);
    pinMode(PIN_LCD_ENABLE, OUTPUT);
    pinMode(PIN_LCD_D4, OUTPUT);
    pinMode(PIN_LCD_D5, OUTPUT);
    pinMode(PIN_LCD_D6, OUTPUT);
    pinMode(PIN_LCD_D7, OUTPUT);

    lcd = LiquidCrystal(\
        PIN_LCD_RS,     \
        PIN_LCD_ENABLE, \
        PIN_LCD_D4,     \
        PIN_LCD_D5,     \
        PIN_LCD_D6,     \
        PIN_LCD_D7);

    lcd.begin(16, 2, LCD_5x8DOTS);
    lcd.clear();
}

void changeScreen(void (*displayFunction)(void))
{
    _displayCallback = displayFunction;
    _displayCallback();
}

void refreshDisplay()
{
    _displayCallback();
}

void helloWorldFunc()
{
    lcd.write("Hello World!");
    lcd.setCursor(0, 1);
    lcd.write("123");
    lcd.cursor();
}

void displayWrite(const char* str)
{
    lcd.print(str);
}

void displayWrite(uint8_t n)
{
    lcd.print(n);
}

void displayWrite(unsigned int n)
{
    lcd.print(n);
}

void displayClear(void)
{
    lcd.clear();
}

void displaySetCursor(uint8_t col, uint8_t row)
{
    lcd.setCursor(col, row);
}

void displayCursor(void)
{
    lcd.cursor();
}

void displayNoCursor(void)
{
    lcd.noCursor();
}

void displayBlink(void)
{
    lcd.blink();
}

void displayNoBlink(void)
{
    lcd.noBlink();
}

void displayDebugInt(DISPLAY_LINES line, int var, const char* prefix = NULL)
{
    lcd.setCursor(0, line);
    lcd.print("                ");
    lcd.setCursor(0, line);
    if (prefix != NULL) lcd.print(prefix);
    lcd.print(var);
}

void displayDebugText(DISPLAY_LINES line, const char* txt)
{
    lcd.setCursor(0, line);
    lcd.print("                ");
    lcd.setCursor(0, line);
    lcd.print(txt);
}