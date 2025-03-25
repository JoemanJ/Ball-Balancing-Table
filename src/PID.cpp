#include "PID.h"


unsigned int pCoef = 275; //350
unsigned int iCoef = 10;  //30
unsigned int dCoef = 25;  //10


unsigned int getPCoef()
{
    return pCoef;
}

unsigned int getICoef()
{
    return iCoef;
}

unsigned int getDCoef()
{
    return dCoef;
}

void incPCoef()
{
    if (pCoef < 1000) pCoef+=5;
}

void incICoef()
{
    if (iCoef < 1000) iCoef+=5;
}

void incDCoef()
{
    if (dCoef < 1000) dCoef+=5;
}

void decPCoef()
{
    if (pCoef > 0) pCoef-=5;
}

void decICoef()
{
    if (iCoef > 0) iCoef-=5;
}

void decDCoef()
{
    if (dCoef > 0) dCoef-=5;
}
