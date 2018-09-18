#include <Arduino.h>

void setup() {
    Serial.begin(9600);
}

void loop() {
    Serial.println(analogRead(A0));
    delay(100);
    // put your main code here, to run repeatedly:
}
