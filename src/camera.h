#ifndef CAMERA_H
#define CAMERA_H

enum CameraStatus {REQUEST_FAIL, NOT_LEARNED, NO_OBJECT, UPDATE_SUCCESS};

extern unsigned int ballX;
extern unsigned int ballY;

void setupCamera();
CameraStatus updateBallPosition();

#endif