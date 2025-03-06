#include <Arduino.h>
#include "menu.h"
#include "camera.h"

void setup() {
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
      Serial.println();
      break;

    case NOT_LEARNED:
      Serial.println("Camera has not learned an object");
      Serial.println("Learn an object first");
      Serial.println();
      break;

    case NO_OBJECT:
      Serial.println("No object found");
      Serial.println();
      break;

    case UPDATE_SUCCESS:
      Serial.print("X:");
      Serial.print(ballX);
      Serial.print(" Y:");
      Serial.println(ballY);
      break;

    default:
      Serial.println("Unknown error!");
  }

  delay(1000);
}
