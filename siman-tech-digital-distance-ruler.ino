#include "Adafruit_VL53L0X.h"

Adafruit_VL53L0X lox = Adafruit_VL53L0X();
VL53L0X_RangingMeasurementData_t measure;

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_I2CDevice.h>
#include <SPI.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

Adafruit_SSD1306 display = Adafruit_SSD1306(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);


void setupDistanceSensor()
{
  // Distance sensor test
  if (!lox.begin())
  {
    Serial.println(F("Failed to boot VL53L0X"));
    while (1)
      ;
  }
}

float getDistance()
{
    lox.rangingTest(&measure, false); // pass in 'true' to get debug data printout!
    Serial.println(measure.RangeMilliMeter);
    return measure.RangeMilliMeter;
}

bool initializeLCD()
{

    if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C))
    { // Address 0x3D for 128x64
        Serial.println(F("SSD1306 allocation failed"));
        for (;;)
            ;
    }
    delay(2000);
    display.clearDisplay();
    return true;
}

void displayDistance(float distanceValue)
{
    Serial.println("kesini bray");
    display.clearDisplay();
    display.setTextSize(2);
    display.setTextColor(WHITE);
    // Display static text
    display.setCursor(0, 10);
    display.println("Distance:");
    // Display current temperature value
    display.setCursor(0, 40);
    display.println(distanceValue);
    display.setCursor(80, 40);
    // Display static text
    display.println("cm");
    display.display();
}

void setup()
{
  Serial.begin(115200);
  setupDistanceSensor();
  initializeLCD();
  
  Serial.println(F("Setup LCD and Distance Sensor Success!\n\n"));
}

void loop()
{
    displayDistance(getDistance());
    delay(100);

}
