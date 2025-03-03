#include "encoder.h"

#include "Arduino.h"
#include "nop.h"

unsigned int PIN_ENCODER_CLK = 2;
unsigned int PIN_ENCODER_SW = 3;
unsigned int PIN_ENCODER_DT = 4;

unsigned char last_state = 0b00;

void (*_leftCallback)(void) = doNothing;
void (*_rightCallback)(void) = doNothing;
void (*_pressCallback)(void) = doNothing;

static void onMovement();

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

    attachInterrupt(digitalPinToInterrupt(PIN_ENCODER_CLK), onMovement, CHANGE);
    attachInterrupt(digitalPinToInterrupt(PIN_ENCODER_SW), _pressCallback, FALLING);
}

static void onMovement()
{
    unsigned char CH_A = digitalRead(PIN_ENCODER_CLK);
    unsigned char CH_B = digitalRead(PIN_ENCODER_DT);

    if (CH_A == CH_B)
    {
        _leftCallback();
    }
    
    // Sentido antihorario
    else
    {
       _rightCallback();
    }
}