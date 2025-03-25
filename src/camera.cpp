#include "camera.h"

#include <HUSKYLENS.h>

HUSKYLENS huskylens;

unsigned int ballX = 0;
unsigned int ballY = 0;

void setupCamera()
{
    Wire.begin();

    while (!huskylens.begin(Wire))
    {
        Serial.println(F("Begin failed!"));
        Serial.println(F("1.Please recheck the \"Protocol Type\" in HUSKYLENS (General Settings>>Protocol Type>>I2C)"));
        Serial.println(F("2.Please recheck the connection."));
        delay(100);
    }
}

CameraStatus updateBallPosition()
{
    if (!huskylens.request()) return REQUEST_FAIL;
    if (!huskylens.isLearned()) return NOT_LEARNED;
    if (!huskylens.available()) return NO_OBJECT;
    
    HUSKYLENSResult result = huskylens.read();
    ballX = result.xCenter;
    ballY = result.yCenter;

    return UPDATE_SUCCESS;
}