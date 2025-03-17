#include "display.h"
#include "Arduino.h"
#include "servoControl.h"
#include <ESP32Servo.h>

#define PIN_SERVO_X 11 
#define PIN_SERVO_Y 11

Servo servoX;
Servo servoY;


void setupServos()
{
    pinMode(PIN_SERVO_X, OUTPUT);
    pinMode(PIN_SERVO_Y, OUTPUT);
    
    servoX.attach(PIN_SERVO_X, MIN_ANG_MS, MAX_ANG_MS);
    servoY.attach(PIN_SERVO_Y, MIN_ANG_MS, MAX_ANG_MS);

    servoX.writeMicroseconds(INI_ANG_MS);
    servoY.writeMicroseconds(INI_ANG_MS);
}

void updateServo(Servo* s, int ms)
{  
    s->writeMicroseconds(ms);
}
