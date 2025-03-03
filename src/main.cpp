#include <Arduino.h>
#include "menu.h"
#include "encoder.h"

void setup() {
  Serial.begin(9600);
  Serial.println("Serial begun");
  setupTestMenu();
  sei();
}

void loop() {
  
}
