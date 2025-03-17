#include "PID.h"


unsigned int pCoef = 1;
unsigned int iCoef = 1;
unsigned int dCoef = 1;


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
    if (pCoef < 255) pCoef++;
}

void incICoef()
{
    if (iCoef < 255) iCoef++;
}

void incDCoef()
{
    if (dCoef < 255) dCoef++;
}

void decPCoef()
{
    if (pCoef > 0) pCoef--;
}

void decICoef()
{
    if (iCoef > 0) iCoef--;
}

void decDCoef()
{
    if (dCoef > 0) dCoef--;
}
