// Sources used:
// - http://arduino-er.blogspot.nl/2016/04/hello-world-nodemcu-esp8266-128x64-i2c.html

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define OLED_RESET LED_BUILTIN  //4
Adafruit_SSD1306 display(OLED_RESET);

#if (SSD1306_LCDHEIGHT != 32)
#error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif

void displaySetup() {
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
}

int leftPadToCenter(String string, int fontSize = 1) {
  return (128 - (string.length() * fontSize * 6)) / 2;
}

void displayShow(String value, String unit, String type) {
  display.clearDisplay();

  // First line (1 - 11)
  String firstLine = "The " + type + " is";
  display.setTextSize(1);
  display.setTextColor(INVERSE);
  display.fillRect(0, 0, 128, 11, WHITE);
  display.setCursor(leftPadToCenter(firstLine), 2);
  display.println(firstLine);

  // Progress line (13 - 15)
  float m = millis();
  float progress = m / 1000 / SCREEN_DISPLAY_TIME;
  int p = progress;
  int width = (progress - p) * 128;
  if(p % 2 == 0) {
    display.fillRect(0, 13, width, 2, WHITE);
  } else {
    display.fillRect(width, 13, 128 - width, 2, WHITE);
  }
  

  // Second line (18 - 32)
  String secondLine = value + unit;
  display.setTextSize(2);
  display.setCursor(leftPadToCenter(secondLine, 2), 18);
  display.println(secondLine);
  display.display();
}

