#ifndef PID_CONTROL_H
#define PID_CONTROL_H

typedef struct pidc PIDControl;

extern PIDControl PIDX;
extern PIDControl PIDY; 


int getPVal(PIDControl* pc);

int getIVal(PIDControl* pc);

int getVel(PIDControl* pc);

int getDVal(PIDControl* pc);

int getPIDVal(PIDControl* pc);

int calcPID( PIDControl* pc, int error);

int remapPID(PIDControl* pc, int minRef, int maxRef);


#endif