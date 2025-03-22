#ifndef SERVOCONTROL_H
#define SERVOCONTROL_H

#define PIN_SERVO_X 12 //MOTOR ROXO
#define PIN_SERVO_Y 14 //MOTOR MARELO

#define INI_ANG_MS 1500
#define MIN_ANG_MS 1200
#define MAX_ANG_MS 1800

#include <ESP32Servo.h>

extern Servo servoX;
extern Servo servoY;

void setupServos();

void updateServo(Servo* s, int ms);

#endif

