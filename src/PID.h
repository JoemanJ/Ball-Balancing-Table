#ifndef PID_H
#define PID_H

#include "Arduino.h"

unsigned int getPCoef();
unsigned int getICoef();
unsigned int getDCoef();

void incPCoef();
void incICoef();
void incDCoef();
void decPCoef();
void decICoef();
void decDCoef();


#endif