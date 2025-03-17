#ifndef PID_CONTROL_H
#define PID_CONTROL_H

#include "Arduino.h"

typedef struct pidc PIDControl;

extern PIDControl PIDX;
extern PIDControl PIDY; 


unsigned int getPVal(PIDControl* pc);

unsigned int getIVal(PIDControl* pc);

unsigned int getDVal(PIDControl* pc);

unsigned int getPIDVal(PIDControl* pc);

int calcPID( PIDControl* pc, int error);

int remapPID(PIDControl* pc, int minRef, int maxRef);


#endif