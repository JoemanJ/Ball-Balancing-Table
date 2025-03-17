#include <Arduino.h>
#include "menu.h"
#include "camera.h"
#include "display.h"
#include "servoControl.h"


void setup() {
  setupLCD();
  setupServos();

  Serial.begin(9600);
  Serial.println("Serial begun");
  // setupMainMenu();
  // setupCamera();
  sei();
}

void loop() {
  switch(updateBallPosition())
  {
    case REQUEST_FAIL:
      // Serial.println("Failed to request object data");
      // Serial.println("Check camera connection");
      displayDebugText(L1, "REQUEST FAIL");
      break;

    case NOT_LEARNED:
      // Serial.println("Camera has not learned an object");
      // Serial.println("Learn an object first");
      displayDebugText(L1, "NOT LEARNED");
      break;

    case NO_OBJECT:
      // Serial.println("No object found");
      displayDebugText(L1, "NO OBJECT");
      break;

    case UPDATE_SUCCESS:
      // Serial.print("X:");
      // Serial.print(ballX);
      // Serial.print(" Y:");
      // Serial.println(ballY);
      //displayDebugInt(L1, ballX, "X: ");
      //displayDebugInt(L2, ballY, "Y: ");
      break;

    default:
      // Serial.println("Unknown error!");
      displayDebugText(L1, "UNKNOWN ERROR");
  }

  delay(1000);
}
