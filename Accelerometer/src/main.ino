// Basic demo for tap/doubletap readings from Adafruit LIS3DH

#include <Wire.h>
#include <SPI.h>
#include <Adafruit_LIS3DH.h>
#include <Adafruit_Sensor.h>

#include "Adafruit_VCNL4010.h"

Adafruit_VCNL4010 vcnl;

// Used for software SPI
#define LIS3DH_CLK 13
#define LIS3DH_MISO 12
#define LIS3DH_MOSI 11
// Used for hardware & software SPI
#define LIS3DH_CS 10

// software SPI
//Adafruit_LIS3DH lis = Adafruit_LIS3DH(LIS3DH_CS, LIS3DH_MOSI, LIS3DH_MISO, LIS3DH_CLK);
// hardware SPI
//Adafruit_LIS3DH lis = Adafruit_LIS3DH(LIS3DH_CS);
// I2C
Adafruit_LIS3DH lis = Adafruit_LIS3DH();

#if defined(ARDUINO_ARCH_SAMD)
// for Zero, output on USB Serial console, remove line below if using programming port to program the Zero!
   #define Serial SerialUSB
#endif

void setup(void) {
#ifndef ESP8266
  while (!Serial);     // will pause Zero, Leonardo, etc until serial console opens
#endif

  Serial.begin(9600);
    Serial.println("Adafruit LIS3DH ADC Test!");
  
  if (! lis.begin(0x18)) {   // change this to 0x19 for alternative i2c address
    Serial.println("Couldnt start");
    while (1);
  }
  Serial.println("LIS3DH found!");
  
  lis.setRange(LIS3DH_RANGE_2_G);   // 2, 4, 8 or 16 G!
  
  Serial.print("Range = "); Serial.print(2 << lis.getRange());  
  Serial.println("G");
  
  pinMode(3, OUTPUT);
  
}


void loop() {
  
  sensors_event_t event; 
  lis.getEvent(&event);
  // Serial.println(lis.z);
  
  // Serial.print(" X: "); Serial.print(event.acceleration.x);
  // Serial.print(" Y: "); Serial.print(event.acceleration.y);
  // Serial.print(" Z: "); Serial.print(event.acceleration.z);
  // Serial.println();
  
  float voltage = float(mapf(lis.z, -32768, 32767, 0.0, 255));
  float true_v = mapf(voltage, 0.0, 160, 0, 3.3);
  // Serial.print("voltage: "); Serial.println(true_v);
  
  // delay(1000);
}

float mapf(float x, float in_min, float in_max, float out_min, float out_max) {
  float result;
  result = (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
  return result;
}
