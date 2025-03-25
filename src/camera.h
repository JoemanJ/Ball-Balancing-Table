#ifndef CAMERA_H
#define CAMERA_H

/*
    HUSKYLENS connection (using I2C protocol):
    HUSKYLENS T to MCU SDA (pin D21 on ESP board)
    HUSKYLENS R to MCU SCL (pin D22 on ESP board)
*/

enum CameraStatus {REQUEST_FAIL, NOT_LEARNED, NO_OBJECT, UPDATE_SUCCESS};

extern unsigned int ballX;
extern unsigned int ballY;

void setupCamera();
CameraStatus updateBallPosition();

#endif