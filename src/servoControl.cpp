#include "display.h"
#include "Arduino.h"
#include "servoControl.h"
#include <ESP32Servo.h>

Servo servoX;
Servo servoY;


void setupServos()
{
    pinMode(PIN_SERVO_X, OUTPUT);
    pinMode(PIN_SERVO_Y, OUTPUT);
    
    servoX.attach(PIN_SERVO_X, MIN_ANG_MS+X_BIAS, MAX_ANG_MS+X_BIAS);
    servoY.attach(PIN_SERVO_Y, MIN_ANG_MS+Y_BIAS, MAX_ANG_MS+Y_BIAS);

    servoX.writeMicroseconds(INI_ANG_MS+X_BIAS);
    servoY.writeMicroseconds(INI_ANG_MS+Y_BIAS);
}

void updateServo(Servo* s, int ms)
{
    s->writeMicroseconds(ms);
}
