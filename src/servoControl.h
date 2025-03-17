#ifndef SERVOCONTROL_H
#define SERVOCONTROL_H

#define INI_ANG_MS 1500
#define MIN_ANG_MS 1000
#define MAX_ANG_MS 2000

#include <ESP32Servo.h>

extern Servo servoX;
extern Servo servoY;

void setupServos();

void updateServo(Servo* s, int ms);

#endif

