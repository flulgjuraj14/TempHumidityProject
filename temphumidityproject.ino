#include <Arduino.h>
#include <Wire.h>
#include "Adafruit_SHT31.h"
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

Adafruit_SHT31 sht31 = Adafruit_SHT31();
Adafruit_SSD1306 display = Adafruit_SSD1306(128, 64, &Wire, -1);

void setup() {
  Serial.begin(115200);

  if (! sht31.begin(0x44)) {   
    Serial.println("Check circuit. SHT31 not found!");
    while (1) delay(1);
  }

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  
   // init done
  display.display();
  delay(100);
  display.clearDisplay();
  display.display();
  display.setTextColor(WHITE);
}

void loop() {
  float temp = sht31.readTemperature();
  float hum = sht31.readHumidity();

  if (! isnan(temp)) {  
    Serial.print("Temperature *C = "); 
    Serial.print(temp); 
    Serial.print("\t\t");
  } else { 
    Serial.println("Failed to read temperature!");
  }
  
  if (! isnan(hum)) {  
    Serial.print("Humidity % = "); 
    Serial.println(hum);
  } else { 
    Serial.println("Failed to read humidity!");
  }

  display.setCursor(0,0);
  display.clearDisplay();

  display.setTextSize(1);
  display.setCursor(0,0);
  display.print("Temperature: ");
  display.setTextSize(2);
  display.setCursor(0,10);
  display.print(temp);
  display.print(" ");
  display.setTextSize(1);
  display.cp437(true);
  display.write(167);
  display.setTextSize(2);
  display.print("C");
  
  // display humidity
  display.setTextSize(1);
  display.setCursor(0, 35);
  display.print("Humidity: ");
  display.setTextSize(2);
  display.setCursor(0, 45);
  display.print(hum);
  display.print(" %");
  
  display.display();
  delay(1000);
}
