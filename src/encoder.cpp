#include "encoder.h"

#include "Arduino.h"
#include "nop.h"

#define PIN_ENCODER_SW 32
#define PIN_ENCODER_DT 35
#define PIN_ENCODER_CLK 34

void (*_leftCallback)(void) = doNothing;
void (*_rightCallback)(void) = doNothing;
void (*_pressCallback)(void) = doNothing;

static void onMovement();
static void onPress();

static unsigned short int clickFlag = 0;

void changeLeftCalback(void (*leftCallback)(void))
{
    _leftCallback = leftCallback;
}

void changeRightCalback(void (*rightCallback)(void))
{
    _rightCallback = rightCallback;
}

void changePressCalback(void (*pressCallback)(void))
{
    _pressCallback = pressCallback;
}

void setupEncoder()
{
    pinMode(PIN_ENCODER_CLK, INPUT);
    pinMode(PIN_ENCODER_DT, INPUT);
    pinMode(PIN_ENCODER_SW, INPUT_PULLUP);

    attachInterrupt(digitalPinToInterrupt(PIN_ENCODER_DT), onMovement, CHANGE);
    attachInterrupt(digitalPinToInterrupt(PIN_ENCODER_SW), onPress, FALLING);
}

static void onMovement()
{
    clickFlag = 0;

    bool CLK = digitalRead(PIN_ENCODER_CLK);
    bool DT = digitalRead(PIN_ENCODER_DT);

    if (CLK == DT)
    {
        _rightCallback();
    }
    
    else
    {
        _leftCallback();
    }
}

static void onPress()
{
    if(!digitalRead(PIN_ENCODER_SW))
    {
        if (clickFlag == 0){
            clickFlag = 1;
            return;
        } else{
            clickFlag = 0;    
            _pressCallback();
        }
    }
}