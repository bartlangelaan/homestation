// Sources used:
// - https://github.com/esp8266/Arduino/blob/master/libraries/ESP8266WiFi/examples/WiFiMulti/WiFiMulti.ino

#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>

ESP8266WiFiMulti wifiMulti;

void setupWifi() {
  WiFi.mode(WIFI_STA);

  // For the open-source code, I removed all wifi networks.
  // You can add an unimited amount of WiFi networks, the
  // network with the best signal will be used.
  //
  // Defining WiFi networks works like this:
  //
  // wifiMulti.addAP("ssid1", "password1");
  // wifiMulti.addAP("ssid2", "password2");
}

bool wifiConnected() {
  return wifiMulti.run() == WL_CONNECTED;
}
