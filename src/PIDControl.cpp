#include "PID.h"
#include "PIDControl.h"


#define MIN_P_VAL -50000
#define MAX_P_VAL 50000
#define MIN_I_VAL -50000
#define MAX_I_VAL 50000
#define MIN_D_VAL -50000
#define MAX_D_VAL 50000
#define MIN_PID_VAL -50000
#define MAX_PID_VAL 50000

#define DT_FIRST_VAL -1

struct pidc{
    int pVal = 0;
    int iVal = 0;
    int dVal = 0;
    int pidVal = 0;

    unsigned long lastTime = millis();        
    double deltaTime = DT_FIRST_VAL;    
    int lastError = 0;
};

PIDControl PIDX;
PIDControl PIDY; 

unsigned int getPVal(PIDControl* pc)
{
    return pc->pVal;
}

unsigned int getIVal(PIDControl* pc)
{
    return pc->iVal;
}

unsigned int getDVal(PIDControl* pc)
{
    return pc->dVal;
}

unsigned int getPIDVal(PIDControl* pc)
{
    return pc->pidVal;
}

int calcPID( PIDControl* pc, int error)
{
    unsigned int pCoef = getPCoef();
    unsigned int iCoef = getICoef();
    unsigned int dCoef = getDCoef();

    //calc proportinal value
    int p = pCoef*error;
    
    if(p>MAX_P_VAL) pc->pVal = MAX_P_VAL;
    else if(p<MIN_P_VAL) pc->pVal = MIN_P_VAL;
    else pc->pVal = p;

    //calc deltatime
    unsigned long time = millis();

    if (pc->lastTime > time){ //insane overflow dodge
        time += sizeof(unsigned long) - pc->lastTime;
        pc->lastTime = 0;
    }
    
    if (pc->deltaTime != DT_FIRST_VAL) pc->deltaTime = (double(time - pc->lastTime))/1000.0;
    else{ //firtCalcOnly
        pc->deltaTime = 1; 
        pc->lastTime = time;
        pc->pidVal = pc->pVal;
        return pc->pidVal;
    } 

    pc->lastTime = time;

    //calc integral value
    int i = iCoef*error*pc->deltaTime;

    if(i>MAX_I_VAL) pc->iVal = MAX_I_VAL;
    else if(i<MIN_I_VAL) pc->iVal = MIN_I_VAL;
    else pc->iVal = i;

    //calc drivative value
    int d = dCoef*((error-pc->lastError)/pc->deltaTime);

    if(d>MAX_D_VAL) pc->dVal = MAX_D_VAL;
    else if(d<MIN_D_VAL) pc->dVal = MIN_D_VAL;
    else pc->dVal = d;

    //total value
    int pid = pc->pVal+pc->iVal+pc->dVal;
    
    if(pid>MAX_PID_VAL) pc->pidVal = MAX_PID_VAL;
    else if(pid<MIN_PID_VAL) pc->pidVal = MIN_PID_VAL;
    else pc->pidVal = pid;

    return pc->pidVal;
}

int remapPID(PIDControl* pc, int minRef, int maxRef)
{
    return map(pc->pidVal, MIN_PID_VAL, MAX_PID_VAL, minRef, maxRef);
}
