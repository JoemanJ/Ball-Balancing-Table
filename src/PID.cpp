#include "PID.h"

unsigned int pVal = 0;
unsigned int iVal = 0;
unsigned int dVal = 0;

uint8_t pCoef = 1;
uint8_t iCoef = 1;
uint8_t dCoef = 1;

unsigned int getPVal()
{
    return pVal;
}
unsigned int getIVal()
{
    return iVal;
}

unsigned int getDVal()
{
    return dVal;
}

uint8_t getPCoef()
{
    return pCoef;
}

uint8_t getICoef()
{
    return iCoef;
}

uint8_t getDCoef()
{
    return dCoef;
}

void setPVal(unsigned int v)
{
    pVal = v;
}

void setIVal(unsigned int v)
{
    iVal = v;
}

void setDVal(unsigned int v)
{
    dVal = v;
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