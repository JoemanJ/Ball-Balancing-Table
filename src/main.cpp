#include <Arduino.h>
#include "menu.h"
#include "camera.h"
#include "display.h"
#include "servoControl.h"
#include "PIDControl.h"
#include "mqttConnect.h"

void setup() {
  delay(500);
  setupLCD();
  setupServos();

  Serial.begin(9600);
  Serial.println("Serial begun");
  setupMainMenu();
  setupCamera();
  sei();
}

void loop() {
  switch(updateBallPosition())
  {
    case REQUEST_FAIL:
      Serial.println("Failed to request object data");
      Serial.println("Check camera connection");
      //displayDebugText(L1, "REQUEST FAIL");
      break;

    case NOT_LEARNED:
      Serial.println("Camera has not learned an object");
      Serial.println("Learn an object first");
      //displayDebugText(L1, "NOT LEARNED");
      break;

    case NO_OBJECT:
      Serial.println("No object found");
      updateServo(&servoX, INI_ANG_MS);
      updateServo(&servoY, INI_ANG_MS);
      //displayDebugText(L1, "NO OBJECT");
      break;

    case UPDATE_SUCCESS:
    {
      Serial.print("X:");
      Serial.print(ballX);
      Serial.print(" Y:");
      Serial.println(ballY);

      int errorX = 160 - ballX;
      calcPID(&PIDX, errorX);
      int valX = remapPID(&PIDX, MIN_ANG_MS, MAX_ANG_MS);

      int errorY = 120 - ballY;
      calcPID(&PIDY, errorY);
      int valY = remapPID(&PIDY, MIN_ANG_MS, MAX_ANG_MS);
      
      updateServo(&servoX, valX);
      updateServo(&servoY, valY);

      /*
      Serial.print("P:");
      Serial.print(getPVal(&PIDX));
      Serial.print("   I:");
      Serial.print(getIVal(&PIDX));
      Serial.print("   D:");
      Serial.println(getDVal(&PIDX));
      Serial.print("PIDval:");
      Serial.println(getPIDVal(&PIDX));
      Serial.print("Convertion:");
      Serial.println(valX);
      */
      break;
    }
    default:
    {
      // Serial.println("Unknown error!");  
    }
  }
}
