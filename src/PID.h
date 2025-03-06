#ifndef PID_H
#define PID_H

#include "Arduino.h"

unsigned int getPVal();
unsigned int getIVal();
unsigned int getDVal();
uint8_t getPCoef();
uint8_t getICoef();
uint8_t getDCoef();

void setPVal(unsigned int v);
void setIVal(unsigned int v);
void setDVal(unsigned int v);
void incPCoef();
void incICoef();
void incDCoef();
void decPCoef();
void decICoef();
void decDCoef();

#endif